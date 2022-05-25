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
	std::map<std::string, int> tmp;

	tmp.insert(std::make_pair("Hello!", 2745785));
	tmp.insert(std::make_pair("Some", 341643213));
	tmp.insert(std::make_pair("AAAAAAA", 2214436321));
	tmp.insert(std::make_pair("ZZZZZZZ", 253454312));
	tmp.insert(std::make_pair("Maybe....", 543151252));
	tmp.insert(std::make_pair("100/100", 54543532));

	for (std::map<std::string, int>::iterator i = tmp.begin(); i != tmp.end(); ++i)
	{
		std::cout << i->first << " ";
	}
	std::cout << std::endl;

	ft::map<std::string, int> structure(tmp.begin(), tmp.end());

	for (ft::map<std::string, int>::iterator i = structure.begin(); i != structure.end(); ++i)
	{
		std::cout << i->first << " ";
	}
	std::cout << std::endl;
}
