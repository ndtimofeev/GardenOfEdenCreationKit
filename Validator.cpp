// Definition
#include <Validator.h>

// STL
#include <initializer_list>

// Core
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>

// Gui
#include <QtGui/QValidator>

PipeValidator::PipeValidator( const std::initializer_list<QValidator*> &pipe, QObject* parent ) :
    QValidator( parent )
{
    for ( QValidator* v : pipe )
        this->pipeStore << v;
}

PipeValidator::~PipeValidator()
{
}

QValidator::State PipeValidator::validate( QString &input, int &pos ) const
{
    State st = Invalid;

    for ( int i = 0, j = this->pipeStore.size(); st != Acceptable && i < j; i++ )
        st = this->pipeStore.at( i )->validate( input, pos );

    return st;
}

void  PipeValidator::fixup( QString &input ) const
{
    for ( int i = 0, j = this->pipeStore.size(); i < j; i++ )
    {
        int pos = 0;
        this->pipeStore.at( i )->fixup( input );
        if ( this->validate( input, pos ) == Acceptable )
            break;
    }
}

Invalidator::Invalidator( QObject* parent ) : QValidator( parent )
{
    // body
}

Invalidator::~Invalidator()
{
    // body
}

QValidator::State Invalidator::validate( QString&, int& ) const
{
    return Invalid;
}

void  Invalidator::fixup( QString& ) const
{
    // body
}

