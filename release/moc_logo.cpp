/****************************************************************************
** Meta object code from reading C++ file 'logo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../logo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Logo_t {
    QByteArrayData data[16];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Logo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Logo_t qt_meta_stringdata_Logo = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Logo"
QT_MOC_LITERAL(1, 5, 4), // "quad"
QT_MOC_LITERAL(2, 10, 0), // ""
QT_MOC_LITERAL(3, 11, 7), // "GLfloat"
QT_MOC_LITERAL(4, 19, 2), // "x1"
QT_MOC_LITERAL(5, 22, 2), // "y1"
QT_MOC_LITERAL(6, 25, 2), // "x2"
QT_MOC_LITERAL(7, 28, 2), // "y2"
QT_MOC_LITERAL(8, 31, 2), // "x3"
QT_MOC_LITERAL(9, 34, 2), // "y3"
QT_MOC_LITERAL(10, 37, 2), // "x4"
QT_MOC_LITERAL(11, 40, 2), // "y4"
QT_MOC_LITERAL(12, 43, 7), // "extrude"
QT_MOC_LITERAL(13, 51, 3), // "add"
QT_MOC_LITERAL(14, 55, 1), // "v"
QT_MOC_LITERAL(15, 57, 1) // "n"

    },
    "Logo\0quad\0\0GLfloat\0x1\0y1\0x2\0y2\0x3\0y3\0"
    "x4\0y4\0extrude\0add\0v\0n"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Logo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    8,   29,    2, 0x08 /* Private */,
      12,    4,   46,    2, 0x08 /* Private */,
      13,    2,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,    7,    8,    9,   10,   11,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,    7,
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QVector3D,   14,   15,

       0        // eod
};

void Logo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Logo *_t = static_cast<Logo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->quad((*reinterpret_cast< GLfloat(*)>(_a[1])),(*reinterpret_cast< GLfloat(*)>(_a[2])),(*reinterpret_cast< GLfloat(*)>(_a[3])),(*reinterpret_cast< GLfloat(*)>(_a[4])),(*reinterpret_cast< GLfloat(*)>(_a[5])),(*reinterpret_cast< GLfloat(*)>(_a[6])),(*reinterpret_cast< GLfloat(*)>(_a[7])),(*reinterpret_cast< GLfloat(*)>(_a[8]))); break;
        case 1: _t->extrude((*reinterpret_cast< GLfloat(*)>(_a[1])),(*reinterpret_cast< GLfloat(*)>(_a[2])),(*reinterpret_cast< GLfloat(*)>(_a[3])),(*reinterpret_cast< GLfloat(*)>(_a[4]))); break;
        case 2: _t->add((*reinterpret_cast< const QVector3D(*)>(_a[1])),(*reinterpret_cast< const QVector3D(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject Logo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Logo.data,
      qt_meta_data_Logo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Logo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Logo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Logo.stringdata0))
        return static_cast<void*>(const_cast< Logo*>(this));
    return QObject::qt_metacast(_clname);
}

int Logo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
