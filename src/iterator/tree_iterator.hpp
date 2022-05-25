#ifndef INC_42FT_CONTAINERS_TREE_ITERATOR_H
#define INC_42FT_CONTAINERS_TREE_ITERATOR_H

#include "utility/utility.hpp"

namespace ft
{
	template <typename T>
	static Node<T>*
	tree_increment(Node<T>* node)
	{
		if (node->right_child != 0)
		{
			node = node->right_child;
			while (node->left_child != 0)
				node = node->left_child;
		}
		else
		{
			Node<T>* tmp = node->parent;
			while (node == tmp->right_child)
			{
				node = tmp;
				tmp = tmp->parent;
			}
			if (node->right_child != tmp)
				node = tmp;
		}
		return node;
	}

	template <typename T>
	static Node<T>*
	tree_decrement(Node<T>* _x)
	{
		// TODO check
//		if (//_x->_M_color == _S_red &&
//		_x->parent->parent == _x)
//			_x = _x->right_child;
		if (_x->left_child != 0)
		{
			Node<T>* _y = _x->left_child;
			while (_y->right_child != 0)
				_y = _y->right_child;
			_x = _y;
		}
		else
		{
			Node<T>* _y = _x->parent;
			while (_x == _y->left_child)
			{
				_x = _y;
				_y = _y->parent;
			}
			_x = _y;
		}
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

		typedef tree_iterator<T>			self;
		typedef Node<T>*					link_type;

		tree_iterator() : node() { }

		explicit tree_iterator(Node<T>* _x) : node(_x) { }

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

		Node<T>* node;
	};
}

#endif
