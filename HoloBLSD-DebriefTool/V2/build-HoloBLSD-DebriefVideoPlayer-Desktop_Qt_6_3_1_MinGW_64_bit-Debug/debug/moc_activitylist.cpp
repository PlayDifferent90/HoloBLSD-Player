/****************************************************************************
** Meta object code from reading C++ file 'activitylist.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../HoloBLSD-DebriefVideoPlayer/activitylist.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'activitylist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ActivityList_t {
    const uint offsetsAndSize[18];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ActivityList_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ActivityList_t qt_meta_stringdata_ActivityList = {
    {
QT_MOC_LITERAL(0, 12), // "ActivityList"
QT_MOC_LITERAL(13, 13), // "DoubleClicked"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 7), // "Clicked"
QT_MOC_LITERAL(36, 4), // "name"
QT_MOC_LITERAL(41, 17), // "AddActivityInList"
QT_MOC_LITERAL(59, 5), // "_name"
QT_MOC_LITERAL(65, 6), // "_visib"
QT_MOC_LITERAL(72, 15) // "FlushActivities"

    },
    "ActivityList\0DoubleClicked\0\0Clicked\0"
    "name\0AddActivityInList\0_name\0_visib\0"
    "FlushActivities"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ActivityList[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    1 /* Public */,
       3,    1,   39,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    2,   42,    2, 0x0a,    4 /* Public */,
       8,    0,   47,    2, 0x0a,    7 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    6,    7,
    QMetaType::Void,

       0        // eod
};

void ActivityList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ActivityList *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->DoubleClicked(); break;
        case 1: _t->Clicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->AddActivityInList((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 3: _t->FlushActivities(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ActivityList::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActivityList::DoubleClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ActivityList::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActivityList::Clicked)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ActivityList::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ActivityList.offsetsAndSize,
    qt_meta_data_ActivityList,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ActivityList_t
, QtPrivate::TypeAndForceComplete<ActivityList, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ActivityList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ActivityList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ActivityList.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ActivityList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ActivityList::DoubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ActivityList::Clicked(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
