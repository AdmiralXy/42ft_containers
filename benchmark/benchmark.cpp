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

	map.insert(std::make_pair(2, 1));
	map.insert(std::make_pair(7, 2));
	map.insert(std::make_pair(-1, 3));

	ft::map<int, int> map2;

	map2.insert(std::make_pair(54, 1));
	map2.insert(std::make_pair(71231, 2));
	map2.insert(std::make_pair(-6611, 3));

	ft::swap(map, map2);

	std::cout << map.begin()->first << std::endl;
}
