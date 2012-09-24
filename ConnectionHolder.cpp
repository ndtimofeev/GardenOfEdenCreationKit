// Core
#include <QtCore/QList>
#include <QtCore/QMetaObject>
#include <QtCore/QObject>
#include <QtCore/QDebug>

// Internal
#include <ConnectionHolder.h>

ConnectionHolder::ConnectionHolder()
{}

ConnectionHolder::~ConnectionHolder()
{
    this->release();
}

void ConnectionHolder::release()
{
    /* for ( const QMetaObject::Connection &connection : this->connections ) */
    /*     qDebug() << QObject::disconnect( connection ); */

    /* this->connections.clear(); */
}

ConnectionHolder& ConnectionHolder::operator << ( QMetaObject::Connection connection )
{
    qDebug() << "Add connection" << connection;
    this->connections.push_back( connection );

    return *this;
}
