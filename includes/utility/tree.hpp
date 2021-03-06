#ifndef INC_42FT_CONTAINERS_TREE_H
#define INC_42FT_CONTAINERS_TREE_H

#include "utility.hpp"
#include "../iterator/iterator_traits.hpp"

namespace ft
{
	template <class value_type>
	struct Node
	{
		value_type								value;
		typedef Node<value_type>*				link_type;
		Node<value_type>*						parent;
		Node<value_type>*						left_child;
		Node<value_type>*						right_child;

		explicit Node() : parent(0), left_child(0), right_child(0) {}

		explicit Node(const value_type& value) : value(value), parent(0), left_child(0), right_child(0) {}

		explicit Node(value_type value, Node *parent) : value(value), parent(parent), left_child(0), right_child(0) {}

		static Node<value_type>* minimum(link_type x)
		{
			while (x->left_child != 0)
				x = x->left_child;
			return x;
		}

		static Node<value_type>* maximum(link_type x)
		{
			while (x->right_child != 0)
				x = x->right_child;
			return x;
		}

		value_type* valptr()
		{
			return std::__addressof(value);
		}

		const value_type* valptr() const
		{
			return std::__addressof(value);
		}
	};

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
	tree_decrement(Node<T>* node)
	{
		if (node->left_child != 0)
		{
			Node<T>* tmp = node->left_child;
			while (tmp->right_child != 0)
				tmp = tmp->right_child;
			node = tmp;
		}
		else
		{
			Node<T>* tmp = node->parent;
			while (node == tmp->left_child)
			{
				node = tmp;
				tmp = tmp->parent;
			}
			node = tmp;
		}
		return node;
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

	template<typename T>
	struct const_tree_iterator
	{
		typedef T			value_type;
		typedef const T&	reference;
		typedef const T*	pointer;

		typedef bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t				difference_type;

		typedef const_tree_iterator<T>			self;
		typedef Node<T>*						link_type;

		const_tree_iterator() : node() { }

		explicit const_tree_iterator(Node<T>* _x) : node(_x) { }

		const_tree_iterator(const tree_iterator<T>& it) : node(it.node) { }

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

	template <class Key, class T, typename Compare = std::less<Key>, typename Alloc = std::allocator<T> >
	class Tree
	{
	public:
		typedef Key															key_type;
		typedef ft::pair<const Key, T>										value_type;
		typedef typename Alloc::template rebind<Node<value_type> >::other	allocator_type;
		typedef Compare														key_compare;
		typedef ft::tree_iterator<value_type>								iterator;
		typedef ft::const_tree_iterator<value_type>							const_iterator;
		typedef typename allocator_type::size_type							size_type;
	private:
		Node<value_type>*		_root;
		Node<value_type>*		_rend;
		Node<value_type>*		_end;
		size_type				_size;
		allocator_type			_alloc;
		Compare					_comp;
	public:
		explicit Tree(const allocator_type &alloc = allocator_type(), const key_compare &comp = key_compare()) : _root(0), _size(0), _alloc(alloc), _comp(comp)
		{
			_rend = _alloc.allocate(1);
			_alloc.construct(_rend, Node<value_type>());
			_end = _alloc.allocate(1);
			_alloc.construct(_end, Node<value_type>());
		}

		Tree(const Tree &x) : _size()
		{
			*this = x;
		}

		Tree& operator=(const Tree& x)
		{
			if (this == &x)
				return *this;
			clear(_root);
			_alloc = x._alloc;
			_comp = x._comp;
			x._end->parent->right_child = 0;
			x._rend->parent->left_child = 0;
			fill(x._root);
			x.set_rend(x._root);
			x.set_end(x._root);
			return *this;
		}

		~Tree()
		{
			if (!_root) {
				_alloc.destroy(_end);
				_alloc.deallocate(_end, 1);
				_alloc.destroy(_rend);
				_alloc.deallocate(_rend, 1);
			} else {
				clear(_root);
			}
		}

		ft::pair<iterator, bool> add(const value_type &value)
		{
			Node<value_type>* inserted;
			if (_root == 0)
			{
				_root = _alloc.allocate(1);
				_alloc.construct(_root, Node<value_type>(value));
				inserted = _root;
			}
			else
			{
				_end->parent->right_child = 0;
				_rend->parent->left_child = 0;
				Node<value_type>* A = _root;
				Node<value_type>* B = A;
				while (A != 0)
				{
					if (!_comp(value.first, A->value.first) && !_comp(A->value.first, value.first)) {
						set_rend(_root);
						set_end(_root);
						return ft::make_pair(A, false);
					}
					B = A;
					if (_comp(value.first, A->value.first))
						A = A->left_child;
					else
						A = A->right_child;
				}
				if (_comp(value.first, B->value.first)) {
					B->left_child = _alloc.allocate(1);
					_alloc.construct(B->left_child, Node<value_type>(value, B));
					inserted = B->left_child;
				} else {
					B->right_child = _alloc.allocate(1);
					_alloc.construct(B->right_child, Node<value_type>(value, B));
					inserted = B->right_child;
				}
			}
			set_rend(_root);
			set_end(_root);
			++_size;
			return ft::make_pair(iterator(inserted), true);
		}

		ft::pair<iterator, bool> find(const key_type &value) const
		{
			if (_root == 0)
				return ft::make_pair(end(), false);
			else
			{
				Node<value_type>* A = _root;
				while (A != 0)
				{
					if (!_comp(value, A->value.first) && !_comp(A->value.first, value)) {
						return ft::make_pair(A, true);
					}
					if (_comp(value, A->value.first))
						A = A->left_child;
					else
						A = A->right_child;
				}
			}
			return ft::make_pair(end(), false);
		}

		size_type erase(const key_type &value)
		{
			if (_root != 0) {
				_end->parent->right_child = 0;
				_rend->parent->left_child = 0;

				ft::pair<iterator, bool> search = find(value);
				if (search.second == false)
					return false;

				Node<value_type>* A = search.first.node;
				Node<value_type>* B = A->parent ? A->parent : A;

				if (A->left_child == 0 && A->right_child == 0)
				{
					if (A == _root)
						_root = 0;
					else if (B->left_child == A)
						B->left_child = 0;
					else
						B->right_child = 0;
					_alloc.destroy(A);
					_alloc.deallocate(A, 1);
				}
				else if (A->left_child && A->right_child)
				{
					Node<value_type> *min = Node<value_type>::minimum(A->right_child);
					Node<value_type> *parent = A->parent;
					Node<value_type> *left_child = A->left_child;
					Node<value_type> *right_child = A->right_child;
					_alloc.destroy(A);
					_alloc.construct(A, Node<value_type>(min->value));
					A->left_child = left_child;
					A->right_child = right_child;
					A->parent = parent;
					if (min->parent == A) {
						A->right_child = min->right_child;
						min->right_child->parent = A->right_child;
					} else {
						min->parent->left_child = 0;
					}
					_alloc.destroy(min);
					_alloc.deallocate(min, 1);
				}
				else
				{
					if (A == _root)
					{
						if (_root->left_child == 0)
							_root = A->right_child;
						else
							_root = A->left_child;
						_root->parent = 0;
					}
					else if (A->left_child == 0)
					{
						if (B->left_child == A)
							B->left_child = A->right_child;
						else
							B->right_child = A->right_child;
						A->right_child->parent = A->parent;
					}
					else if (A->right_child == 0)
					{
						if (B->left_child == A)
							B->left_child = A->left_child;
						else
							B->right_child = A->left_child;
						A->left_child->parent = A->parent;
					}
					_alloc.destroy(A);
					_alloc.deallocate(A, 1);
				}
				if (_root) {
					set_rend(_root);
					set_end(_root);
				}
			}
			--_size;
			return true;
		}

		iterator lower_bound(const key_type& k)
		{
			for (iterator it = begin(); it != end(); ++it)
			{
				if (_comp(k, it->first) || (!_comp(k, it->first) && !_comp(it->first, k)))
					return it;
			}
			return end();
		}

		iterator upper_bound(const key_type& k)
		{
			for (iterator it = begin(); it != end(); ++it)
			{
				if (!_comp(k, it->first) && !_comp(it->first, k))
					return ++it;
				if (_comp(k, it->first))
					return it;
			}
			return end();
		}

		void clear()
		{
			_end->parent->right_child = 0;
			_rend->parent->left_child = 0;
			clear(_root);
			_size = 0;
			_root = 0;
		}

		size_type size() const
		{
			return _size;
		}

		iterator begin() const
		{
			if (!_root)
				return iterator(0);
			return iterator(_rend->parent);
		}

		iterator rbegin() const
		{
			if (!_root)
				return iterator(0);
			return iterator(_end->parent);
		}

		iterator end() const
		{
			if (!_root)
				return iterator(0);
			return iterator(_end);
		}

		iterator rend() const
		{
			if (!_root)
				return iterator(0);
			return iterator(_rend);
		}

		T base()
		{
			return _root;
		}

		void swap(Tree& x)
		{
			std::swap(_root, x._root);
			std::swap(_rend, x._rend);
			std::swap(_end, x._end);
			std::swap(_size, x._size);
			std::swap(_alloc, x._alloc);
			std::swap(_comp, x._comp);
		}

		size_type max_size() const
		{
			return _alloc.max_size();
		}
	private:
		void fill(Node<value_type> *node)
		{
			if (node) {
				add(node->value);
				fill(node->left_child);
				fill(node->right_child);
			}
		}

		void clear(Node<value_type> *node)
		{
			if (node) {
				clear(node->right_child);
				clear(node->left_child);
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}
		}

		void set_end(Node<value_type> *node) const
		{
			Node<value_type>* tmp = node;
			while (tmp->right_child)
				tmp = tmp->right_child;
			tmp->right_child = _end;
			_end->parent = tmp;
		}

		void set_rend(Node<value_type> *node) const
		{
			Node<value_type>* tmp = node;
			while (tmp->left_child)
				tmp = tmp->left_child;
			tmp->left_child = _rend;
			_rend->parent = tmp;
		}
	};
}

#endif
