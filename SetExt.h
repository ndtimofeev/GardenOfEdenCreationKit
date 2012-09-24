#ifndef SETEXT_H
#define SETEXT_H

// QtCore
#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtCore/QWeakPointer>

template <typename T>
int qHash( const QWeakPointer<T> &ptr )
{
    return qHash( ptr.data() );
}

template <typename T>
int qHash( const QPointer<T> &ptr )
{
    return qHash( ptr.data() );
}

template <typename T>
QSet<T> uniqSet( const QSet<T> &set )
{
    QSet<T> ret;
    for ( T elem : set )
        if ( ! ret.contains( elem ) )
            ret << elem;

    return ret;
}

#endif // SETEXT_H
