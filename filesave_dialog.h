#ifndef FILESAVE_DIALOG_H
#define FILESAVE_DIALOG_H

#include"globaldata.h"
#include <QDialog>

namespace Ui {
class fileSave_Dialog;
}

class fileSave_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit fileSave_Dialog(QWidget *parent = 0);
    ~fileSave_Dialog();

private slots:
    void on_SelFilePath_pushButton_clicked();

    void on_start_saveFile_pushButton_clicked();

    void on_cancel_save_pushButton_clicked();

signals:
    void isSaveFlagSignal(bool,QString,int);       //是否保存标识；存储路径；文件类型（预留）

private:
    Ui::fileSave_Dialog *ui;

    QString file_path;
};

#endif // FILESAVE_DIALOG_H
