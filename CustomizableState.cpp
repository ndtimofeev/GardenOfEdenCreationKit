// Definition
#include  <CustomizableState.h>

// Core
#include <QtCore/QState>
#include <QtCore/QEvent>

CustomizableState::CustomizableState( QState* parent ) : QState( parent )
{
    // body
}

CustomizableState::~CustomizableState()
{
    // body
}

void CustomizableState::setEntryHandler( std::function<void ( QState*, QEvent* )> h )
{
    this->entryHandler = h;
}

void CustomizableState::setExitHandler( std::function<void ( QState*, QEvent* )> h )
{
    this->exitHandler = h;
}

void CustomizableState::onEntry( QEvent* e )
{
    this->QState::onEntry( e );

    if ( this->entryHandler )
        this->entryHandler( this, e );
}

void CustomizableState::onExit( QEvent* e )
{
    this->QState::onExit( e );

    if ( this->exitHandler )
        this->exitHandler( this, e );
}
