#ifndef _CONNECTIONHOLDER_H_9403_
#define _CONNECTIONHOLDER_H_9403_

// STL
#include <vector>

// Core
#include <QtCore/QVector>
#include <QtCore/QMetaObject>
#include <QtCore/QObject>

class ConnectionHolder
{
public:
    ConnectionHolder();
    virtual ~ConnectionHolder();

    void release();

    ConnectionHolder& operator << ( QMetaObject::Connection connection );

private:
    std::vector<QMetaObject::Connection> connections;
};

#endif /* _CONNECTIONHOLDER_H_9403_ */
