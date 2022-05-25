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
	ft::map<int, int> temp;

	temp.insert(std::make_pair(1, 5));

	temp.insert(*(temp.begin()));

	std::cout << temp.size() << std::endl;
}
