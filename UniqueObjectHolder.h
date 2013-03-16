#ifndef _UNIQUEOBJECTHOLDER_H_22627_
#define _UNIQUEOBJECTHOLDER_H_22627_

// Core
#include <QtCore/QMap>
#include <QtCore/QMutex>
#include <QtCore/QSharedPointer>

template <typename T>
struct DefaultConstructor
{
    static T* newObject()
    {
        return new T;
    }
};

template <typename Identifier, typename T, template <typename Created> class CreationPolicy = DefaultConstructor >
class UniqueObjectHolder : private CreationPolicy<T>
{
public:
    UniqueObjectHolder() = delete;
    UniqueObjectHolder( const UniqueObjectHolder& ) = delete;
    UniqueObjectHolder& operator = ( const UniqueObjectHolder& ) = delete;
    ~UniqueObjectHolder() = delete;

    static QSharedPointer<T> create( const Identifier &id )
    {
        static QMutex mutex;
        T*            ptr = 0;

        if ( UniqueObjectHolder::mapPtr )
        {
            ptr = UniqueObjectHolder::mapPtr->value( id, 0 );
            if ( ! ptr )
            {
                mutex.lock();

                ptr = UniqueObjectHolder::mapPtr->value( id, 0 );

                if ( ! ptr )
                    ptr = UniqueObjectHolder::insertObject( id );

                mutex.unlock();
            }
        }
        else
        {
            mutex.lock();

            if ( UniqueObjectHolder::mapPtr )
            {
                mutex.unlock();
                return UniqueObjectHolder::create( id );
            }
            else
            {
                static QMap<Identifier,T*> map;
                UniqueObjectHolder::mapPtr = &map;

                ptr = insertObject( id );

                mutex.unlock();
            }
        }

        return QSharedPointer<T>( ptr, deleteObject );
    }

private:
    static T* insertObject( const Identifier &id )
    {
        T* objectPtr = CreationPolicy<T>::newObject();
        mapPtr->insert( id, objectPtr );
        return objectPtr;
    }

    static void deleteObject( T* obj )
    {
        static QMutex mutex;
        mutex.lock();

        if ( UniqueObjectHolder::mapPtr )
        {
            UniqueObjectHolder::mapPtr->remove( UniqueObjectHolder::mapPtr->key( obj ) );
            delete obj;
        }

        mutex.unlock();
    }

    static QMap<Identifier,T*>* mapPtr;
};

template <typename Identifier, typename T, template <typename Created> class CreationPolicy>
QMap<Identifier,T*>* UniqueObjectHolder<Identifier, T, CreationPolicy>::mapPtr = 0;

#endif /* _UNIQUEOBJECTHOLDER_H_22627_ */
