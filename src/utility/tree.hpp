#ifndef INC_42FT_CONTAINERS_TREE_H
#define INC_42FT_CONTAINERS_TREE_H

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

	template <class Key, class T, typename Compare = std::less<Key>, typename Alloc = std::allocator<T> >
	class Tree
	{
	public:
		typedef ft::pair<const Key, T>										value_type;
		typedef typename Alloc::template rebind<Node<value_type> >::other	allocator_type;
		typedef Compare														key_compare;
	private:
		Node<value_type>*		_root;
		Node<value_type>*		_rend;
		Node<value_type>*		_end;
		int						_size;
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

		Tree(const Tree &x) : _size() { *this = x; }

		Tree& operator=(const Tree& x)
		{
			if (this == &x)
				return *this;
			clear(_root);
			_root = x.base();
			_size = x.size();
			return *this;
		}

		~Tree() { clear(_root); }

		bool add(const value_type &value)
		{
			if (_root == 0)
			{
				_root = _alloc.allocate(1);
				_alloc.construct(_root, Node<value_type>(value));
			}
			else
			{
				_end->parent->right_child = 0;
				_rend->parent->left_child = 0;
				Node<value_type>* A = _root;
				Node<value_type>* B = A;
				while (A != 0)
				{
					if (A->value.first == value.first)
						return false;
					B = A;
					if (_comp(value.first, A->value.first))
						A = A->left_child;
					else
						A = A->right_child;
				}
				if (_comp(value.first, B->value.first)) {
					B->left_child = _alloc.allocate(1);
					_alloc.construct(B->left_child, Node<value_type>(value, B));
				} else {
					B->right_child = _alloc.allocate(1);
					_alloc.construct(B->right_child, Node<value_type>(value, B));
				}
			}
			set_rend(_root);
			set_end(_root);
			++_size;
			return true;
		}

		bool find(const value_type &value)
		{
			if (_root == 0)
				return false;
			else
			{
				Node<value_type>* A = _root;
				while (A != 0)
				{
					if (A->value == value)
						return true;
					else if (_comp(value.first, A->value.first))
						A = A->left_child;
					else
						A = A->right_child;
				}
			}
			return false;
		}

		void remove(const value_type &value)
		{
			if (_root != 0) {
				Node<value_type>* A = _root;
				Node<value_type>* B = A;

				while (A->value != value)
				{
					B = A;
					if (_comp(value.first, A->value.first))
						A = A->left_child;
					else
						A = A->right_child;
				}
				if (A->left_child == 0 && A->right_child == 0) {
					if (A == _root)
						_root = 0;
					else if (B->left_child == A)
						B->left_child = 0;
					else
						B->right_child = 0;
					_alloc.destroy(A);
					_alloc.deallocate(A, 1);
				} else if (A->left_child && A->right_child) {
					Node<value_type>* B_parent = B;
					for (Node<value_type>* tempSearch = A->right_child; tempSearch != 0;)
					{
						B_parent = B;
						B = tempSearch;
						tempSearch = tempSearch->left_child;
					}
					A->value = B->value;
					if (B->right_child == 0) {
						if (B_parent->left_child == B)
							B_parent->left_child = 0;
						else
							B_parent->right_child = 0;
					} else {
						if (B_parent->left_child == B)
							B_parent->left_child = B->right_child;
						else
							B_parent->right_child = B->right_child;
					}
					_alloc.destroy(B);
					_alloc.deallocate(B, 1);
				} else {
					if (A == B) {
						if (A->left_child == 0)
							_root = A->right_child;
						else
							_root = A->left_child;
					} else if (A->left_child == 0) {
						if (B->left_child == A)
							B->left_child = A->right_child;
						else
							B->right_child = A->right_child;
					} else {
						if (B->left_child == A)
							B->left_child = A->left_child;
						else
							B->right_child = A->left_child;
					}
					_alloc.destroy(A);
					_alloc.deallocate(A, 1);
				}
			}
		}

		int size() const
		{
			return _size;
		}

		// TODO remove func
        void print()
        {
            default_print(_root, 0);
        }

		Node<value_type>* begin()
		{
			return _rend->parent;
		}

		Node<value_type>* rbegin()
		{
			return _end->parent;
		}

		Node<value_type>* end()
		{
			return _end;
		}

		Node<value_type>* rend()
		{
			return _rend;
		}

		T base()
		{
			return _root;
		}
	private:
		// TODO remove func
		void default_print(Node<value_type> *A, int space)
		{
			if (A)
			{
				default_print(A->right_child, space + 1);
				for (int i = 0; i < space; i++) std::cout << "  ";
				std::cout << A->value << std::endl;
				default_print(A->left_child, space + 1);
			} else {
				for (int i = 0; i < space; i++) std::cout << "  ";
				std::cout << "@" << std::endl;
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

		void set_end(Node<value_type> *node)
		{
			Node<value_type>* tmp = node;
			while (tmp->right_child)
				tmp = tmp->right_child;
			tmp->right_child = _end;
			_end->parent = tmp;
		}

		void set_rend(Node<value_type> *node)
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
