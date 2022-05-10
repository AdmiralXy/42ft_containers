#include <iostream>
#include <stack>
#include "../src/stack.hpp"
#include <vector>
#include "../src/vector.hpp"
#include <map>
#include "../src/map.hpp"
#include "../src/utility/utility.hpp"

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
//	std::map<int, int> map;
//
//	map.insert(std::pair<int, int>(1, 10));
//	map.insert(std::pair<int, int>(2, 10));
//	map.insert(std::pair<int, int>(3, 10));
//
//	std::map<int, int>::iterator iterator(map.begin());
//	for (std::map<int, int>::size_type i = 0; i < map.size(); i++)
//	{
//		std::cout << iterator->first << std::endl;
//		std::cout << &iterator << std::endl;
//		iterator++;
//	}
//
//	std::cout << &iterator << std::endl;
//	std::cout << iterator->first << std::endl;

//	std::map<int, int> map;
//
//	map.insert(std::pair<int, int>(1, 10));
//	map.insert(std::pair<int, int>(2, 10));
//	map.insert(std::pair<int, int>(3, 10));
//
//	std::map<int, int>::iterator iterator = map.end();
//
//	std::cout << iterator->first << ", " << &(iterator->first) << std::endl;
//	iterator--;
//	std::cout << iterator->first << ", " << &(iterator->first) << std::endl;
//	iterator--;
//	std::cout << iterator->first << ", " << &(iterator->first) << std::endl;
//	iterator--;
//	std::cout << iterator->first << ", " << &(iterator->first) << std::endl;
//
//	iterator = map.end();
//	std::cout << std::endl << std::endl << std::endl;
//	iterator++;
//	std::cout << iterator->first << ", " << &(iterator->first) << std::endl;
//	iterator++;
//	std::cout << iterator->first << ", " << &(iterator->first) << std::endl;
//	iterator++;
//	std::cout << iterator->first << ", " << &(iterator->first) << std::endl;

	ft::Tree<ft::pair<int, int> > tree;
	tree.add(ft::pair<int, int>(100, 10));
	tree.add(ft::pair<int, int>(35, 10));
	tree.add(ft::pair<int, int>(56, 10));
	tree.add(ft::pair<int, int>(1, 10));
	tree.add(ft::pair<int, int>(2, 10));
	tree.add(ft::pair<int, int>(3, 10));
	tree.add(ft::pair<int, int>(5, 10));
	tree.add(ft::pair<int, int>(7, 10));
	tree.add(ft::pair<int, int>(18, 10));
	ft::tree_iterator<ft::pair<int, int> > iterator(tree.begin());

	for (; iterator != ft::tree_iterator<ft::pair<int, int> >(tree.end()) ;)
	{
		std::cout << *iterator << std::endl;
		iterator++;
	}
}
