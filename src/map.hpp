#ifndef INC_42FT_CONTAINERS_MAP_H
#define INC_42FT_CONTAINERS_MAP_H

#include "utility/utility.hpp"
#include <memory>

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< pair<const Key,T> > >
	class map
	{
	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T>	value_type;
		typedef Compare					key_compare;
		typedef Alloc					allocator_type;
	public:
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map<Key, T, Compare, Alloc>;
		protected:
			Compare comp;
			explicit value_compare(Compare c) : comp(c) { }
		public:
			bool operator()(const value_type& lhs, const value_type& rhs) const
			{
				return comp(lhs.first, rhs.first);
			}
		};
	public:
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename _Rep_type::iterator							iterator;
		typedef typename _Rep_type::const_iterator						const_iterator;
//		typedef typename _Rep_type::reverse_iterator					reverse_iterator;
//		typedef typename _Rep_type::const_reverse_iterator				const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef typename allocator_type::size_type						size_type;
	};
}

#endif
