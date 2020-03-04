/****************************************************************************
** Meta object code from reading C++ file 'dealusb_msg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dealusb_msg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dealusb_msg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DealUsb_msg_t {
    QByteArrayData data[20];
    char stringdata0[283];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DealUsb_msg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DealUsb_msg_t qt_meta_stringdata_DealUsb_msg = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DealUsb_msg"
QT_MOC_LITERAL(1, 12, 17), // "staticValueSignal"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 13), // "savePCDSignal"
QT_MOC_LITERAL(4, 45, 33), // "pcl::PointCloud<pcl::PointXYZ..."
QT_MOC_LITERAL(5, 79, 13), // "saveTXTSignal"
QT_MOC_LITERAL(6, 93, 18), // "Display_log_signal"
QT_MOC_LITERAL(7, 112, 3), // "str"
QT_MOC_LITERAL(8, 116, 14), // "loadLocalArray"
QT_MOC_LITERAL(9, 131, 11), // "recvMsgSlot"
QT_MOC_LITERAL(10, 143, 5), // "array"
QT_MOC_LITERAL(11, 149, 13), // "isFilter_slot"
QT_MOC_LITERAL(12, 163, 7), // "isFiter"
QT_MOC_LITERAL(13, 171, 27), // "alterStatisticFrameNum_slot"
QT_MOC_LITERAL(14, 199, 3), // "num"
QT_MOC_LITERAL(15, 203, 16), // "readLocalPCDFile"
QT_MOC_LITERAL(16, 220, 18), // "playLocalFile_slot"
QT_MOC_LITERAL(17, 239, 5), // "sPath"
QT_MOC_LITERAL(18, 245, 16), // "change_gain_slot"
QT_MOC_LITERAL(19, 262, 20) // "change_tof_peak_slot"

    },
    "DealUsb_msg\0staticValueSignal\0\0"
    "savePCDSignal\0pcl::PointCloud<pcl::PointXYZRGB>\0"
    "saveTXTSignal\0Display_log_signal\0str\0"
    "loadLocalArray\0recvMsgSlot\0array\0"
    "isFilter_slot\0isFiter\0alterStatisticFrameNum_slot\0"
    "num\0readLocalPCDFile\0playLocalFile_slot\0"
    "sPath\0change_gain_slot\0change_tof_peak_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DealUsb_msg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,   10,   74,    2, 0x06 /* Public */,
       3,    2,   95,    2, 0x06 /* Public */,
       5,    1,  100,    2, 0x06 /* Public */,
       6,    1,  103,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  106,    2, 0x0a /* Public */,
       9,    1,  107,    2, 0x0a /* Public */,
      11,    1,  110,    2, 0x0a /* Public */,
      13,    1,  113,    2, 0x0a /* Public */,
      15,    0,  116,    2, 0x0a /* Public */,
      16,    1,  117,    2, 0x0a /* Public */,
      18,    1,  120,    2, 0x0a /* Public */,
      19,    0,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void,

       0        // eod
};

void DealUsb_msg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DealUsb_msg *_t = static_cast<DealUsb_msg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->staticValueSignal((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6])),(*reinterpret_cast< float(*)>(_a[7])),(*reinterpret_cast< float(*)>(_a[8])),(*reinterpret_cast< float(*)>(_a[9])),(*reinterpret_cast< float(*)>(_a[10]))); break;
        case 1: _t->savePCDSignal((*reinterpret_cast< pcl::PointCloud<pcl::PointXYZRGB>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->saveTXTSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->Display_log_signal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->loadLocalArray(); break;
        case 5: _t->recvMsgSlot((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: _t->isFilter_slot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->alterStatisticFrameNum_slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->readLocalPCDFile(); break;
        case 9: _t->playLocalFile_slot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->change_gain_slot((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->change_tof_peak_slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DealUsb_msg::*_t)(float , float , float , float , float , float , float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DealUsb_msg::staticValueSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DealUsb_msg::*_t)(pcl::PointCloud<pcl::PointXYZRGB> , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DealUsb_msg::savePCDSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DealUsb_msg::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DealUsb_msg::saveTXTSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DealUsb_msg::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DealUsb_msg::Display_log_signal)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject DealUsb_msg::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DealUsb_msg.data,
      qt_meta_data_DealUsb_msg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DealUsb_msg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DealUsb_msg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DealUsb_msg.stringdata0))
        return static_cast<void*>(const_cast< DealUsb_msg*>(this));
    return QObject::qt_metacast(_clname);
}

int DealUsb_msg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void DealUsb_msg::staticValueSignal(float _t1, float _t2, float _t3, float _t4, float _t5, float _t6, float _t7, float _t8, float _t9, float _t10)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)), const_cast<void*>(reinterpret_cast<const void*>(&_t10)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DealUsb_msg::savePCDSignal(pcl::PointCloud<pcl::PointXYZRGB> _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DealUsb_msg::saveTXTSignal(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DealUsb_msg::Display_log_signal(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
