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
    QByteArrayData data[17];
    char stringdata0[301];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pc_assistant_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pc_assistant_t qt_meta_stringdata_pc_assistant = {
    {
QT_MOC_LITERAL(0, 0, 12), // "pc_assistant"
QT_MOC_LITERAL(1, 13, 27), // "signal_on_refresh_mcu_state"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 10), // "MCU_STATE*"
QT_MOC_LITERAL(4, 53, 9), // "mcu_state"
QT_MOC_LITERAL(5, 63, 28), // "signal_on_send_serial_packet"
QT_MOC_LITERAL(6, 92, 14), // "Serial_packet*"
QT_MOC_LITERAL(7, 107, 6), // "packet"
QT_MOC_LITERAL(8, 114, 19), // "slot_on_click_start"
QT_MOC_LITERAL(9, 134, 22), // "slot_on_serial_timeout"
QT_MOC_LITERAL(10, 157, 22), // "slot_on_packet_timeout"
QT_MOC_LITERAL(11, 180, 25), // "slot_on_refresh_mcu_state"
QT_MOC_LITERAL(12, 206, 13), // "serial_packet"
QT_MOC_LITERAL(13, 220, 26), // "slot_on_send_serial_packet"
QT_MOC_LITERAL(14, 247, 20), // "init_signal_and_slot"
QT_MOC_LITERAL(15, 268, 18), // "on_serial_callback"
QT_MOC_LITERAL(16, 287, 13) // "Serial_packet"

    },
    "pc_assistant\0signal_on_refresh_mcu_state\0"
    "\0MCU_STATE*\0mcu_state\0"
    "signal_on_send_serial_packet\0"
    "Serial_packet*\0packet\0slot_on_click_start\0"
    "slot_on_serial_timeout\0slot_on_packet_timeout\0"
    "slot_on_refresh_mcu_state\0serial_packet\0"
    "slot_on_send_serial_packet\0"
    "init_signal_and_slot\0on_serial_callback\0"
    "Serial_packet"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pc_assistant[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,
      11,    1,   68,    2, 0x0a /* Public */,
      13,    1,   71,    2, 0x0a /* Public */,
      14,    0,   74,    2, 0x0a /* Public */,
      15,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,   12,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,    7,

       0        // eod
};

void pc_assistant::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pc_assistant *_t = static_cast<pc_assistant *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_on_refresh_mcu_state((*reinterpret_cast< MCU_STATE*(*)>(_a[1]))); break;
        case 1: _t->signal_on_send_serial_packet((*reinterpret_cast< Serial_packet*(*)>(_a[1]))); break;
        case 2: _t->slot_on_click_start(); break;
        case 3: _t->slot_on_serial_timeout(); break;
        case 4: _t->slot_on_packet_timeout(); break;
        case 5: _t->slot_on_refresh_mcu_state((*reinterpret_cast< MCU_STATE*(*)>(_a[1]))); break;
        case 6: _t->slot_on_send_serial_packet((*reinterpret_cast< Serial_packet*(*)>(_a[1]))); break;
        case 7: _t->init_signal_and_slot(); break;
        case 8: _t->on_serial_callback((*reinterpret_cast< Serial_packet(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (pc_assistant::*_t)(MCU_STATE * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&pc_assistant::signal_on_refresh_mcu_state)) {
                *result = 0;
            }
        }
        {
            typedef void (pc_assistant::*_t)(Serial_packet * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&pc_assistant::signal_on_send_serial_packet)) {
                *result = 1;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void pc_assistant::signal_on_refresh_mcu_state(MCU_STATE * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void pc_assistant::signal_on_send_serial_packet(Serial_packet * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
