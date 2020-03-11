/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "control_textedit.h"
#include "glwidget.h"
#include "mylabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openFile_action;
    QAction *saveFile_action;
    QAction *statistic_action;
    QAction *pileUp_action;
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    GLWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *tof_peak_change_toolButton;
    QLabel *label;
    QLineEdit *gain_lineEdit;
    QToolButton *front_toolButton;
    QToolButton *side_toolButton;
    QToolButton *down_toolButton;
    QRadioButton *filter_radioButton;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *left_dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *tof_Histogram_pushButton;
    QSpacerItem *horizontalSpacer_4;
    myLabel *tof_label;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    myLabel *peak_label;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *peak_Histogram_pushButton;
    QSpacerItem *horizontalSpacer_6;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_6;
    QToolBox *config_toolBox;
    QWidget *page;
    QPushButton *play_pushButton;
    QWidget *page_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_22;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QSlider *rotate_horizontalSlider;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QSlider *scale_horizontalSlider;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_8;
    QSlider *translate_horizontalSlider;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_23;
    QLabel *label_12;
    QLineEdit *peakOffset_lineEdit;
    QLabel *label_14;
    QLineEdit *averageNum_lineEdit;
    QLabel *label_13;
    QRadioButton *centerShowYes_radioButton;
    QRadioButton *centerShowNo_radioButton;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_4;
    QGridLayout *gridLayout_7;
    Control_textEdit *control_log_textEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1287, 713);
        QIcon icon;
        icon.addFile(QStringLiteral("images/icon_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        openFile_action = new QAction(MainWindow);
        openFile_action->setObjectName(QStringLiteral("openFile_action"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/images/ccOpen.png"), QSize(), QIcon::Normal, QIcon::Off);
        openFile_action->setIcon(icon1);
        saveFile_action = new QAction(MainWindow);
        saveFile_action->setObjectName(QStringLiteral("saveFile_action"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("images/ccSave.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveFile_action->setIcon(icon2);
        statistic_action = new QAction(MainWindow);
        statistic_action->setObjectName(QStringLiteral("statistic_action"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/images/ccHistogram.png"), QSize(), QIcon::Normal, QIcon::Off);
        statistic_action->setIcon(icon3);
        pileUp_action = new QAction(MainWindow);
        pileUp_action->setObjectName(QStringLiteral("pileUp_action"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/images/ccPivotAuto.png"), QSize(), QIcon::Normal, QIcon::Off);
        pileUp_action->setIcon(icon4);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 2);
        widget = new GLWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tof_peak_change_toolButton = new QToolButton(groupBox);
        tof_peak_change_toolButton->setObjectName(QStringLiteral("tof_peak_change_toolButton"));

        horizontalLayout->addWidget(tof_peak_change_toolButton);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        gain_lineEdit = new QLineEdit(groupBox);
        gain_lineEdit->setObjectName(QStringLiteral("gain_lineEdit"));

        horizontalLayout->addWidget(gain_lineEdit);

        front_toolButton = new QToolButton(groupBox);
        front_toolButton->setObjectName(QStringLiteral("front_toolButton"));
        QIcon icon5;
        icon5.addFile(QStringLiteral("images/ccViewYpos.png"), QSize(), QIcon::Normal, QIcon::Off);
        front_toolButton->setIcon(icon5);

        horizontalLayout->addWidget(front_toolButton);

        side_toolButton = new QToolButton(groupBox);
        side_toolButton->setObjectName(QStringLiteral("side_toolButton"));
        QIcon icon6;
        icon6.addFile(QStringLiteral("images/ccViewXneg.png"), QSize(), QIcon::Normal, QIcon::Off);
        side_toolButton->setIcon(icon6);

        horizontalLayout->addWidget(side_toolButton);

        down_toolButton = new QToolButton(groupBox);
        down_toolButton->setObjectName(QStringLiteral("down_toolButton"));
        QIcon icon7;
        icon7.addFile(QStringLiteral("images/ccViewZpos.png"), QSize(), QIcon::Normal, QIcon::Off);
        down_toolButton->setIcon(icon7);

        horizontalLayout->addWidget(down_toolButton);

        filter_radioButton = new QRadioButton(groupBox);
        filter_radioButton->setObjectName(QStringLiteral("filter_radioButton"));

        horizontalLayout->addWidget(filter_radioButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);
        horizontalLayout->setStretch(5, 1);
        horizontalLayout->setStretch(6, 1);
        horizontalLayout->setStretch(7, 1);
        horizontalLayout->setStretch(8, 5);

        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 15);
        gridLayout->setRowStretch(1, 1);

        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1287, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        left_dockWidget = new QDockWidget(MainWindow);
        left_dockWidget->setObjectName(QStringLiteral("left_dockWidget"));
        left_dockWidget->setStyleSheet(QStringLiteral(""));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_4 = new QGridLayout(dockWidgetContents);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox_2 = new QGroupBox(dockWidgetContents);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 3, -1, 2);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        tof_Histogram_pushButton = new QPushButton(groupBox_2);
        tof_Histogram_pushButton->setObjectName(QStringLiteral("tof_Histogram_pushButton"));
        QIcon icon8;
        icon8.addFile(QStringLiteral("images/ccHistogram.png"), QSize(), QIcon::Normal, QIcon::Off);
        tof_Histogram_pushButton->setIcon(icon8);

        horizontalLayout_2->addWidget(tof_Histogram_pushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        tof_label = new myLabel(groupBox_2);
        tof_label->setObjectName(QStringLiteral("tof_label"));
        tof_label->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        tof_label->setScaledContents(true);

        gridLayout_2->addWidget(tof_label, 0, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 9);

        gridLayout_4->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(dockWidgetContents);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 3, -1, 2);
        peak_label = new myLabel(groupBox_3);
        peak_label->setObjectName(QStringLiteral("peak_label"));
        peak_label->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        peak_label->setScaledContents(true);

        gridLayout_3->addWidget(peak_label, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        peak_Histogram_pushButton = new QPushButton(groupBox_3);
        peak_Histogram_pushButton->setObjectName(QStringLiteral("peak_Histogram_pushButton"));
        peak_Histogram_pushButton->setIcon(icon8);

        horizontalLayout_3->addWidget(peak_Histogram_pushButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        gridLayout_3->setRowStretch(0, 9);
        gridLayout_3->setRowStretch(1, 1);

        gridLayout_4->addWidget(groupBox_3, 1, 0, 1, 1);

        left_dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), left_dockWidget);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        gridLayout_6 = new QGridLayout(dockWidgetContents_3);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        config_toolBox = new QToolBox(dockWidgetContents_3);
        config_toolBox->setObjectName(QStringLiteral("config_toolBox"));
        config_toolBox->setMinimumSize(QSize(300, 0));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 300, 433));
        play_pushButton = new QPushButton(page);
        play_pushButton->setObjectName(QStringLiteral("play_pushButton"));
        play_pushButton->setGeometry(QRect(70, 120, 80, 20));
        config_toolBox->addItem(page, QString::fromUtf8("\345\237\272\346\234\254\350\256\276\347\275\256"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 300, 433));
        groupBox_4 = new QGroupBox(page_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(40, 20, 220, 141));
        gridLayout_22 = new QGridLayout(groupBox_4);
        gridLayout_22->setSpacing(6);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QStringLiteral("gridLayout_22"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_9->addWidget(label_7);

        rotate_horizontalSlider = new QSlider(groupBox_4);
        rotate_horizontalSlider->setObjectName(QStringLiteral("rotate_horizontalSlider"));
        rotate_horizontalSlider->setMinimum(1);
        rotate_horizontalSlider->setMaximum(50);
        rotate_horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(rotate_horizontalSlider);


        gridLayout_22->addLayout(horizontalLayout_9, 0, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_10->addWidget(label_10);

        scale_horizontalSlider = new QSlider(groupBox_4);
        scale_horizontalSlider->setObjectName(QStringLiteral("scale_horizontalSlider"));
        scale_horizontalSlider->setMinimum(1);
        scale_horizontalSlider->setMaximum(50);
        scale_horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_10->addWidget(scale_horizontalSlider);


        gridLayout_22->addLayout(horizontalLayout_10, 1, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_13->addWidget(label_8);

        translate_horizontalSlider = new QSlider(groupBox_4);
        translate_horizontalSlider->setObjectName(QStringLiteral("translate_horizontalSlider"));
        translate_horizontalSlider->setMinimum(10);
        translate_horizontalSlider->setMaximum(100);
        translate_horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_13->addWidget(translate_horizontalSlider);


        gridLayout_22->addLayout(horizontalLayout_13, 2, 0, 1, 1);

        groupBox_5 = new QGroupBox(page_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(40, 190, 220, 115));
        gridLayout_23 = new QGridLayout(groupBox_5);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QStringLiteral("gridLayout_23"));
        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_23->addWidget(label_12, 0, 0, 1, 1);

        peakOffset_lineEdit = new QLineEdit(groupBox_5);
        peakOffset_lineEdit->setObjectName(QStringLiteral("peakOffset_lineEdit"));
        peakOffset_lineEdit->setAlignment(Qt::AlignCenter);

        gridLayout_23->addWidget(peakOffset_lineEdit, 0, 1, 1, 2);

        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_23->addWidget(label_14, 1, 0, 1, 1);

        averageNum_lineEdit = new QLineEdit(groupBox_5);
        averageNum_lineEdit->setObjectName(QStringLiteral("averageNum_lineEdit"));
        averageNum_lineEdit->setAlignment(Qt::AlignCenter);

        gridLayout_23->addWidget(averageNum_lineEdit, 1, 1, 1, 2);

        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_23->addWidget(label_13, 2, 0, 1, 1);

        centerShowYes_radioButton = new QRadioButton(groupBox_5);
        centerShowYes_radioButton->setObjectName(QStringLiteral("centerShowYes_radioButton"));

        gridLayout_23->addWidget(centerShowYes_radioButton, 2, 1, 1, 1);

        centerShowNo_radioButton = new QRadioButton(groupBox_5);
        centerShowNo_radioButton->setObjectName(QStringLiteral("centerShowNo_radioButton"));
        centerShowNo_radioButton->setChecked(true);

        gridLayout_23->addWidget(centerShowNo_radioButton, 2, 2, 1, 1);

        config_toolBox->addItem(page_2, QString::fromUtf8("\346\230\276\347\244\272\350\256\276\347\275\256"));

        gridLayout_6->addWidget(config_toolBox, 0, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);
        dockWidget_2 = new QDockWidget(MainWindow);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        gridLayout_7 = new QGridLayout(dockWidgetContents_4);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        control_log_textEdit = new Control_textEdit(dockWidgetContents_4);
        control_log_textEdit->setObjectName(QStringLiteral("control_log_textEdit"));
        control_log_textEdit->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_7->addWidget(control_log_textEdit, 0, 0, 1, 1);

        dockWidget_2->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_2);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(openFile_action);
        menu->addAction(saveFile_action);
        menu_2->addAction(statistic_action);
        menu_3->addAction(pileUp_action);
        mainToolBar->addAction(openFile_action);
        mainToolBar->addAction(saveFile_action);
        mainToolBar->addAction(statistic_action);
        mainToolBar->addAction(pileUp_action);

        retranslateUi(MainWindow);

        config_toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "VI4310_Demo(v0.1)", Q_NULLPTR));
        openFile_action->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\234\254\345\234\260\346\226\207\344\273\266", Q_NULLPTR));
        saveFile_action->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\226\207\344\273\266", Q_NULLPTR));
        statistic_action->setText(QApplication::translate("MainWindow", "\347\273\237\350\256\241\344\277\241\346\201\257", Q_NULLPTR));
        pileUp_action->setText(QApplication::translate("MainWindow", "\347\233\270\346\234\272\346\240\241\346\255\243", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "3D\347\202\271\344\272\221\357\274\232", Q_NULLPTR));
        tof_peak_change_toolButton->setText(QApplication::translate("MainWindow", "tof/peak", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\242\236\347\233\212\357\274\232", Q_NULLPTR));
        gain_lineEdit->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        front_toolButton->setText(QApplication::translate("MainWindow", "front", Q_NULLPTR));
        side_toolButton->setText(QApplication::translate("MainWindow", "side", Q_NULLPTR));
        down_toolButton->setText(QApplication::translate("MainWindow", "down", Q_NULLPTR));
        filter_radioButton->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\350\260\203\350\257\225", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\346\267\261\345\272\246\345\233\276(tof)\357\274\232", Q_NULLPTR));
        tof_Histogram_pushButton->setText(QApplication::translate("MainWindow", "\347\233\264\346\226\271\345\233\276", Q_NULLPTR));
        tof_label->setText(QString());
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\345\274\272\345\272\246\345\233\276(peak)\357\274\232", Q_NULLPTR));
        peak_label->setText(QString());
        peak_Histogram_pushButton->setText(QApplication::translate("MainWindow", "\347\233\264\346\226\271\345\233\276", Q_NULLPTR));
        play_pushButton->setText(QApplication::translate("MainWindow", "play", Q_NULLPTR));
        config_toolBox->setItemText(config_toolBox->indexOf(page), QApplication::translate("MainWindow", "\345\237\272\346\234\254\350\256\276\347\275\256", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "3D\351\274\240\346\240\207\350\256\276\347\275\256\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "\346\227\213\350\275\254\350\247\222\345\272\246\357\274\232", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "\347\274\251\346\224\276\346\257\224\344\276\213\357\274\232", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "\346\213\226\345\212\250\346\257\224\344\276\213\357\274\232", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "\346\230\276\347\244\272\350\256\276\347\275\256\357\274\232", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "  peak\346\230\276\347\244\272\351\230\210\345\200\274\357\274\232", Q_NULLPTR));
        peakOffset_lineEdit->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "      \345\271\263\345\235\207\345\270\247\346\225\260\357\274\232", Q_NULLPTR));
        averageNum_lineEdit->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "\345\217\252\346\230\276\347\244\272\344\270\255\345\277\203\345\214\272\345\237\237\357\274\232", Q_NULLPTR));
        centerShowYes_radioButton->setText(QApplication::translate("MainWindow", "\346\230\257", Q_NULLPTR));
        centerShowNo_radioButton->setText(QApplication::translate("MainWindow", "\345\220\246", Q_NULLPTR));
        config_toolBox->setItemText(config_toolBox->indexOf(page_2), QApplication::translate("MainWindow", "\346\230\276\347\244\272\350\256\276\347\275\256", Q_NULLPTR));
        dockWidget_2->setWindowTitle(QApplication::translate("MainWindow", "\344\277\241\346\201\257\347\233\221\346\216\247\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
