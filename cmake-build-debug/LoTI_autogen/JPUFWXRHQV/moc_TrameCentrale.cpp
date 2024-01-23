/****************************************************************************
** Meta object code from reading C++ file 'TrameCentrale.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../gui/trames/TrameCentrale.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrameCentrale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TrameCentrale_t {
    QByteArrayData data[21];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrameCentrale_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrameCentrale_t qt_meta_stringdata_TrameCentrale = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TrameCentrale"
QT_MOC_LITERAL(1, 14, 23), // "c_nouvelle_bibliotheque"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 6), // "Biblio"
QT_MOC_LITERAL(4, 46, 12), // "bibliotheque"
QT_MOC_LITERAL(5, 59, 13), // "changer_image"
QT_MOC_LITERAL(6, 73, 18), // "indice_selectionne"
QT_MOC_LITERAL(7, 92, 7), // "flouter"
QT_MOC_LITERAL(8, 100, 13), // "taille_filtre"
QT_MOC_LITERAL(9, 114, 7), // "deriver"
QT_MOC_LITERAL(10, 122, 8), // "noFiltre"
QT_MOC_LITERAL(11, 131, 15), // "detecter_lignes"
QT_MOC_LITERAL(12, 147, 9), // "rehausser"
QT_MOC_LITERAL(13, 157, 9), // "segmenter"
QT_MOC_LITERAL(14, 167, 7), // "seuil_r"
QT_MOC_LITERAL(15, 175, 7), // "seuil_g"
QT_MOC_LITERAL(16, 183, 7), // "seuil_b"
QT_MOC_LITERAL(17, 191, 20), // "appliquer_traitement"
QT_MOC_LITERAL(18, 212, 10), // "traitement"
QT_MOC_LITERAL(19, 223, 13), // "charge_biblio"
QT_MOC_LITERAL(20, 237, 14) // "suprimer_image"

    },
    "TrameCentrale\0c_nouvelle_bibliotheque\0"
    "\0Biblio\0bibliotheque\0changer_image\0"
    "indice_selectionne\0flouter\0taille_filtre\0"
    "deriver\0noFiltre\0detecter_lignes\0"
    "rehausser\0segmenter\0seuil_r\0seuil_g\0"
    "seuil_b\0appliquer_traitement\0traitement\0"
    "charge_biblio\0suprimer_image"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrameCentrale[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   67,    2, 0x0a /* Public */,
       7,    1,   70,    2, 0x0a /* Public */,
       9,    1,   73,    2, 0x0a /* Public */,
      11,    0,   76,    2, 0x0a /* Public */,
      12,    1,   77,    2, 0x0a /* Public */,
      13,    3,   80,    2, 0x0a /* Public */,
      17,    1,   87,    2, 0x0a /* Public */,
      19,    1,   90,    2, 0x0a /* Public */,
      20,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   14,   15,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void TrameCentrale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrameCentrale *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->c_nouvelle_bibliotheque((*reinterpret_cast< Biblio(*)>(_a[1]))); break;
        case 1: _t->changer_image((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->flouter((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->deriver((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->detecter_lignes(); break;
        case 5: _t->rehausser((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->segmenter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->appliquer_traitement((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->charge_biblio((*reinterpret_cast< Biblio(*)>(_a[1]))); break;
        case 9: _t->suprimer_image(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrameCentrale::*)(Biblio );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrameCentrale::c_nouvelle_bibliotheque)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TrameCentrale::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_TrameCentrale.data,
    qt_meta_data_TrameCentrale,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TrameCentrale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrameCentrale::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrameCentrale.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int TrameCentrale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void TrameCentrale::c_nouvelle_bibliotheque(Biblio _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
