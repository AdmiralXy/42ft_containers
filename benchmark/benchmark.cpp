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
	ft::map<int, int> map;

	map.insert(ft::make_pair(1, 2));
	map.insert(ft::make_pair(3, 4));
	map.insert(ft::make_pair(5, 6));

	ft::map<int, int>::reverse_iterator it = map.rbegin();
	// 5 3 1
	for (; it != map.rend(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//	std::map<int, int> tmp;
//
//	tmp.insert(std::make_pair(1, 2));
//	tmp.insert(std::make_pair(3, 4));
//	tmp.insert(std::make_pair(5, 6));
//
//	for (std::map<int, int>::reverse_iterator i = tmp.rbegin(); i != tmp.rend(); ++i)
//	{
//		std::cout << i->first << std::endl;
//	}
//
//	ft::map<int, int> structure(tmp.begin(), tmp.end());
//
//	for (ft::map<int, int>::iterator i = structure.begin(); i != structure.end(); ++i)
//	{
//		std::cout << *i << std::endl;
//	}
}
