#ifndef _SMARTPOINTERS_H_17302_
#define _SMARTPOINTERS_H_17302_

// STL
// #include <type_traits>
// #include <initializer_list>

// Core
// #include <QtCore/QMap>
// #include <QtCore/QString>
// #include <QtCore/QVariant>
#include <QtCore/QScopedPointer>

// Internal
// #include <MapExt.h>
// #include <VariantExt.h>

template <typename T, typename Cleanup = QScopedPointerDeleter<T>>
class UniquePointer : public QScopedPointer<T,Cleanup>
{
public:
    inline UniquePointer( T* ptr = nullptr ) : QScopedPointer<T,Cleanup>( ptr ) {};

    inline UniquePointer( UniquePointer<T,Cleanup> &&ptr )
    {
        T* realPtr = ptr.take();
        this->reset( realPtr );
    }

    inline UniquePointer& operator = ( UniquePointer<T,Cleanup> &&ptr )
    {
        T* realPtr = ptr.take();
        this->reset( realPtr );

        return *this;
    }

    inline UniquePointer( const UniquePointer<T,Cleanup> &ptr ) :
        QScopedPointer<T,Cleanup>()
    {
        T* realPtr = const_cast<UniquePointer<T,Cleanup>*>( &ptr )->take();
        this->reset( realPtr );
    }

    inline ~UniquePointer() = default;

// private:
//     UniquePointer( UniquePointer<T,Cleanup> && ) = delete;
//     UniquePointer& operator = ( UniquePointer<T,Cleanup> && ) = delete;
};


// template <typename T>
// class ScopePropertyPointer
// {
// public:
//     ScopePropertyPointer( const VariantPair<QString> &pair, T* object = nullptr ) :
//         propertys( QMapFromList<QString>( { pair.first, object ? object->property( pair.first.toUtf8().constData() ) : QVariant() ) } ),
//         ptr( object )
//     {
//         static_assert( std::is_convertible<T*,QObject*>::value,
//                 "T is not QObject" );

//         if ( object && name.second.isValid() )
//             object->setProperty( pair.first.toStdString().c_str(), pair.second );
//     }

//     ScopePropertyPointer( const std::initializer_list<VariantPair<QString>> &list, T* object = nullptr ) :
//         ptr( object )
//     {
//         static_assert( std::is_convertible<T*,QObject*>::value,
//                 "T is not QObject" );

//         if ( object )
//         {
//             for ( const VariantPair<QString> &pair : list )
//             {
//                 this->propertys.insert( pair.first, object->property( pair.first.toStdString().c_str() ) );
//                 if ( pair.second.isValid() )
//                     object->setProperty( pair.first.toStdString().c_str(), pair.second );
//             }
//         }
//         else
//             for ( const VariantPair<QString> &pair : list )
//                 this->propertys.inserta( pair.first, QVariant() );
//     }

//     ~ScopePropertyPointer()
//     {
//         if ( this->ptr )
//             for ( const QString &name : this->propertys.keys() )
//                 this->ptr->setProperty( name.toStdString().c_str(), this->propertys.value( name ) );
//     }

//     ScopePropertyPointer<T>& operator = ( T* newPtr )
//     {
//         static_assert( std::is_convertible<T*,QObject*>::value, "T is not QObject" );

//         if ( this->ptr != newPtr )
//         {
//             for ( const QString &name : this->propertys.keys() )
//                 this->propertys.insert( name, newPtr->property( this->propertyName.toStdString().c_str() ) );

//             this->ptr = newPtr;
//         }

//         return *this;
//     }

//     inline T* operator->() const
//     {
//         return this->ptr;
//     }

//     inline T& operator*()
//     {
//         return *( this->ptr );
//     }

//     inline T* data() const
//     {
//         return this->ptr;
//     }

//     inline void release()
//     {
//         this->ptr = nullptr;
//     }

// private:
//     QVariantMap propertys;
//     T*          ptr;

// };

#endif /* _SMARTPOINTERS_H_17302_ */
