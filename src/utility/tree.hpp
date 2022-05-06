#ifndef INC_42FT_CONTAINERS_TREE_H
#define INC_42FT_CONTAINERS_TREE_H

namespace ft
{
	template <class T>
	struct Node
	{
		T value;
		Node* left_child;
		Node* right_child;

		explicit Node(T value) : value(value), left_child(0), right_child(0)
		{

		}

		Node(T value, Node *l, Node *r) : value(value), left_child(l), right_child(r)
		{

		}
	};

	template <class T>
	class Tree {
	private:
		Node<T>* _root;
		int _size;
	public:
		Tree() : _root(0), _size(0) { }

		explicit Tree(T value) : _size(1)
		{
			_root = new Node<T>(value);
		}

		~Tree()
		{
			Clear(_root);
		}

		bool add(T value)
		{
			if (_root == 0)
				_root = new Node<T>(value);
			else
			{
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
				if (value < B->value)
					B->left_child = new Node<T>(value);
				else
					B->right_child = new Node<T>(value);
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
					delete A;
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
					delete B;
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
					delete A;
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
		void Clear(Node<T> *A)
		{
			if (A) {
				Clear(A->right_child);
				Clear(A->left_child);
				delete A;
			}
		}
	};
}

#endif
