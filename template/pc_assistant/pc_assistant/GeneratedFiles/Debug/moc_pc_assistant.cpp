/****************************************************************************
** Meta object code from reading C++ file 'pc_assistant.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pc_assistant.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pc_assistant.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_pc_assistant_t {
    QByteArrayData data[11];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pc_assistant_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pc_assistant_t qt_meta_stringdata_pc_assistant = {
    {
QT_MOC_LITERAL(0, 0, 12), // "pc_assistant"
QT_MOC_LITERAL(1, 13, 27), // "signal_on_rec_serial_packet"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 13), // "Serial_packet"
QT_MOC_LITERAL(4, 56, 13), // "serial_packet"
QT_MOC_LITERAL(5, 70, 19), // "slot_on_click_start"
QT_MOC_LITERAL(6, 90, 22), // "slot_on_serial_timeout"
QT_MOC_LITERAL(7, 113, 22), // "slot_on_packet_timeout"
QT_MOC_LITERAL(8, 136, 20), // "init_signal_and_slot"
QT_MOC_LITERAL(9, 157, 18), // "on_serial_callback"
QT_MOC_LITERAL(10, 176, 6) // "packet"

    },
    "pc_assistant\0signal_on_rec_serial_packet\0"
    "\0Serial_packet\0serial_packet\0"
    "slot_on_click_start\0slot_on_serial_timeout\0"
    "slot_on_packet_timeout\0init_signal_and_slot\0"
    "on_serial_callback\0packet"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pc_assistant[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,
       8,    0,   50,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,   10,

       0        // eod
};

void pc_assistant::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pc_assistant *_t = static_cast<pc_assistant *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_on_rec_serial_packet((*reinterpret_cast< Serial_packet(*)>(_a[1]))); break;
        case 1: _t->slot_on_click_start(); break;
        case 2: _t->slot_on_serial_timeout(); break;
        case 3: _t->slot_on_packet_timeout(); break;
        case 4: _t->init_signal_and_slot(); break;
        case 5: _t->on_serial_callback((*reinterpret_cast< Serial_packet(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (pc_assistant::*_t)(Serial_packet );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&pc_assistant::signal_on_rec_serial_packet)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject pc_assistant::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_pc_assistant.data,
      qt_meta_data_pc_assistant,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *pc_assistant::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pc_assistant::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_pc_assistant.stringdata0))
        return static_cast<void*>(const_cast< pc_assistant*>(this));
    if (!strcmp(_clname, "Serial_service"))
        return static_cast< Serial_service*>(const_cast< pc_assistant*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int pc_assistant::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void pc_assistant::signal_on_rec_serial_packet(Serial_packet _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
