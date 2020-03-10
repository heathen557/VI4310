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

    void on_play_pushButton_clicked();   //播放 3D

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

signals:
    void change_gain_signal(float);
    void change_tof_peak_signal();
    void isFilter_signal(bool);

private:
    QThread *dealMsg_thread;      //数据处理线程
    DealUsb_msg *dealMsg_obj;

    QThread *savePcd_thread;      //文件保存线程
    savePCDThread* savePcd_obj;

    calMeanStdThread *calMeanStd_obj; //
    QThread *calThread;

    QString localFileDirPath;    //本地播放文件

    statisticsDialog  statisticsDia_; //统计信息界面

    fileSave_Dialog fileSave_dia;




    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
