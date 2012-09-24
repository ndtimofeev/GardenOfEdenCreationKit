#ifndef _TYPETRICKS_H_52913_
#define _TYPETRICKS_H_52913_

// STL
#include <type_traits>

template <typename T>
using ValueOrRef = typename std::conditional<( std::is_pointer<T>::value || ( sizeof( T ) < 2 * sizeof( T* ) ) ), T, const T&>::type;

#endif /* _TYPETRICKS_H_52913_ */
