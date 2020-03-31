/****************************************************************************
** Meta object code from reading C++ file 'layerelementcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "layerelementcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'layerelementcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LayerElementController_t {
    QByteArrayData data[8];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LayerElementController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LayerElementController_t qt_meta_stringdata_LayerElementController = {
    {
QT_MOC_LITERAL(0, 0, 22), // "LayerElementController"
QT_MOC_LITERAL(1, 23, 13), // "heightChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 11), // "std::string"
QT_MOC_LITERAL(4, 50, 2), // "id"
QT_MOC_LITERAL(5, 53, 5), // "value"
QT_MOC_LITERAL(6, 59, 12), // "widthChanged"
QT_MOC_LITERAL(7, 72, 16) // "roughnessChanged"

    },
    "LayerElementController\0heightChanged\0"
    "\0std::string\0id\0value\0widthChanged\0"
    "roughnessChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LayerElementController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       6,    2,   34,    2, 0x06 /* Public */,
       7,    2,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,    5,

       0        // eod
};

void LayerElementController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LayerElementController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->heightChanged((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->widthChanged((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->roughnessChanged((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LayerElementController::*)(std::string , double ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayerElementController::heightChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LayerElementController::*)(std::string , double ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayerElementController::widthChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LayerElementController::*)(std::string , double ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayerElementController::roughnessChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LayerElementController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LayerElementController.data,
    qt_meta_data_LayerElementController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LayerElementController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LayerElementController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LayerElementController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LayerElementController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void LayerElementController::heightChanged(std::string _t1, double _t2)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(const_cast< LayerElementController *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LayerElementController::widthChanged(std::string _t1, double _t2)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(const_cast< LayerElementController *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LayerElementController::roughnessChanged(std::string _t1, double _t2)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(const_cast< LayerElementController *>(this), &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
