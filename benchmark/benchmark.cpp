#include "../src/map.hpp"
#include <iostream>
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
	ft::map<int, int> map;

	map.insert(ft::make_pair(2, 5));

	map.value_comp()(ft::make_pair(2, 5), ft::make_pair(2, 5));
map.find().
	std::cout << map.size() << std::endl;
}
