#ifndef INC_42FT_CONTAINERS_TREE_H
#define INC_42FT_CONTAINERS_TREE_H

namespace ft
{
	template <class T>
	struct Tree_node
	{
		T value;
		Tree_node* left_child;
		Tree_node* right_child;

		explicit Tree_node(T value) : value(value), left_child(0), right_child(0)
		{

		}

		Tree_node(T value, Tree_node *l, Tree_node *r) : value(value), left_child(l), right_child(r)
		{

		}
	};

	template <class T>
	class Binary_tree {
	private:
		Tree_node<T>* _root;
		int _size;
	public:
		Binary_tree() : _root(0), _size(0) { }

		explicit Binary_tree(T value) : _size(1)
		{
			_root = new Tree_node<T>(value);
		}

		~Binary_tree()
		{
			Clear(_root);
		}

		bool add(T value)
		{
			if (_root == 0)
				_root = new Tree_node<T>(value);
			else
			{
				Tree_node<T>* A = _root;
				Tree_node<T>* B = A;
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
					B->left_child = new Tree_node<T>(value);
				else
					B->right_child = new Tree_node<T>(value);
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
				Tree_node<T>* A = _root;
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
				Tree_node<T>* A = _root;
				Tree_node<T>* B = A;

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
					Tree_node<T>* B_parent = B;
					for (Tree_node<T>* tempSearch = A->right_child; tempSearch != 0;)
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

		//int height();
		int size()
		{
			return _size;
		}
	private:
		void default_print(Tree_node<T> *A, int space)
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
		void Clear(Tree_node<T> *A)
		{
			if (A) {
				Clear(A->right_child);
				Clear(A->left_child);
				delete A;
			}
		}
	public:
		void print()
		{
			default_print(_root, 0);
		}

		//void print_pre_order();
		//void print_in_order();
		//void print_post_order();
	};
}

#endif
