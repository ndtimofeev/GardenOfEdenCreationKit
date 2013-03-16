#ifndef _UNIQUELIST_H_22085_
#define _UNIQUELIST_H_22085_

// // STL
// #include <utility>

// // Core
// #include <QtCore/QScopedPointer>

// Internal
#include <SmartPointers.h>

template <typename T>
class UniqueList
{
    struct Node
    {
        UniquePointer<Node> nextPtr;
        Node*               prevPtr;
        T                   value;
    };

public:
    class const_iterator
    {
        friend UniqueList<T>;

    public:
        inline const_iterator() : pointee( nullptr ), position( -1 ) {};

        inline const_iterator( const const_iterator & ) = default;
        inline const_iterator& operator = ( const const_iterator & ) = default;

        inline const_iterator( const_iterator && ) = default;
        inline const_iterator& operator = ( const_iterator && ) = default;

        inline ~const_iterator() = default;

        inline bool operator == ( const const_iterator &it ) const
        {
            return this->pointee == it.pointee;
        }

        inline bool operator != ( const const_iterator &it ) const
        {
            return ! ( *this == it );
        }

        inline const_iterator& operator + ( int i )
        {
            this->position += i;

            while ( i-- )
                this->pointee = this->pointee->nextPtr.data();

            if ( ! this->pointee )
                this->position = -1;

            return *this;
        }

        inline const_iterator& operator ++ ()
        {
            return ( *this + 1 );
        }

        inline const_iterator operator ++ ( int )
        {
            const_iterator i( *this );
            ++( *this );

            return i;
        }

        inline const_iterator& operator += ( int i )
        {
            return ( *this + i );
        }

        inline const_iterator& operator - ( int i )
        {
            this->position -= i;

            while ( i-- )
                this->pointee = this->pointee->prevPtr;

            return *this;
        }

        inline const_iterator& operator -- ()
        {
            return ( *this - 1 );
        }

        inline const_iterator operator -- ( int )
        {
            const_iterator i( *this );
            --( *this );

            return *this;
        }

        inline const_iterator& operator -= ( int i )
        {
            *this - i;
            return *this;
        }

        inline int operator - ( const const_iterator& it )
        {
            return this->position - it.position;
        }

        inline const T & operator * () const
        {
            return this->pointee->value;
        }

        inline int pos() const
        {
            return this->position;
        }

    protected:
        inline const_iterator( Node* ptr, Node* head ) :
            pointee( ptr ), position( -1 )
        {
            this->setPosition( head );
        }

    private:
        inline void setPosition( Node* first )
        {
            this->position = 0;

            while ( this->pointee != first )
            {
                first = first->nextPtr.data();
                ++( this->position );
            }
        }

        Node* pointee;
        int   position;
    };

    inline UniqueList() : firstPtr( nullptr ), lastPtr( nullptr ), sizeStore( 0 )
    {
        // body
    }

    inline UniqueList( UniqueList &&ulist ) = default;

    inline UniqueList& operator = ( UniqueList &&ulist ) = default;

    inline ~UniqueList() = default;

    inline const_iterator begin() const
    {
        return const_iterator( this->firstPtr.data(), this->firstPtr.data() );
    }

    inline const_iterator end() const
    {
        return const_iterator();
    }

    const T & first() const
    {
        return *( this->firstPtr );
    }

    const T & last() const
    {
        return *( this->lastPtr );
    }

    UniqueList& operator << ( T &&uelem )
    {
        Node* newNode    = new Node { nullptr, nullptr, uelem };

        if ( this->lastPtr )
        {
            newNode->prevPtr = this->lastPtr;
            this->lastPtr->nextPtr = newNode;
        }
        else
            this->firstPtr = newNode;

        this->lastPtr = newNode;
        ++( this->sizeStore );

        return *this;
    }

private:
    UniquePointer<Node> firstPtr;
    Node*               lastPtr;
    size_t              sizeStore;

    UniqueList( const UniqueList & ) = delete;
    UniqueList& operator = ( const UniqueList & ) = delete;
};

#endif /* end of include guard: _UNIQUELIST_H_22085_ */
