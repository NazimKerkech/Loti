/****************************************************************************
** Meta object code from reading C++ file 'TrameGauche.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../gui/trames/TrameGauche.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrameGauche.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TrameGauche_t {
    QByteArrayData data[21];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrameGauche_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrameGauche_t qt_meta_stringdata_TrameGauche = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TrameGauche"
QT_MOC_LITERAL(1, 12, 21), // "demande_changer_image"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 18), // "indice_selectionne"
QT_MOC_LITERAL(4, 54, 21), // "nouvelle_bibliotheque"
QT_MOC_LITERAL(5, 76, 6), // "Biblio"
QT_MOC_LITERAL(6, 83, 12), // "bibliotheque"
QT_MOC_LITERAL(7, 96, 11), // "maj_tableau"
QT_MOC_LITERAL(8, 108, 3), // "row"
QT_MOC_LITERAL(9, 112, 6), // "column"
QT_MOC_LITERAL(10, 119, 15), // "enregistere_bib"
QT_MOC_LITERAL(11, 135, 6), // "string"
QT_MOC_LITERAL(12, 142, 4), // "path"
QT_MOC_LITERAL(13, 147, 13), // "ajouter_image"
QT_MOC_LITERAL(14, 161, 13), // "charge_biblio"
QT_MOC_LITERAL(15, 175, 22), // "charger_biblio_externe"
QT_MOC_LITERAL(16, 198, 3), // "bib"
QT_MOC_LITERAL(17, 202, 4), // "trie"
QT_MOC_LITERAL(18, 207, 10), // "slide_prix"
QT_MOC_LITERAL(19, 218, 22), // "onItemSelectionChanged"
QT_MOC_LITERAL(20, 241, 8) // "chercher"

    },
    "TrameGauche\0demande_changer_image\0\0"
    "indice_selectionne\0nouvelle_bibliotheque\0"
    "Biblio\0bibliotheque\0maj_tableau\0row\0"
    "column\0enregistere_bib\0string\0path\0"
    "ajouter_image\0charge_biblio\0"
    "charger_biblio_externe\0bib\0trie\0"
    "slide_prix\0onItemSelectionChanged\0"
    "chercher"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrameGauche[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   75,    2, 0x0a /* Public */,
      10,    1,   80,    2, 0x0a /* Public */,
      13,    0,   83,    2, 0x0a /* Public */,
      14,    1,   84,    2, 0x0a /* Public */,
      15,    1,   87,    2, 0x0a /* Public */,
      17,    0,   90,    2, 0x0a /* Public */,
      18,    0,   91,    2, 0x0a /* Public */,
      19,    0,   92,    2, 0x0a /* Public */,
      20,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TrameGauche::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrameGauche *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->demande_changer_image((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->nouvelle_bibliotheque((*reinterpret_cast< Biblio(*)>(_a[1]))); break;
        case 2: _t->maj_tableau((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->enregistere_bib((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 4: _t->ajouter_image(); break;
        case 5: _t->charge_biblio((*reinterpret_cast< Biblio(*)>(_a[1]))); break;
        case 6: _t->charger_biblio_externe((*reinterpret_cast< Biblio(*)>(_a[1]))); break;
        case 7: _t->trie(); break;
        case 8: _t->slide_prix(); break;
        case 9: _t->onItemSelectionChanged(); break;
        case 10: _t->chercher(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrameGauche::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrameGauche::demande_changer_image)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TrameGauche::*)(Biblio );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrameGauche::nouvelle_bibliotheque)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TrameGauche::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_TrameGauche.data,
    qt_meta_data_TrameGauche,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TrameGauche::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrameGauche::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrameGauche.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int TrameGauche::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void TrameGauche::demande_changer_image(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TrameGauche::nouvelle_bibliotheque(Biblio _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
