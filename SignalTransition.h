#ifndef _SIGNALTRANSITION_H_10871_
#define _SIGNALTRANSITION_H_10871_

// STL
#include <type_traits>

// Core
#include <QtCore/QSignalTransition>
#include <QtCore/QObject>
#include <QtCore/QMetaMethod>
#include <QtCore/QState>
#include <QtCore/QAbstractState>

template <typename Sender, typename Type, typename ...Args>
QSignalTransition* signalTransition( const Sender* sender, void (Type::*f)( Args... ), QState* sourceState = nullptr )
{
    static_assert( std::is_base_of<QObject,Sender>::value, "sender is not QObject" );
    static_assert( std::is_base_of<Type,Sender>::value, "signal is not member of sender" );

    return new QSignalTransition(
        static_cast<const QObject*>( sender ),
        QMetaMethod::fromSignal( f ).methodSignature().data(), sourceState );
}

template <typename Sender, typename Type, typename ...Args>
QSignalTransition* signalTransition( QState* from, const Sender* sender, void (Type::*f)( Args... ), QAbstractState* to )
{
    QSignalTransition* trans = signalTransition( sender, f, from );
    trans->setTargetState( to );

    return trans;
}

#endif /* end of include guard: _SIGNALTRANSITION_H_10871_ */
