#include "../src/stack.hpp"
#include "../src/map.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <ctime>

template <typename T>
void print_map(T map)
{
	typename T::iterator iterator = map.begin();
	for (typename T::size_type i = map.size(); i > 0; --i)
	{
		std::cout << iterator->second << " ";
		iterator++;
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
	std::map<int, int> tmp;

	std::srand(std::time(0));
	for (int i = 0; i < 20; ++i)
	{
		tmp.insert(std::make_pair(std::rand() % 100, 2));
	}

	for (std::map<int, int>::reverse_iterator i = --(tmp.rend()); i != tmp.rbegin(); --i)
	{
		std::cout << i->first << " ";
	}
	std::cout << std::endl;

	ft::map<int, int> structure(tmp.begin(), tmp.end());

	for (ft::map<int, int>::reverse_iterator i = --(structure.rend()); i != structure.rbegin(); --i)
	{
		std::cout << i->first << " ";
	}
	std::cout << std::endl;
}
