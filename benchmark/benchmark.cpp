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

// TODO test initialize const_iterator from iterator & const_reverse_iterator from reverse_iterator (map, vector)
// TODO add test to compare const_iterator and iterators
// TODO test for same keys (map) (also check NULL)
// TODO add test STD vector/deque/list compatibility with ft::stack
// TODO learn value compare
// TODO add benchmark test (produce two binaries that run the same tests: one with FT containers only, and the other one with the STL containers)
// TODO move all implementations (except templates) to .cpp files

int main()
{
	ft::map<int, int> tmp;
	tmp.insert(std::make_pair(1200, 0));
	ft::map<int, int>::iterator iterator = tmp.begin();
	tmp.insert(std::make_pair(1300, 0));
	tmp.insert(std::make_pair(1400, 0));
	tmp.insert(std::make_pair(50, 0));

	for (ft::map<int, int>::iterator iter = iterator; iter != tmp.end(); iter++)
		std::cout << iter->first << " ";
	std::cout << std::endl;
}
