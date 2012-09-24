#ifndef _VARIANTEXT_H_636_
#define _VARIANTEXT_H_636_

// STL
#include <functional>

// Core
#include <QtCore/QVariant>

// Internal
#include <TypeTricks.h>

template <class T>
class VariantPair
{
public:
    constexpr VariantPair( ValueOrRef<T> val, const QVariant &var = QVariant() )
        : first( val ), second( var )
    {
        /* base */
    }

    constexpr VariantPair( const VariantPair& ) = default;
    constexpr VariantPair &operator = ( const VariantPair& ) = default;
    ~VariantPair() = default;

    T        first;
    QVariant second;
};

template <typename T>
inline QVariant operator >>= ( const QVariant &var, const std::function<QVariant(T)> &f )
{
    if ( var.isNull() )
        return var;

    QVariant newVar;

    if ( var.canConvert<T>() )
        newVar = f( var.value<T>() );

    return newVar;
}

template <typename T>
inline void operator >>= ( const QVariant &var, const std::function<void(T)> &f )
{
    if ( ! var.isNull() )
        if ( var.canConvert<T>() )
            f( var.value<T>() );
}

template <typename T>
using VariantFrom = std::function<QVariant(T)>;

template <typename T>
using VoidFrom = std::function<void(T)>;

template <typename ... Types>
inline QVariant mdo( const QVariant &var, std::function<QVariant(Types)> ... arg )
{
    return QVariant();
}

template <typename R, typename T, typename ... Types>
inline void mdo( const QVariant &var, std::function<QVariant(Types)> ... arg, std::function<R(T)> f )
{
}

template <typename T, typename Func>
inline void monadBind( const QVariant &var, Func func )
{
    if ( ! var.isNull() )
        if ( var.canConvert<T>() )
            func( var.value<T>() );
}

/* template <typename T, typename Func> */
/* inline QVariant monadBind( const QVariant &var, Func func ) */
/* { */
/*     if ( var.isNull() ) */
/*         return var; */

/*     QVariant newVar; */

/*     if ( var.canConvert<T>() ) */
/*         newVar = func( var.value<T>() ); */

/*     return newVar; */
/* } */

#endif /* _VARIANTEXT_H_636_ */
