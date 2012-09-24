// Core
#include <QtCore/QDebug>
#include <QtCore/QElapsedTimer>
#include <QtCore/QCoreApplication>
#include <QtCore/QObject>

// Internal
#include <ConnectionHolder.h>
#include <Waiter.h>

Waiter::Waiter( qint64 msec, QObject* parent ) :
    QObject( parent ),
    ConnectionHolder(),
    timeout( msec ),
    app( QCoreApplication::instance() ),
    good( false ),
    next( true ),
    val( No )
{}

Waiter::~Waiter()
{
    this->release();
}

void Waiter::success()
{
    this->good = true;
    this->next = false;
    this->val = Good;
    this->release();
    emit intercepted();
}

void Waiter::drop()
{
    this->next = false;
    this->val = Bad;
    this->release();
}

bool Waiter::exec()
{
    this->timer.start();
    while ( ! this->timer.hasExpired( this->timeout ) && this->next && ! this->val )
        app->processEvents();

    return this->good;
}
