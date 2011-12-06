/****************************************************************************
** Meta object code from reading C++ file 'Button.h'
**
** Created: Thu Nov 10 18:29:01 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Button.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Button.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Button[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      22,    7,    7,    7, 0x05,
      38,    7,    7,    7, 0x05,
      61,   59,    7,    7, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Button[] = {
    "Button\0\0mine_marked()\0mine_unmarked()\0"
    "player_lose_signal()\0b\0"
    "mine_search_signal(Button*)\0"
};

const QMetaObject Button::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_Button,
      qt_meta_data_Button, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Button::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Button::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Button::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Button))
        return static_cast<void*>(const_cast< Button*>(this));
    return QPushButton::qt_metacast(_clname);
}

int Button::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mine_marked(); break;
        case 1: mine_unmarked(); break;
        case 2: player_lose_signal(); break;
        case 3: mine_search_signal((*reinterpret_cast< Button*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Button::mine_marked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Button::mine_unmarked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Button::player_lose_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Button::mine_search_signal(Button * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
