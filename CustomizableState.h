#ifndef _CUSTOMIZABLESTATE_H_12401_
#define _CUSTOMIZABLESTATE_H_12401_

// STL
#include <functional>
#include <type_traits>
#include <tuple>

// Core
#include <QtCore/QObject>
#include <QtCore/QState>
#include <QtCore/QEvent>
#include <QtCore/QAbstractState>
#include <QtCore/QVector>
#include <QtCore/QLatin1String>
#include <QtCore/QVariant>

template <typename T>
class EntryHandler : public T
{
public:
    using Handler = std::function<void ( T*, QEvent* )>;

    EntryHandler( QState* parent = nullptr ) : T( parent )
    {
        static_assert( std::is_base_of<QAbstractState,T>::value, "T is not QAbstractState" );
    }

    virtual ~EntryHandler() override {};

    void setEntryHandler( Handler h )
    {
        this->entryHandler = h;
    }

protected:
    virtual void onEntry( QEvent* e ) override
    {
        this->T::onEntry( e );

        if ( this->entryHandler )
            this->entryHandler( this, e );
    }

private:
    Handler entryHandler;
};

template <typename T>
class ExitHandler : public T
{
public:
    using Handler = std::function<void ( T*, QEvent* )>;

    ExitHandler( QState* parent = nullptr ) : T( parent )
    {
        static_assert( std::is_base_of<QAbstractState,T>::value, "T is not QAbstractState" );
    }

    virtual ~ExitHandler() override {};

    void setExitHandler( Handler h )
    {
        this->exitHandler = h;
    }

protected:
    virtual void onExit( QEvent* e ) override
    {
        this->T::onExit( e );

        if ( this->exitHandler )
            this->exitHandler( this, e );
    }

private:
    Handler exitHandler;
};

template <typename T>
class UpdateProperty : public T
{
public:
    using Property = std::tuple<QObject*, QByteArray, QVariant>;

    UpdateProperty( QState* parent = nullptr ) : T( parent )
    {
        static_assert( std::is_base_of<QAbstractState,T>::value, "T is not QAbstractState" );
    }

    virtual ~UpdateProperty() override
    {
        // body
    }

    void updateProperty( QObject* obj, const char* name, const QVariant &var )
    {
        this->propertys << Property( obj, name, var );
    }

protected:
    virtual void onEntry( QEvent* e ) override
    {
        this->T::onEntry( e );

        for ( const Property &it : this->propertys )
            std::get<0>( it )->setProperty( std::get<1>( it ).constData(), std::get<2>( it ) );
    }

private:
    QVector<Property> propertys;
};

class CustomizableState : public QState
{
    Q_OBJECT
public:
    CustomizableState( QState* parent = nullptr );
    virtual ~CustomizableState() override;

    void setEntryHandler( std::function<void ( QState*, QEvent* )> h );
    void setExitHandler( std::function<void ( QState*, QEvent* )> h );

protected:
    virtual void onEntry( QEvent* e ) override;
    virtual void onExit( QEvent* e ) override;

private:
    std::function<void ( QState*, QEvent* )> entryHandler;
    std::function<void ( QState*, QEvent* )> exitHandler;

    CustomizableState( const CustomizableState & ) = delete;
    CustomizableState( CustomizableState && ) = delete;
    CustomizableState& operator = ( const CustomizableState & ) = delete;
    CustomizableState& operator = ( CustomizableState && ) = delete;
};


#endif /* end of include guard: _CUSTOMIZABLESTATE_H_12401_ */
