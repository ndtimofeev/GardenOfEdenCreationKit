#ifndef _CUSTOMIZABLESIGNALTRANSITION_H_29940_
#define _CUSTOMIZABLESIGNALTRANSITION_H_29940_

// STL
#include <functional>

// Core
#include <QtCore/QSignalTransition>
#include <QtCore/QState>
#include <QtCore/QStateMachine>
#include <QtCore/QObject>
#include <QtCore/QEvent>

template <typename Sender, typename Type, typename ...Args>
class CustomizableSignalTransition : public QSignalTransition
{
public:
    using SignalHandler = std::function<bool( Args... )>;

    CustomizableSignalTransition( QState* sourceState = nullptr ) :
        QSignalTransition( sourceState )
    {
        // body
    }

    CustomizableSignalTransition( const Sender* sender, void (Type::*f)( Args... ), SignalHandler h = SignalHandler(), QState* sourceState = nullptr ) :
        QSignalTransition( sender, QMetaMethod::fromSignal( f ).methodSignature().data(), sourceState ),
        handlerStore( h )
    {
        static_assert( std::is_base_of<QObject,Sender>::value, "sender is not QObject" );
        static_assert( std::is_base_of<Type,Sender>::value, "signal is not member of sender" );
    }

    virtual ~CustomizableSignalTransition() override {};

protected:
    virtual bool eventTest( QEvent* e ) override
    {
        if ( ! QSignalTransition::eventTest( e ) )
            return false;

        return true;
    }

private:
    SignalHandler handlerStore;

    CustomizableSignalTransition( const CustomizableSignalTransition & ) = delete;
    CustomizableSignalTransition( CustomizableSignalTransition && ) = delete;
    CustomizableSignalTransition& operator = ( const CustomizableSignalTransition & ) = delete;
    CustomizableSignalTransition& operator = ( CustomizableSignalTransition && ) = delete;
};


#endif /* end of include guard: _CUSTOMIZABLESIGNALTRANSITION_H_29940_ */
