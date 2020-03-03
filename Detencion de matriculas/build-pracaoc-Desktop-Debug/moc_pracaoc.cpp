/****************************************************************************
** Meta object code from reading C++ file 'pracaoc.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pracaoc/pracaoc.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pracaoc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_pracAOC_t {
    QByteArrayData data[16];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pracAOC_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pracAOC_t qt_meta_stringdata_pracAOC = {
    {
QT_MOC_LITERAL(0, 0, 7), // "pracAOC"
QT_MOC_LITERAL(1, 8, 10), // "paintEvent"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "QPaintEvent*"
QT_MOC_LITERAL(4, 33, 15), // "procesoCompleto"
QT_MOC_LITERAL(5, 49, 6), // "cargar"
QT_MOC_LITERAL(6, 56, 12), // "copiarOrigen"
QT_MOC_LITERAL(7, 69, 13), // "copiarDestino"
QT_MOC_LITERAL(8, 83, 6), // "borrar"
QT_MOC_LITERAL(9, 90, 5), // "negar"
QT_MOC_LITERAL(10, 96, 10), // "umbralizar"
QT_MOC_LITERAL(11, 107, 13), // "eliminarRuido"
QT_MOC_LITERAL(12, 121, 9), // "detectarv"
QT_MOC_LITERAL(13, 131, 9), // "detectarh"
QT_MOC_LITERAL(14, 141, 8), // "recortar"
QT_MOC_LITERAL(15, 150, 8) // "matching"

    },
    "pracAOC\0paintEvent\0\0QPaintEvent*\0"
    "procesoCompleto\0cargar\0copiarOrigen\0"
    "copiarDestino\0borrar\0negar\0umbralizar\0"
    "eliminarRuido\0detectarv\0detectarh\0"
    "recortar\0matching"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pracAOC[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x0a /* Public */,
       4,    0,   82,    2, 0x0a /* Public */,
       5,    0,   83,    2, 0x0a /* Public */,
       6,    0,   84,    2, 0x0a /* Public */,
       7,    0,   85,    2, 0x0a /* Public */,
       8,    0,   86,    2, 0x0a /* Public */,
       9,    0,   87,    2, 0x0a /* Public */,
      10,    0,   88,    2, 0x0a /* Public */,
      11,    0,   89,    2, 0x0a /* Public */,
      12,    0,   90,    2, 0x0a /* Public */,
      13,    0,   91,    2, 0x0a /* Public */,
      14,    0,   92,    2, 0x0a /* Public */,
      15,    0,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void pracAOC::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pracAOC *_t = static_cast<pracAOC *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 1: _t->procesoCompleto(); break;
        case 2: _t->cargar(); break;
        case 3: _t->copiarOrigen(); break;
        case 4: _t->copiarDestino(); break;
        case 5: _t->borrar(); break;
        case 6: _t->negar(); break;
        case 7: _t->umbralizar(); break;
        case 8: _t->eliminarRuido(); break;
        case 9: _t->detectarv(); break;
        case 10: _t->detectarh(); break;
        case 11: _t->recortar(); break;
        case 12: _t->matching(); break;
        default: ;
        }
    }
}

const QMetaObject pracAOC::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_pracAOC.data,
      qt_meta_data_pracAOC,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *pracAOC::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pracAOC::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_pracAOC.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int pracAOC::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
