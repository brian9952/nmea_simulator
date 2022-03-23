/****************************************************************************
** Meta object code from reading C++ file 'RangeSlider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "libs/RangeSlider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RangeSlider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RangeSlider_t {
    QByteArrayData data[15];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RangeSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RangeSlider_t qt_meta_stringdata_RangeSlider = {
    {
QT_MOC_LITERAL(0, 0, 11), // "RangeSlider"
QT_MOC_LITERAL(1, 12, 17), // "lowerValueChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 11), // "aLowerValue"
QT_MOC_LITERAL(4, 43, 17), // "upperValueChanged"
QT_MOC_LITERAL(5, 61, 11), // "aUpperValue"
QT_MOC_LITERAL(6, 73, 12), // "rangeChanged"
QT_MOC_LITERAL(7, 86, 4), // "aMin"
QT_MOC_LITERAL(8, 91, 4), // "aMax"
QT_MOC_LITERAL(9, 96, 13), // "setLowerValue"
QT_MOC_LITERAL(10, 110, 13), // "setUpperValue"
QT_MOC_LITERAL(11, 124, 10), // "setMinimum"
QT_MOC_LITERAL(12, 135, 8), // "aMinimum"
QT_MOC_LITERAL(13, 144, 10), // "setMaximum"
QT_MOC_LITERAL(14, 155, 8) // "aMaximum"

    },
    "RangeSlider\0lowerValueChanged\0\0"
    "aLowerValue\0upperValueChanged\0aUpperValue\0"
    "rangeChanged\0aMin\0aMax\0setLowerValue\0"
    "setUpperValue\0setMinimum\0aMinimum\0"
    "setMaximum\0aMaximum"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RangeSlider[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       6,    2,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   60,    2, 0x0a /* Public */,
      10,    1,   63,    2, 0x0a /* Public */,
      11,    1,   66,    2, 0x0a /* Public */,
      13,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,

 // enums: name, alias, flags, count, data

 // enum data: key, value

       0        // eod
};

void RangeSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RangeSlider *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->lowerValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->upperValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->rangeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setLowerValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setUpperValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setMinimum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setMaximum((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RangeSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RangeSlider::lowerValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RangeSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RangeSlider::upperValueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RangeSlider::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RangeSlider::rangeChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RangeSlider::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_RangeSlider.data,
    qt_meta_data_RangeSlider,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RangeSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RangeSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RangeSlider.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RangeSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void RangeSlider::lowerValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RangeSlider::upperValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RangeSlider::rangeChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
