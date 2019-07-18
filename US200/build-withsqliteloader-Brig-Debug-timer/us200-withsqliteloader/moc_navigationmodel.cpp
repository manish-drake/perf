/****************************************************************************
** Meta object code from reading C++ file 'navigationmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Scope_timer/withsqliteloader/us200-withsqliteloader/navigationmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'navigationmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NavigationModel_t {
    QByteArrayData data[8];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NavigationModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NavigationModel_t qt_meta_stringdata_NavigationModel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "NavigationModel"
QT_MOC_LITERAL(1, 16, 11), // "onAppLoaded"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "nextPath"
QT_MOC_LITERAL(4, 38, 8), // "currPage"
QT_MOC_LITERAL(5, 47, 8), // "prevPath"
QT_MOC_LITERAL(6, 56, 12), // "scopeDispose"
QT_MOC_LITERAL(7, 69, 9) // "appLoaded"

    },
    "NavigationModel\0onAppLoaded\0\0nextPath\0"
    "currPage\0prevPath\0scopeDispose\0appLoaded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NavigationModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    1,   40,    2, 0x02 /* Public */,
       5,    1,   43,    2, 0x02 /* Public */,
       6,    0,   46,    2, 0x02 /* Public */,
       7,    0,   47,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString, QMetaType::QString,    4,
    QMetaType::QString, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NavigationModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NavigationModel *_t = static_cast<NavigationModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onAppLoaded(); break;
        case 1: { QString _r = _t->nextPath((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 2: { QString _r = _t->prevPath((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->scopeDispose(); break;
        case 4: _t->appLoaded(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NavigationModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NavigationModel::onAppLoaded)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject NavigationModel::staticMetaObject = {
    { &ModelBase::staticMetaObject, qt_meta_stringdata_NavigationModel.data,
      qt_meta_data_NavigationModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NavigationModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NavigationModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NavigationModel.stringdata0))
        return static_cast<void*>(const_cast< NavigationModel*>(this));
    return ModelBase::qt_metacast(_clname);
}

int NavigationModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ModelBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void NavigationModel::onAppLoaded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
