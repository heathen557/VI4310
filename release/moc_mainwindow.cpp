/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[41];
    char stringdata0[958];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "change_gain_signal"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 22), // "change_tof_peak_signal"
QT_MOC_LITERAL(4, 54, 15), // "isFilter_signal"
QT_MOC_LITERAL(5, 70, 15), // "openLink_signal"
QT_MOC_LITERAL(6, 86, 15), // "closeLinkSignal"
QT_MOC_LITERAL(7, 102, 13), // "readSysSignal"
QT_MOC_LITERAL(8, 116, 14), // "writeSysSignal"
QT_MOC_LITERAL(9, 131, 17), // "loadSettingSignal"
QT_MOC_LITERAL(10, 149, 21), // "start_read_usb_signal"
QT_MOC_LITERAL(11, 171, 16), // "Display_log_slot"
QT_MOC_LITERAL(12, 188, 3), // "str"
QT_MOC_LITERAL(13, 192, 28), // "on_openFile_action_triggered"
QT_MOC_LITERAL(14, 221, 26), // "on_play_pushButton_clicked"
QT_MOC_LITERAL(15, 248, 21), // "show_image_timer_slot"
QT_MOC_LITERAL(16, 270, 27), // "queryPixel_showToolTip_slot"
QT_MOC_LITERAL(17, 298, 1), // "x"
QT_MOC_LITERAL(18, 300, 1), // "y"
QT_MOC_LITERAL(19, 302, 37), // "on_tof_peak_change_toolButton..."
QT_MOC_LITERAL(20, 340, 30), // "on_gain_lineEdit_returnPressed"
QT_MOC_LITERAL(21, 371, 29), // "on_filter_radioButton_clicked"
QT_MOC_LITERAL(22, 401, 29), // "on_statistic_action_triggered"
QT_MOC_LITERAL(23, 431, 28), // "on_saveFile_action_triggered"
QT_MOC_LITERAL(24, 460, 14), // "isSaveFlagSlot"
QT_MOC_LITERAL(25, 475, 38), // "on_rotate_horizontalSlider_sl..."
QT_MOC_LITERAL(26, 514, 8), // "position"
QT_MOC_LITERAL(27, 523, 37), // "on_scale_horizontalSlider_sli..."
QT_MOC_LITERAL(28, 561, 41), // "on_translate_horizontalSlider..."
QT_MOC_LITERAL(29, 603, 17), // "save3DSettingFile"
QT_MOC_LITERAL(30, 621, 36), // "on_peakOffset_lineEdit_return..."
QT_MOC_LITERAL(31, 658, 36), // "on_averageNum_lineEdit_return..."
QT_MOC_LITERAL(32, 695, 36), // "on_centerShowYes_radioButton_..."
QT_MOC_LITERAL(33, 732, 35), // "on_centerShowNo_radioButton_c..."
QT_MOC_LITERAL(34, 768, 29), // "on_linkUSB_pushButton_clicked"
QT_MOC_LITERAL(35, 798, 29), // "on_readSys_pushButton_clicked"
QT_MOC_LITERAL(36, 828, 13), // "reReadSysSlot"
QT_MOC_LITERAL(37, 842, 30), // "on_writeSys_pushButton_clicked"
QT_MOC_LITERAL(38, 873, 33), // "on_loadSetting_pushButton_cli..."
QT_MOC_LITERAL(39, 907, 33), // "on_saveSetting_pushButton_cli..."
QT_MOC_LITERAL(40, 941, 16) // "USB_linkInfoSlot"

    },
    "MainWindow\0change_gain_signal\0\0"
    "change_tof_peak_signal\0isFilter_signal\0"
    "openLink_signal\0closeLinkSignal\0"
    "readSysSignal\0writeSysSignal\0"
    "loadSettingSignal\0start_read_usb_signal\0"
    "Display_log_slot\0str\0on_openFile_action_triggered\0"
    "on_play_pushButton_clicked\0"
    "show_image_timer_slot\0queryPixel_showToolTip_slot\0"
    "x\0y\0on_tof_peak_change_toolButton_clicked\0"
    "on_gain_lineEdit_returnPressed\0"
    "on_filter_radioButton_clicked\0"
    "on_statistic_action_triggered\0"
    "on_saveFile_action_triggered\0"
    "isSaveFlagSlot\0on_rotate_horizontalSlider_sliderMoved\0"
    "position\0on_scale_horizontalSlider_sliderMoved\0"
    "on_translate_horizontalSlider_sliderMoved\0"
    "save3DSettingFile\0"
    "on_peakOffset_lineEdit_returnPressed\0"
    "on_averageNum_lineEdit_returnPressed\0"
    "on_centerShowYes_radioButton_clicked\0"
    "on_centerShowNo_radioButton_clicked\0"
    "on_linkUSB_pushButton_clicked\0"
    "on_readSys_pushButton_clicked\0"
    "reReadSysSlot\0on_writeSys_pushButton_clicked\0"
    "on_loadSetting_pushButton_clicked\0"
    "on_saveSetting_pushButton_clicked\0"
    "USB_linkInfoSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  189,    2, 0x06 /* Public */,
       3,    0,  192,    2, 0x06 /* Public */,
       4,    1,  193,    2, 0x06 /* Public */,
       5,    2,  196,    2, 0x06 /* Public */,
       6,    0,  201,    2, 0x06 /* Public */,
       7,    2,  202,    2, 0x06 /* Public */,
       8,    3,  207,    2, 0x06 /* Public */,
       9,    2,  214,    2, 0x06 /* Public */,
      10,    0,  219,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,  220,    2, 0x08 /* Private */,
      13,    0,  223,    2, 0x08 /* Private */,
      14,    0,  224,    2, 0x08 /* Private */,
      15,    0,  225,    2, 0x08 /* Private */,
      16,    2,  226,    2, 0x08 /* Private */,
      19,    0,  231,    2, 0x08 /* Private */,
      20,    0,  232,    2, 0x08 /* Private */,
      21,    0,  233,    2, 0x08 /* Private */,
      22,    0,  234,    2, 0x08 /* Private */,
      23,    0,  235,    2, 0x08 /* Private */,
      24,    3,  236,    2, 0x08 /* Private */,
      25,    1,  243,    2, 0x08 /* Private */,
      27,    1,  246,    2, 0x08 /* Private */,
      28,    1,  249,    2, 0x08 /* Private */,
      29,    0,  252,    2, 0x08 /* Private */,
      30,    0,  253,    2, 0x08 /* Private */,
      31,    0,  254,    2, 0x08 /* Private */,
      32,    0,  255,    2, 0x08 /* Private */,
      33,    0,  256,    2, 0x08 /* Private */,
      34,    0,  257,    2, 0x08 /* Private */,
      35,    0,  258,    2, 0x08 /* Private */,
      36,    1,  259,    2, 0x08 /* Private */,
      37,    0,  262,    2, 0x08 /* Private */,
      38,    0,  263,    2, 0x08 /* Private */,
      39,    0,  264,    2, 0x08 /* Private */,
      40,    1,  265,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Bool,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change_gain_signal((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->change_tof_peak_signal(); break;
        case 2: _t->isFilter_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->openLink_signal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->closeLinkSignal(); break;
        case 5: _t->readSysSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->writeSysSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 7: _t->loadSettingSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->start_read_usb_signal(); break;
        case 9: _t->Display_log_slot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->on_openFile_action_triggered(); break;
        case 11: _t->on_play_pushButton_clicked(); break;
        case 12: _t->show_image_timer_slot(); break;
        case 13: _t->queryPixel_showToolTip_slot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->on_tof_peak_change_toolButton_clicked(); break;
        case 15: _t->on_gain_lineEdit_returnPressed(); break;
        case 16: _t->on_filter_radioButton_clicked(); break;
        case 17: _t->on_statistic_action_triggered(); break;
        case 18: _t->on_saveFile_action_triggered(); break;
        case 19: _t->isSaveFlagSlot((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 20: _t->on_rotate_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->on_scale_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->on_translate_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->save3DSettingFile(); break;
        case 24: _t->on_peakOffset_lineEdit_returnPressed(); break;
        case 25: _t->on_averageNum_lineEdit_returnPressed(); break;
        case 26: _t->on_centerShowYes_radioButton_clicked(); break;
        case 27: _t->on_centerShowNo_radioButton_clicked(); break;
        case 28: _t->on_linkUSB_pushButton_clicked(); break;
        case 29: _t->on_readSys_pushButton_clicked(); break;
        case 30: _t->reReadSysSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 31: _t->on_writeSys_pushButton_clicked(); break;
        case 32: _t->on_loadSetting_pushButton_clicked(); break;
        case 33: _t->on_saveSetting_pushButton_clicked(); break;
        case 34: _t->USB_linkInfoSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::change_gain_signal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::change_tof_peak_signal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::isFilter_signal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::openLink_signal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::closeLinkSignal)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::readSysSignal)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(int , QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::writeSysSignal)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::loadSettingSignal)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::start_read_usb_signal)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 35;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::change_gain_signal(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::change_tof_peak_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MainWindow::isFilter_signal(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::openLink_signal(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::closeLinkSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void MainWindow::readSysSignal(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::writeSysSignal(int _t1, QString _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::loadSettingSignal(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::start_read_usb_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
