#include "mainwindow.h"
#include "ui_mainwindow.h"

//是否显示 直方图统计功能,切换tof/peak的按钮
//#define SHOW_HISTORGRAM_BUTTON
//#define SHOW_TOF_PEAK_BUTTON

using namespace std;

//图像显示相关
extern QMutex mutex_3D;  //3D点云/2D传输的互斥锁
extern QImage tofImage;
extern QImage intensityImage;
extern pcl::PointCloud<pcl::PointXYZRGB> pointCloudRgb;
extern bool isShowPointCloud;  //是否有点云数据 ，有的话显示否则不显示

//鼠标点击显示时相关
extern QMutex mouseShowMutex;
extern float mouseShowTOF[160][120];
extern int mouseShowPEAK[160][120];

/*保存用到的标识*/
extern bool isSaveFlag;        //是否进行存储
extern QString saveFilePath;   //保存的路径  E:/..../.../的形式
extern int saveFileIndex;      //文件标号；1作为开始

/*****是否进行数据接收的标识*****/
extern bool isRecvFlag;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isLinkSuccess = false;     //USB 连接是否成功的标识

#ifndef SHOW_HISTORGRAM_BUTTON
    ui->tof_Histogram_pushButton->setVisible(false);
    ui->peak_Histogram_pushButton->setVisible(false);
#endif
#ifndef SHOW_TOF_PEAK_BUTTON
    ui->tof_peak_change_toolButton->setVisible(false);
#endif


    init_thread();
    init_connect();
    load_ini_file();
    dealMsg_obj->loadLocalArray();   //接收数据线程中 加载角度矩阵的矫正文件
}

MainWindow::~MainWindow()
{
    delete ui;
}

//!
//! \brief init_thread
//! //线程的初始化
void MainWindow::init_thread()
{
    //数据接收线程
    dealMsg_thread = new QThread();
    dealMsg_obj = new DealUsb_msg();
    dealMsg_obj->moveToThread(dealMsg_thread);
    dealMsg_thread->start();

    //文件保存线程
    savePcd_thread = new QThread();      //文件保存线程
    savePcd_obj = new savePCDThread;
    savePcd_obj->moveToThread(savePcd_thread);
    savePcd_thread->start();

    //统计信息相关
    calThread = new QThread();
    calMeanStd_obj = new calMeanStdThread(); //
    calMeanStd_obj->moveToThread(calThread);
    calThread->start();

    //USB数据接收相关
    recvUsb_thread = new QThread();
    recvUsbMsg_obj = new ReceUSB_Msg();
    recvUsbMsg_obj->moveToThread(recvUsb_thread);
    recvUsb_thread->start();


}


//!
//! \brief init_connect
//! //信号与槽的初始化
void MainWindow::init_connect()
{
    //与数据处理线程的 信号与槽的连接
    connect(dealMsg_obj,&DealUsb_msg::Display_log_signal,this,&MainWindow::Display_log_slot);
    connect(this,&MainWindow::change_gain_signal,dealMsg_obj,&DealUsb_msg::change_gain_slot);
    connect(this,&MainWindow::change_tof_peak_signal,dealMsg_obj,&DealUsb_msg::change_tof_peak_slot);
    connect(this,&MainWindow::isFilter_signal,dealMsg_obj,&DealUsb_msg::isFilter_slot);


    //文件保存相关的信号与槽的连接
    connect(&fileSave_dia,&fileSave_Dialog::isSaveFlagSignal,this,&MainWindow::isSaveFlagSlot);
    connect(dealMsg_obj,&DealUsb_msg::saveTXTSignal,savePcd_obj,&savePCDThread::saveTXTSlot);

    //统计信息相关的槽函数
    connect(calMeanStd_obj,SIGNAL(statistic_MeanStdSignal(QStringList,QStringList,QStringList,QStringList)),&statisticsDia_,SLOT(statistic_MeanStdSlot(QStringList,QStringList,QStringList,QStringList)));
    connect(&statisticsDia_,SIGNAL(startStop_signal(int)),calMeanStd_obj,SLOT(startStop_slot(int)));
    connect(&statisticsDia_,SIGNAL(alterStatisticFrameNum_signal(int)),dealMsg_obj,SLOT(alterStatisticFrameNum_slot(int)));

    //2D图像的显示相关
    connect(&show_image_timer,SIGNAL(timeout()),this,SLOT(show_image_timer_slot()));

    //鼠标停靠处显示
    connect(ui->tof_label,SIGNAL(queryPixSignal(int,int)),this,SLOT(queryPixel_showToolTip_slot(int,int)));
    connect(ui->peak_label,SIGNAL(queryPixSignal(int,int)),this,SLOT(queryPixel_showToolTip_slot(int,int)));

    //USB设备连接相关
    connect(this,SIGNAL(openLink_signal(int,int)),recvUsbMsg_obj,SLOT(openLinkDevSlot(int,int)));
    connect(recvUsbMsg_obj,SIGNAL(Display_log_signal(QString)),this,SLOT(Display_log_slot(QString)));
    connect(recvUsbMsg_obj,SIGNAL(linkInfoSignal(int)),this,SLOT(USB_linkInfoSlot(int)));
    connect(this,SIGNAL(closeLinkSignal()),recvUsbMsg_obj,SLOT(closeUSB()));
    connect(this,SIGNAL(readSysSignal(int,bool)),recvUsbMsg_obj,SLOT(readSysSlot(int,bool)));
    connect(recvUsbMsg_obj,&ReceUSB_Msg::reReadSysSignal,this,&MainWindow::reReadSysSlot);
    connect(this,&MainWindow::writeSysSignal,recvUsbMsg_obj,&ReceUSB_Msg::writeSysSlot);
    connect(this,&MainWindow::loadSettingSignal,recvUsbMsg_obj,&ReceUSB_Msg::loadSettingSlot);
    connect(this,&MainWindow::start_read_usb_signal,recvUsbMsg_obj,&ReceUSB_Msg::read_usb);


    //数据接收 与数据处理线程
    connect(recvUsbMsg_obj,SIGNAL(recvMsgSignal(QByteArray)),dealMsg_obj,SLOT(recvMsgSlot(QByteArray)));

    //自动校正相关
    connect(&autoCal_dia,SIGNAL(start_autoCalibration_signal(int)),dealMsg_obj,SLOT(start_autoCalibration_slot(int)));
    connect(dealMsg_obj,SIGNAL(send_cali_success_signal(QString)),&autoCal_dia,SLOT(send_cali_success_slot(QString)));



}

//!
//! \brief MainWindow::load_ini_file
//!加载配置集文件
void MainWindow::load_ini_file()
{
    QSettings configSetting("setting.ini", QSettings::IniFormat);

    int Rotate_rate = configSetting.value("operation/Rotate_rate").toInt();
    int Scale_rate = configSetting.value("operation/Scale_rate").toInt();
    int transtate_rate = configSetting.value("operation/transtate_rate").toInt();

    if(Rotate_rate==0 || Scale_rate==0 || transtate_rate==0)    //防止第一次加载时，没有配置文件，这时候初始化为初始值
    {
        Rotate_rate = 8;
        Scale_rate = 10;
        transtate_rate = 30;
        QString log_str = "[load conf file error]:setting.ini";
        Display_log_slot(log_str);
    }

    ui->widget->rotateRate = Rotate_rate;
    ui->widget->scaleRate = Scale_rate;
    ui->widget->translateRate = transtate_rate;


    ui->rotate_horizontalSlider->setValue(Rotate_rate);
    ui->scale_horizontalSlider->setValue(Scale_rate);
    ui->translate_horizontalSlider->setValue(transtate_rate);
    QString log_str = "[load conf file success]:setting.ini";
    Display_log_slot(log_str);

}


//!
//! \brief MainWindow::on_openFile_action_triggered
//!打开本地文件的槽函数  弹出窗口
void MainWindow::on_openFile_action_triggered()
{
    QString filePath=QFileDialog::getExistingDirectory();
    filePath.append("/");

    if(filePath.length()<2)
        return;

    localFileDirPath = filePath;
    QString log_str_ = "[Local Dir]:" + filePath;
    Display_log_slot(log_str_);

    dealMsg_obj->playLocalFile_slot(filePath);

}

//!
//! \brief MainWindow::on_play_pushButton_clicked
//!开启播放图像的槽函数
void MainWindow::on_play_pushButton_clicked()
{
    if(ui->play_pushButton->text() == "play")
    {
        ui->widget->show3D_timer.start(90);   //3D点云的刷新频率
        show_image_timer.start(90);
        ui->play_pushButton->setText("pause");

        if(isLinkSuccess)
        {
           isRecvFlag = true;
           emit start_read_usb_signal();
           QString log_str = "[video start]";
           Display_log_slot(log_str);
        }

    }else
    {
        ui->widget->show3D_timer.stop();
        show_image_timer.stop();
        ui->play_pushButton->setText("play");
        QString log_str = "[video stop]";
        Display_log_slot(log_str);
    }
}


//!
//! \brief MainWindow::show_image_timer_slot
//! 播放2D图像的槽函数
void MainWindow::show_image_timer_slot()
{
    if(!isShowPointCloud)
        return;

    if(!tofImage.isNull() && !intensityImage.isNull())
    {
        mutex_3D.lock();
        QPixmap pixmap_tof(QPixmap::fromImage (tofImage));
        ui->tof_label->setPixmap(pixmap_tof);

        QPixmap pixmap_peak(QPixmap::fromImage (intensityImage));
        ui->peak_label->setPixmap(pixmap_peak);
        mutex_3D.unlock();
    }
}


//! \brief MainWindow::queryPixel_showToolTip_slot
//! \param x   实际的x坐标值  缩放以后的
//! \param y   实际的y坐标值  缩放以后的
//!  鼠标停靠处显示tof和peak
void MainWindow::queryPixel_showToolTip_slot(int x,int y)
{

    float width_scale = ui->tof_label->width()/160.0;
    float height_scale = ui->tof_label->height()/120.0;

    int y_index = y/height_scale;
    int x_index = x/width_scale;
//    qDebug()<<"y_index="<<y_index<<"  x_index ="<<x_index;
    int index = 160*y_index + x_index;
    mouseShowMutex.lock();
    QString str= "x="+QString::number(x_index)+",y="+QString::number(y_index)+",Depth="+QString::number(mouseShowTOF[x_index][y_index])+"m,peak="+QString::number(mouseShowPEAK[x_index][y_index]);
    mouseShowMutex.unlock();
    QToolTip::showText(QCursor::pos(),str);
}


//!
//! \brief MainWindow::Display_log_slot
//!打印控制信息的槽函数
void MainWindow::Display_log_slot(QString str)
{
    ui->control_log_textEdit->append(str);
}



//!
//! \brief MainWindow::on_tof_peak_change_toolButton_clicked
//!切换tof peak的槽函数
void MainWindow::on_tof_peak_change_toolButton_clicked()
{
    emit change_tof_peak_signal();
}


//!
//! \brief MainWindow::on_gain_lineEdit_returnPressed
//!改变增益的槽函数
void MainWindow::on_gain_lineEdit_returnPressed()
{
    float gain = ui->gain_lineEdit->text().toFloat();
    emit change_gain_signal(gain);
}

//!
//! \brief MainWindow::on_filter_radioButton_clicked
//!是否进行滤波的槽函数
void MainWindow::on_filter_radioButton_clicked()
{
    bool isChecked = ui->filter_radioButton->isChecked();
    emit isFilter_signal(isChecked);
}

//!
//! \brief MainWindow::on_statistic_action_triggered
//!统计信息 弹出界面函数
void MainWindow::on_statistic_action_triggered()
{
    QMessageBox::warning(NULL,QStringLiteral("提示"),QStringLiteral("该功能需要管理员权限，否则可能会异常退出"));
    statisticsDia_.setModal(true);
    statisticsDia_.show();
}

//!
//! \brief MainWindow::on_saveFile_action_triggered
//!文件保存界面 弹出
void MainWindow::on_saveFile_action_triggered()
{
    fileSave_dia.setModal(true);
    fileSave_dia.show();
}

//!
//! \brief isSaveFlagSlot
//! 文件保存 接收的槽函数
void MainWindow::isSaveFlagSlot(bool flag,QString filePath,int fileFormat)
{


   isSaveFlag = flag;        //是否进行存储
   saveFilePath = filePath;   //保存的路径  E:/..../.../的形式
   saveFileIndex = 1;      //文件标号；1作为开始
}


//旋转角度设置的槽函数
void MainWindow::on_rotate_horizontalSlider_sliderMoved(int position)
{
    ui->widget->rotateRate = position;
    save3DSettingFile();
}

//缩放比例设置的槽函数
void MainWindow::on_scale_horizontalSlider_sliderMoved(int position)
{
    ui->widget->scaleRate = position;
    save3DSettingFile();
}

//拖放比例的槽函数
void MainWindow::on_translate_horizontalSlider_sliderMoved(int position)
{
    ui->widget->translateRate = 110 - position;
    save3DSettingFile();
}

//鼠标控制相关的配置 会保存到配置文件当中
void MainWindow::save3DSettingFile()
{
    QSettings configSetting("setting.ini", QSettings::IniFormat);

    int rotateRate = ui->widget->rotateRate;
    int scaleRate = ui->widget->scaleRate;
    int translateRate = 110-ui->widget->translateRate;

    configSetting.setValue("operation/Rotate_rate",rotateRate);
    configSetting.setValue("operation/Scale_rate",scaleRate);
    configSetting.setValue("operation/transtate_rate",translateRate);

}

//显示  peak的阈值
void MainWindow::on_peakOffset_lineEdit_returnPressed()
{
    int peakOffset = ui->peakOffset_lineEdit->text().toInt();
    dealMsg_obj->peakOffset = peakOffset;
}
//显示  平均的帧数
void MainWindow::on_averageNum_lineEdit_returnPressed()
{
    int average_frameNum = ui->averageNum_lineEdit->text().toInt();
    dealMsg_obj->averageNum = average_frameNum;
}
//显示 只显示中心区域
void MainWindow::on_centerShowYes_radioButton_clicked()
{
    dealMsg_obj->isOnlyCenterShow_flag = true;
}
//显示 不显示中心区域
void MainWindow::on_centerShowNo_radioButton_clicked()
{
    dealMsg_obj->isOnlyCenterShow_flag = false;
}




/********************************************  USB 配置相关的槽函数   ********************************************************************/
//!
//! \brief MainWindow::on_linkUSB_pushButton_clicked
//!连接USB 设备的槽函数
void MainWindow::on_linkUSB_pushButton_clicked()
{

    if(ui->linkUSB_pushButton->text() == QStringLiteral("连接设备"))
    {
        int vid = ui->VID_lineEdit->text().toInt(NULL,16);
        int pid = ui->PID_lineEdit->text().toInt(NULL,16);
        emit openLink_signal(vid,pid);

    }else
    {
        isRecvFlag = false;
        isLinkSuccess = false;
        emit closeLinkSignal();
        ui->linkUSB_pushButton->setText(QStringLiteral("连接设备"));
    }
}
//!
//! \brief MainWindow::on_readSys_pushButton_clicked
//! 读取系统寄存器的额槽函数
void MainWindow::on_readSys_pushButton_clicked()
{
    if(!isLinkSuccess)
    {
        QMessageBox::information(NULL,QStringLiteral("告警"),QStringLiteral("设备未连接"));
        return;
    }
    int address = ui->sysAddress_lineEdit->text().toInt(NULL,16);

    if(isRecvFlag)
    {
        isRecvFlag = false;
        emit readSysSignal(address,true);
    }else
    {
        emit readSysSignal(address,false);
    }
}

//!
//! \brief MainWindow::reReadSysSlot   //读取sys的返回结果
//! \param str
//!
void MainWindow::reReadSysSlot(QString str)
{
    int m = str.toInt();
    qDebug()<<" the data =  "<<m<<endl;
    ui->sysData_lineEdit->setText(QString::number(m,16));
}



//!
//! \brief MainWindow::on_writeSys_pushButton_clicked
//!写入系统寄存器的槽函数
void MainWindow::on_writeSys_pushButton_clicked()
{
    if(!isLinkSuccess)
    {
        QMessageBox::information(NULL,QStringLiteral("告警"),QStringLiteral("设备未连接"));
        return;
    }
    int address = ui->sysAddress_lineEdit->text().toInt(NULL,16);
    QString data = ui->sysData_lineEdit->text();

    if(isRecvFlag)
    {
        isRecvFlag = false;
        emit writeSysSignal(address,data,true);
    }else
    {
        emit writeSysSignal(address,data,false);
    }
    ui->sysData_lineEdit->clear();

}
//!
//! \brief MainWindow::on_loadSetting_pushButton_clicked
//!加载配置集的槽函数
void MainWindow::on_loadSetting_pushButton_clicked()
{
    if(!isLinkSuccess)
    {
        QMessageBox::information(NULL,QStringLiteral("告警"),QStringLiteral("设备未连接"));
        return;
    }


    QString file_path;
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(QStringLiteral("请选择寄存器配置文件"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径

    QStringList mimeTypeFilters;
    mimeTypeFilters <<QStringLiteral("芯片配置文件(*.para)|*.para") ;
    fileDialog->setNameFilters(mimeTypeFilters);

    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }else
    {
        return;
    }


    file_path = fileNames[0];
    qDebug()<<" file_path = "<<fileNames[0]<<endl;

    QString checkStr = file_path.right(4);
    if("para" != checkStr)
    {
        QMessageBox::information(NULL,QStringLiteral("告警"),QStringLiteral("请选择正确的配置文件！"));
        return ;
    }

    if(isRecvFlag)
    {
        isRecvFlag = true;
        emit loadSettingSignal(file_path,true);
    }else
    {
        emit loadSettingSignal(file_path,false);
    }

}
//!
//! \brief MainWindow::on_saveSetting_pushButton_clicked
//!保存配置集的槽函数
void MainWindow::on_saveSetting_pushButton_clicked()
{
    if(!isLinkSuccess)
    {
        QMessageBox::information(NULL,QStringLiteral("告警"),QStringLiteral("设备未连接"));
        return;
    }
}

//!
//! \brief MainWindow::USB_linkInfoSlot
//! \param flag
//!USB 连接的返回信息
//! //向主线程发送链接信息（错误警告）
// 0：连接正常 1没找到设备
// 2:没有接收到数据  3打开设备失败
// 4：读取系统成功；5：读取系统失败；
// 6：读取设备成功；7：读取设备失败
// 8：加载配置信息成功；9：加载配置信息失败
// 10：保存配置信息成功； 11：保存配置信息失败
// 12：写入系统成功      13：写入系统失败
// 14：写入设备成功      15：写入设备失败
void MainWindow::USB_linkInfoSlot(int flag )
{
    if(0 == flag)     //连接正常
    {
        ui->linkUSB_pushButton->setText(QStringLiteral("关闭设备"));
        isLinkSuccess = true;
    }else if(3==flag)   //连接设备失败
    {
        isLinkSuccess = false;
        ui->linkUSB_pushButton->setText(QStringLiteral("连接设备"));
    }
}



//自动校准的窗口
void MainWindow::on_autoCalibration_action_triggered()
{
    autoCal_dia.setModal(true);
    autoCal_dia.show();
}
