// Definition
#include <ScopedPropertyRollback.h>

// Core
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QByteArray>

ScopedPropertyRollback::ScopedPropertyRollback( QObject* object, const char* name, QVariant &&var ) :
    oldValueStore( object->property( name ) ),
    propertyName( name ),
    objectPointer( object )
{
    object->setProperty( name, var );
}

ScopedPropertyRollback::ScopedPropertyRollback( QObject* object, const char* name, const QVariant &var ) :
    oldValueStore( object->property( name ) ),
    propertyName( name ),
    objectPointer( object )
{
    object->setProperty( name, var );
}

ScopedPropertyRollback::~ScopedPropertyRollback()
{
    this->objectPointer->setProperty( this->propertyName.constData(), this->oldValueStore );
}
