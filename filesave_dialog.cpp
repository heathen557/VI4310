#include "filesave_dialog.h"
#include "ui_filesave_dialog.h"

fileSave_Dialog::fileSave_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileSave_Dialog)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);

}

fileSave_Dialog::~fileSave_Dialog()
{
    delete ui;
}


//!
//! \brief fileSave_Dialog::on_SelFilePath_pushButton_clicked
//!  选出一个文件路径
void fileSave_Dialog::on_SelFilePath_pushButton_clicked()
{
    file_path = QFileDialog::getExistingDirectory(this,QStringLiteral("请选择文件保存路径..."),"./");
    if(file_path.isEmpty())
    {
       qDebug()<<QStringLiteral("没有选择路径")<<endl;
       QMessageBox::information(NULL,QStringLiteral("告警"),QStringLiteral("保存路径不能为空"));
        return;
    }
    else
    {
        file_path.append("/");
        qDebug() << file_path << endl;
        ui->lineEdit->setText(file_path);
    }
}

//!
//! \brief fileSave_Dialog::on_start_saveFile_pushButton_clicked
//!开始保存槽函数
void fileSave_Dialog::on_start_saveFile_pushButton_clicked()
{
    if(!file_path.isEmpty())
    {
        emit isSaveFlagSignal(true,file_path,0);
        this->hide();
    }else
    {
        QMessageBox::information(NULL,QStringLiteral("告警"),QStringLiteral("保存路径不能为空"));
    }


}

//!
//! \brief fileSave_Dialog::on_cancel_save_pushButton_clicked
//!取消保存 槽函数
void fileSave_Dialog::on_cancel_save_pushButton_clicked()
{
    emit isSaveFlagSignal(false,file_path,0);
    this->hide();
}
