#ifndef _MAPEXT_H_50193_
#define _MAPEXT_H_50193_

// STL
#include <initializer_list>

// Core
#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QVariant>

// Internal
#include <TypeTricks.h>
#include <VariantExt.h>

template <class Key, class T>
inline QMap<Key,T> QMapFromList( const std::initializer_list<QPair<Key,T>> &list )
{
    QMap<Key,T> map;

    for ( ValueOrRef<QPair<Key,T>> pair : list )
        map.insert( pair.first, pair.second );

    return map;
}

template <class T>
inline QMap<T,QVariant> QMapFromList( const std::initializer_list<VariantPair<T>> &list )
{
    QMap<T,QVariant> map;

    for ( ValueOrRef<VariantPair<T>> pair : list )
        map.insert( pair.first, pair.second );

    return map;
}

#endif /* _MAPEXT_H_50193_ */
