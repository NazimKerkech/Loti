/****************************************************************************
** Meta object code from reading C++ file 'TrameDroite.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../gui/trames/TrameDroite.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrameDroite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TrameDroite_t {
    QByteArrayData data[22];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrameDroite_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrameDroite_t qt_meta_stringdata_TrameDroite = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TrameDroite"
QT_MOC_LITERAL(1, 12, 4), // "flou"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 13), // "taille_filtre"
QT_MOC_LITERAL(4, 32, 8), // "contours"
QT_MOC_LITERAL(5, 41, 8), // "noFiltre"
QT_MOC_LITERAL(6, 50, 10), // "traitement"
QT_MOC_LITERAL(7, 61, 16), // "detection_lignes"
QT_MOC_LITERAL(8, 78, 12), // "rehaussement"
QT_MOC_LITERAL(9, 91, 12), // "segmentation"
QT_MOC_LITERAL(10, 104, 7), // "seuil_r"
QT_MOC_LITERAL(11, 112, 7), // "seuil_g"
QT_MOC_LITERAL(12, 120, 7), // "seuil_b"
QT_MOC_LITERAL(13, 128, 14), // "suprimer_image"
QT_MOC_LITERAL(14, 143, 19), // "charger_histogramme"
QT_MOC_LITERAL(15, 163, 18), // "indice_selectionne"
QT_MOC_LITERAL(16, 182, 10), // "get_pixmap"
QT_MOC_LITERAL(17, 193, 3), // "Mat"
QT_MOC_LITERAL(18, 197, 5), // "image"
QT_MOC_LITERAL(19, 203, 13), // "charge_biblio"
QT_MOC_LITERAL(20, 217, 6), // "Biblio"
QT_MOC_LITERAL(21, 224, 12) // "bibliotheque"

    },
    "TrameDroite\0flou\0\0taille_filtre\0"
    "contours\0noFiltre\0traitement\0"
    "detection_lignes\0rehaussement\0"
    "segmentation\0seuil_r\0seuil_g\0seuil_b\0"
    "suprimer_image\0charger_histogramme\0"
    "indice_selectionne\0get_pixmap\0Mat\0"
    "image\0charge_biblio\0Biblio\0bibliotheque"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrameDroite[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    1,   70,    2, 0x06 /* Public */,
       7,    0,   73,    2, 0x06 /* Public */,
       8,    1,   74,    2, 0x06 /* Public */,
       9,    3,   77,    2, 0x06 /* Public */,
      13,    0,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,   85,    2, 0x0a /* Public */,
      16,    1,   88,    2, 0x0a /* Public */,
      19,    1,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,   12,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::QPixmap, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 20,   21,

       0        // eod
};

void TrameDroite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrameDroite *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->flou((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->contours((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->traitement((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->detection_lignes(); break;
        case 4: _t->rehaussement((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->segmentation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->suprimer_image(); break;
        case 7: _t->charger_histogramme((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: { QPixmap _r = _t->get_pixmap((*reinterpret_cast< Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPixmap*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->charge_biblio((*reinterpret_cast< Biblio(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrameDroite::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrameDroite::flou)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TrameDroite::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrameDroite::contours)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TrameDroite::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrameDroite::traitement)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TrameDroite::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrameDroite::detection_lignes)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TrameDroite::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrameDroite::rehaussement)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TrameDroite::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrameDroite::segmentation)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TrameDroite::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrameDroite::suprimer_image)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TrameDroite::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_TrameDroite.data,
    qt_meta_data_TrameDroite,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TrameDroite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrameDroite::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrameDroite.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int TrameDroite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TrameDroite::flou(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TrameDroite::contours(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TrameDroite::traitement(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TrameDroite::detection_lignes()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TrameDroite::rehaussement(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TrameDroite::segmentation(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TrameDroite::suprimer_image()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
