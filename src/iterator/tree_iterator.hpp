#ifndef INC_42FT_CONTAINERS_TREE_ITERATOR_H
#define INC_42FT_CONTAINERS_TREE_ITERATOR_H

#include "iterator_traits.hpp"
#include "../utility/utility.hpp"

namespace ft
{
	template<typename T>
	struct tree_iterator
	{
		typedef T  value_type;
		typedef T& reference;
		typedef T* pointer;

		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t			 difference_type;

		typedef tree_iterator<T>		_Self;
		typedef _Rb_tree_node_base::_Base_ptr	_Base_ptr;
		typedef _Rb_tree_node<T>*		_Link_type;

		tree_iterator()
				: _M_node() { }

		explicit
		tree_iterator(_Base_ptr __x)
				: _M_node(__x) { }

		reference
		operator*() const
		{ return *static_cast<_Link_type>(_M_node)->_M_valptr(); }

		pointer
		operator->() const
		{ return static_cast<_Link_type> (_M_node)->_M_valptr(); }

		_Self&
		operator++()
		{
			_M_node = _Rb_tree_increment(_M_node);
			return *this;
		}

		_Self
		operator++(int)
		{
			_Self __tmp = *this;
			_M_node = _Rb_tree_increment(_M_node);
			return __tmp;
		}

		_Self&
		operator--()
		{
			_M_node = _Rb_tree_decrement(_M_node);
			return *this;
		}

		_Self
		operator--(int)
		{
			_Self __tmp = *this;
			_M_node = _Rb_tree_decrement(_M_node);
			return __tmp;
		}

		friend bool
		operator==(const _Self& __x, const _Self& __y)
		{ return __x._M_node == __y._M_node; }

		friend bool
		operator!=(const _Self& __x, const _Self& __y)
		{ return __x._M_node != __y._M_node; }

		_Base_ptr _M_node;
	};
}

#endif
