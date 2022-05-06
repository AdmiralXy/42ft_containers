#include <iostream>
#include <stack>
#include "../src/stack.hpp"
#include <vector>
#include "../src/vector.hpp"
#include <map>
#include "../src/map.hpp"
#include "../src/utility/tree.hpp"

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
	//std::map<int, int> map;
	ft::Tree< std::pair<int, int> > map;
	for (int i = 0; i < 100000; ++i) {
		map.add(std::pair<int, int>(i, i));
	}
	std::cout << map.size() << std::endl;
}
