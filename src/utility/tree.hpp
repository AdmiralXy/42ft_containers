#ifndef INC_42FT_CONTAINERS_TREE_H
#define INC_42FT_CONTAINERS_TREE_H

namespace ft
{
	template <class T>
	struct Node
	{
		T								value;
		typedef Node<T>*				link_type;
		Node<T>*						parent;
		Node<T>*						left_child;
		Node<T>*						right_child;

		explicit Node() : parent(0), left_child(0), right_child(0) {}

		explicit Node(const T& value) : value(value), parent(0), left_child(0), right_child(0) {}

		explicit Node(T value, Node *parent) : value(value), parent(parent), left_child(0), right_child(0) {}

		static Node<T>* minimum(link_type x)
		{
			while (x->left_child != 0)
				x = x->left_child;
			return x;
		}

		static Node<T>* maximum(link_type x)
		{
			while (x->right_child != 0)
				x = x->right_child;
			return x;
		}

		T* valptr()
		{
			return std::__addressof(value);
		}

		const T* valptr() const
		{
			return std::__addressof(value);
		}
	};

	template <class T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
	class Tree
	{
	public:
		typedef typename Alloc::template rebind<Node<T> >::other	allocator_type;
	private:
		Node<T>*		_root;
		Node<T>*		_end;
		int				_size;
		allocator_type	_alloc;
	public:
		explicit Tree(const allocator_type &alloc = allocator_type()) : _root(0), _size(0), _alloc(alloc)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, Node<T>());
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

		bool add(T value)
		{
			if (_root == 0)
			{
				_root = _alloc.allocate(1);
				_alloc.construct(_root, Node<T>(value));
				set_end(_root);
			}
			else
			{
				_end->parent->right_child = 0;
				Node<T>* A = _root;
				Node<T>* B = A;
				while (A != 0)
				{
					if (A->value == value)
						return false;
					B = A;
					if (value < A->value)
						A = A->left_child;
					else
						A = A->right_child;
				}
				if (value < B->value) {
					B->left_child = _alloc.allocate(1);
					_alloc.construct(B->left_child, Node<T>(value, B));
				} else {
					B->right_child = _alloc.allocate(1);
					_alloc.construct(B->right_child, Node<T>(value, B));
				}
				set_end(_root);
			}
			++_size;
			return true;
		}

		bool find(T value)
		{
			if (_root == 0)
				return false;
			else
			{
				Node<T>* A = _root;
				while (A != 0)
				{
					if (A->value == value)
						return true;
					else if (value < A->value)
						A = A->left_child;
					else
						A = A->right_child;
				}
			}
			return false;
		}

		void remove(T value)
		{
			if (_root != 0) {
				Node<T>* A = _root;
				Node<T>* B = A;

				while (A->value != value)
				{
					B = A;
					if (value < A->value)
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
					Node<T>* B_parent = B;
					for (Node<T>* tempSearch = A->right_child; tempSearch != 0;)
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

		int size()
		{
			return _size;
		}

        void print()
        {
            default_print(_root, 0);
        }

		void inorder()
		{
			inorder_print(_root);
		}

		Node<T>* begin()
		{
			Node<T>* tmp = _root;
			while (tmp->left_child)
				tmp = tmp->left_child;
			return tmp;
		}

		Node<T>* end()
		{
			return _end;
		}

		T base()
		{
			return _root;
		}
	private:
		void default_print(Node<T> *A, int space)
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

		void inorder_print(Node<T> *A)
		{
			if (A) {
				inorder_print(A->left_child);
				std::cout << A->value << " ";
				inorder_print(A->right_child);
			}
		}

		void clear(Node<T> *node)
		{
			if (node) {
				clear(node->right_child);
				clear(node->left_child);
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}
		}

		void set_end(Node<T> *node)
		{
			Node<T>* tmp = node;
			while (tmp->right_child)
				tmp = tmp->right_child;
			tmp->right_child = _end;
			_end->parent = tmp;
		}
	};
}

#endif
