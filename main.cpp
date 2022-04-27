#include <iostream>
#include <stack>
#include "src/stack.hpp"
#include <vector>
#include "src/vector.hpp"

template <typename T>
void print_stack(T stack)
{
	for (typename T::size_type i = stack.size(); i > 0; --i)
	{
		std::cout << stack.top() << " ";
		stack.pop();
	}
	std::cout << std::endl;
}

class User
{
public:
	int id;
	explicit User(int id) : id(id) {}
};

int main()
{
	std::stack<int> vector1(7, 3);
	ft::vector<int> vector2(10, 3);

	std::cout << (vector1 <= vector2) << std::endl;
}
