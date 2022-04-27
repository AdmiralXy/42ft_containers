#include <iostream>
#include <stack>
#include "src/stack.hpp"
#include <vector>

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
	std::vector<std::string> vector(5, "text");

	ft::stack<std::string, std::vector<std::string> > stack(vector);

	print_stack(stack);
}
