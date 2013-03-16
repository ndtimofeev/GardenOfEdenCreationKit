#ifndef _SCOPEDPROPERTYROLLBACK_H_41974_
#define _SCOPEDPROPERTYROLLBACK_H_41974_

// Core
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QByteArray>

class ScopedPropertyRollback
{
public:
    ScopedPropertyRollback( QObject* obj, const char* name, const QVariant &var );
    ScopedPropertyRollback( QObject* obj, const char* name, QVariant &&var );
    ~ScopedPropertyRollback();

private:
    QVariant   oldValueStore;
    QByteArray propertyName;
    QObject*   objectPointer;

    ScopedPropertyRollback( const ScopedPropertyRollback & ) = delete;
    ScopedPropertyRollback( ScopedPropertyRollback && ) = delete;
    ScopedPropertyRollback& operator = ( const ScopedPropertyRollback & ) = delete;
    ScopedPropertyRollback& operator = ( ScopedPropertyRollback && ) = delete;
};

#endif /* end of include guard: _SCOPEDPROPERTYROLLBACK_H_41974_ */
