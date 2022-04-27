#ifndef INC_42FT_CONTAINERS_ENABLE_IF_H
#define INC_42FT_CONTAINERS_ENABLE_IF_H

namespace ft
{
	template< bool B, class T = void >
	struct enable_if;

	template<class T>
	struct enable_if<true, T> { typedef T type; };
}

#endif
