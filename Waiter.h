#ifndef _WAITER_H_29323_
#define _WAITER_H_29323_

// STL
#include <tuple>

// Core
#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>
#include <QtCore/QList>
#include <QtCore/QMetaObject>
#include <QtCore/QObject>
#include <QtCore/QVariant>

// Internal
#include <ConnectionHolder.h>

class Waiter : public QObject, public ConnectionHolder
{
    Q_OBJECT
signals:
    void intercepted();

public:
    enum State
    {
        No   = 0,
        Good = 1,
        Bad  = 2
    };

    Waiter( qint64 msec, QObject* parent = 0 );
    virtual ~Waiter();

    void success();
    void drop();
    bool exec();

    static inline void sleep( qint64 msec )
    {
        QElapsedTimer timer;
        QCoreApplication* app = QCoreApplication::instance();

        timer.start();
        while ( ! timer.hasExpired( msec ) )
            app->processEvents();
    }

private:
    qint64                         timeout;
    QCoreApplication*              app;
    QElapsedTimer                  timer;
    bool                           good;
    bool                           next;
    State                          val;
};


template <typename ... T>
class Interceptor : public Waiter
{
public:
    Interceptor( qint64 msec, QObject* parent = 0 ) : Waiter( msec, parent )
    {}

    virtual ~Interceptor()
    {}

    void intercept( const T ... args )
    {
        this->mValue = std::make_tuple( args ... );
        this->success();
    }

    const std::tuple<T ...>& value() const
    {
        return this->mValue;
    }

private:
    std::tuple<T ...> mValue;
};

#endif
