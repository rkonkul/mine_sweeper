/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Nov 10 18:28:59 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      35,   11,   11,   11, 0x0a,
      58,   11,   11,   11, 0x0a,
      73,   11,   11,   11, 0x0a,
      81,   11,   11,   11, 0x0a,
      97,   95,   11,   11, 0x0a,
     118,   95,   11,   11, 0x0a,
     143,   11,   11,   11, 0x0a,
     156,   11,   11,   11, 0x0a,
     173,   11,   11,   11, 0x08,
     200,   11,   11,   11, 0x08,
     226,   11,   11,   11, 0x08,
     255,   11,   11,   11, 0x08,
     290,   11,   11,   11, 0x08,
     316,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0increment_mines_left()\0"
    "decrement_mines_left()\0update_timer()\0"
    "reset()\0player_lose()\0b\0mine_search(Button*)\0"
    "rec_mine_search(Button*)\0show_mines()\0"
    "show_num_mines()\0on_actionReset_triggered()\0"
    "on_actionExit_triggered()\0"
    "on_actionTop_Ten_triggered()\0"
    "on_actionReset_Top_Ten_triggered()\0"
    "on_actionHelp_triggered()\0"
    "on_actionAbout_triggered()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: increment_mines_left(); break;
        case 1: decrement_mines_left(); break;
        case 2: update_timer(); break;
        case 3: reset(); break;
        case 4: player_lose(); break;
        case 5: mine_search((*reinterpret_cast< Button*(*)>(_a[1]))); break;
        case 6: rec_mine_search((*reinterpret_cast< Button*(*)>(_a[1]))); break;
        case 7: show_mines(); break;
        case 8: show_num_mines(); break;
        case 9: on_actionReset_triggered(); break;
        case 10: on_actionExit_triggered(); break;
        case 11: on_actionTop_Ten_triggered(); break;
        case 12: on_actionReset_Top_Ten_triggered(); break;
        case 13: on_actionHelp_triggered(); break;
        case 14: on_actionAbout_triggered(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
