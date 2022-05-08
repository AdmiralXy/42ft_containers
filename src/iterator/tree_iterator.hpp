#ifndef INC_42FT_CONTAINERS_TREE_ITERATOR_H
#define INC_42FT_CONTAINERS_TREE_ITERATOR_H

#include "utility/utility.hpp"

namespace ft
{
	template <typename T>
	static NodeBase*
	tree_increment(Node<T>* _x)
	{
		if (_x && _x->left_child)
			_x = _x->left_child;
		return _x;
	}

	template <typename T>
	static NodeBase*
	tree_decrement(Node<T>* _x)
	{
		if (_x && _x->right_child)
			_x = _x->right_child;
		return _x;
	}

	template<typename T>
	struct tree_iterator
	{
		typedef T  value_type;
		typedef T& reference;
		typedef T* pointer;

		typedef bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t				difference_type;

		typedef tree_iterator<T>		self;
		typedef NodeBase::base_ptr		base_ptr;
		typedef Node<T>*				link_type;

		tree_iterator() : node() { }

		explicit tree_iterator(base_ptr _x) : node(_x) { }

		reference operator*() const { return *static_cast<link_type>(node)->valptr(); }

		pointer operator->() const { return static_cast<link_type> (node)->valptr(); }

		self& operator++()
		{
			node = tree_increment<T>(node);
			return *this;
		}

		self operator++(int)
		{
			self _tmp = *this;
			node = tree_increment<T>(node);
			return _tmp;
		}

		self& operator--()
		{
			node = tree_decrement<T>(node);
			return *this;
		}

		self operator--(int)
		{
			self _tmp = *this;
			node = tree_decrement<T>(node);
			return _tmp;
		}

		friend bool
		operator==(const self& _x, const self& _y) { return _x.node == _y.node; }

		friend bool
		operator!=(const self& _x, const self& _y) { return _x.node != _y.node; }

		base_ptr node;
	};
}

#endif
