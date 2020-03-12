#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"globaldata.h"
#include"dealusb_msg.h"
#include"savepcdthread.h"
#include"statisticsdialog.h"
#include"filesave_dialog.h"
#include"savepcdthread.h"
#include"calmeanstdthread.h"
#include"receusb_msg.h"



namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init_thread();    //线程的初始化
    void init_connect();   //信号与槽的初始化
    void load_ini_file();   //加载配置文件

private slots:

    void Display_log_slot(QString str);  //打印日志信息到控制信息输出窗口的槽函数

    void on_openFile_action_triggered();  //打开 本地文件TOF\PEAK

    void on_play_pushButton_clicked();   //播放 3D、2D  ，打开相关的定时器

    void show_image_timer_slot();       //播放2D图像的槽函数

    void queryPixel_showToolTip_slot(int x,int y);  //鼠标停靠处显示TOF 和 peak信息

    void on_tof_peak_change_toolButton_clicked();

    void on_gain_lineEdit_returnPressed();

    void on_filter_radioButton_clicked();

    void on_statistic_action_triggered();

    void on_saveFile_action_triggered();

    void isSaveFlagSlot(bool,QString,int);       //是否保存标识；存储路径；文件类型（预留）

    void on_rotate_horizontalSlider_sliderMoved(int position);    //旋转

    void on_scale_horizontalSlider_sliderMoved(int position);     //缩放

    void on_translate_horizontalSlider_sliderMoved(int position); //平移

    void save3DSettingFile();

    void on_peakOffset_lineEdit_returnPressed();

    void on_averageNum_lineEdit_returnPressed();

    void on_centerShowYes_radioButton_clicked();

    void on_centerShowNo_radioButton_clicked();




  /////////////////  /**  USB 设备读写相关** * /////////////////////
    void on_linkUSB_pushButton_clicked();

    void on_readSys_pushButton_clicked();

    void reReadSysSlot(QString str);    //读取sys的返回结果

    void on_writeSys_pushButton_clicked();

    void on_loadSetting_pushButton_clicked();

    void on_saveSetting_pushButton_clicked();

    void USB_linkInfoSlot(int );

signals:
    void change_gain_signal(float);
    void change_tof_peak_signal();
    void isFilter_signal(bool);


    /***********USB 设备读写相关************/
    void openLink_signal(int,int);
    void closeLinkSignal();
    void readSysSignal(int,bool);
    void writeSysSignal(int,QString,bool);
    void loadSettingSignal(QString,bool);   //加载配置集
    void start_read_usb_signal();

private:
    QThread *dealMsg_thread;           //数据处理线程
    DealUsb_msg *dealMsg_obj;

    QThread *savePcd_thread;           //文件保存线程
    savePCDThread* savePcd_obj;

    QThread *calThread;
    calMeanStdThread *calMeanStd_obj; //计算均值、方差线程相关

    QThread *recvUsb_thread;
    ReceUSB_Msg *recvUsbMsg_obj;      //接收USB 数据相关线程

    QString localFileDirPath;           //本地播放文件
    statisticsDialog  statisticsDia_; //统计信息界面
    fileSave_Dialog fileSave_dia;     //文件保存界面
    QTimer show_image_timer;         //2D图像显示的定时器


    /**********USB 连接信息相关****************/
    bool isLinkSuccess;


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
