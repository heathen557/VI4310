#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"globaldata.h"
#include"dealusb_msg.h"



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

signals:
    void change_gain_signal(float);
    void change_tof_peak_signal();
    void isFilter_signal(bool);

private:
    QThread *dealMsg_thread;
    DealUsb_msg *dealMsg_obj;

    QString localFileDirPath;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
