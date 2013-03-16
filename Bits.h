#ifndef BITS_H
#define BITS_H

constexpr unsigned int __constCharToOneOrZero( char c )
{
    return c == '0' ? 0 : 1;
}

template <char ... Bits>
struct __checkBits
{
    static const bool valid = false;
};

template <char Head, char ... Bits>
struct __checkBits<Head, Bits ... >
{
    static const bool valid = ( Head == '0' || Head == '1' )
        && ( sizeof...(Bits) ? __checkBits<Bits ...>::valid : true );
};

template <char ... Bits>
struct __constBinaryToIntValue
{
    static const unsigned long long value = 0;
};

template <char Head, char ... Bits>
struct __constBinaryToIntValue<Head, Bits ... >
{
    static const unsigned long long value =
        ( __constCharToOneOrZero( Head ) << sizeof...(Bits) ) + __constBinaryToIntValue<Bits ...>::value;
};

template <char ... Bits>
constexpr inline unsigned long long operator "" b()
{
    static_assert( __checkBits<Bits ...>::valid, "invalid binary string literal" );
    return __constBinaryToIntValue<Bits ...>::value;
}

#endif /* end of include guard: BITS_H */
