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
    QByteArrayData data[20];
    char stringdata0[466];
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
QT_MOC_LITERAL(5, 70, 16), // "Display_log_slot"
QT_MOC_LITERAL(6, 87, 3), // "str"
QT_MOC_LITERAL(7, 91, 28), // "on_openFile_action_triggered"
QT_MOC_LITERAL(8, 120, 26), // "on_play_pushButton_clicked"
QT_MOC_LITERAL(9, 147, 37), // "on_tof_peak_change_toolButton..."
QT_MOC_LITERAL(10, 185, 30), // "on_gain_lineEdit_returnPressed"
QT_MOC_LITERAL(11, 216, 29), // "on_filter_radioButton_clicked"
QT_MOC_LITERAL(12, 246, 29), // "on_statistic_action_triggered"
QT_MOC_LITERAL(13, 276, 28), // "on_saveFile_action_triggered"
QT_MOC_LITERAL(14, 305, 14), // "isSaveFlagSlot"
QT_MOC_LITERAL(15, 320, 38), // "on_rotate_horizontalSlider_sl..."
QT_MOC_LITERAL(16, 359, 8), // "position"
QT_MOC_LITERAL(17, 368, 37), // "on_scale_horizontalSlider_sli..."
QT_MOC_LITERAL(18, 406, 41), // "on_translate_horizontalSlider..."
QT_MOC_LITERAL(19, 448, 17) // "save3DSettingFile"

    },
    "MainWindow\0change_gain_signal\0\0"
    "change_tof_peak_signal\0isFilter_signal\0"
    "Display_log_slot\0str\0on_openFile_action_triggered\0"
    "on_play_pushButton_clicked\0"
    "on_tof_peak_change_toolButton_clicked\0"
    "on_gain_lineEdit_returnPressed\0"
    "on_filter_radioButton_clicked\0"
    "on_statistic_action_triggered\0"
    "on_saveFile_action_triggered\0"
    "isSaveFlagSlot\0on_rotate_horizontalSlider_sliderMoved\0"
    "position\0on_scale_horizontalSlider_sliderMoved\0"
    "on_translate_horizontalSlider_sliderMoved\0"
    "save3DSettingFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       3,    0,   97,    2, 0x06 /* Public */,
       4,    1,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,  101,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    3,  111,    2, 0x08 /* Private */,
      15,    1,  118,    2, 0x08 /* Private */,
      17,    1,  121,    2, 0x08 /* Private */,
      18,    1,  124,    2, 0x08 /* Private */,
      19,    0,  127,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,

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
        case 3: _t->Display_log_slot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->on_openFile_action_triggered(); break;
        case 5: _t->on_play_pushButton_clicked(); break;
        case 6: _t->on_tof_peak_change_toolButton_clicked(); break;
        case 7: _t->on_gain_lineEdit_returnPressed(); break;
        case 8: _t->on_filter_radioButton_clicked(); break;
        case 9: _t->on_statistic_action_triggered(); break;
        case 10: _t->on_saveFile_action_triggered(); break;
        case 11: _t->isSaveFlagSlot((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: _t->on_rotate_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_scale_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_translate_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->save3DSettingFile(); break;
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
