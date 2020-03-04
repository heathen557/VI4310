#include "mainwindow.h"
#include "ui_mainwindow.h"

//是否显示 直方图统计功能,切换tof/peak的按钮
#define SHOW_HISTORGRAM_BUTTON
//#define SHOW_TOF_PEAK_BUTTON

using namespace std;
extern QMutex mutex;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
//!播放图像的槽函数
void MainWindow::on_play_pushButton_clicked()
{
    if(ui->play_pushButton->text() == "play")
    {
        ui->widget->show3D_timer.start(90);
        ui->play_pushButton->setText("pause");
    }else
    {
        ui->widget->show3D_timer.stop();
        ui->play_pushButton->setText("play");
    }
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


MainWindow::~MainWindow()
{
    delete ui;
}
