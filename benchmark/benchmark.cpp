#include "../src/map.hpp"
#include <iostream>
#include <map>
#include <ctime>
#include <cstdlib>

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

// TODO tests for relational operators (map, vector)

int main()
{
//	ft::map<int, int> map;
//
//	map.insert(ft::make_pair(100, 0));
//	map.insert(ft::make_pair(50, 0));
//	map.insert(ft::make_pair(200, 0));
//	map.insert(ft::make_pair(300, 0));
//
//	map.erase(100);
//
//	for (ft::map<int, int>::iterator it = map.begin(); it != map.end(); ++it)
//	{
//		std::cout << it->first << " ";
//	}
//	std::cout << std::endl;

	ft::map<int, int> map;

	std::srand(std::time(0));
	for (int i = 0; i < 25; ++i)
		map.insert(ft::make_pair(std::rand() % 600, 0));

	for (int i = 0; i < 14; ++i)
	{
		map.erase(map.begin()->first);
	}

	for (ft::map<int, int>::iterator it = map.begin(); it != map.end(); ++it)
	{
		std::cout << it->first << " ";
	}
	std::cout << std::endl;
}
