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
	User *user1 = new User(1);
	User *user2 = new User(2);
	User *user3 = new User(3);
	User *user4 = new User(4);
	User *user5 = new User(5);

	ft::map<User*, int> map;

	map.insert(ft::make_pair(user1, 5));
	map.insert(ft::make_pair(user2, 5));
	map.insert(ft::make_pair(user4, 5));
	map.insert(ft::make_pair(user3, 5));
	map.insert(ft::make_pair(user5, 5));
	map.insert(ft::make_pair(user3, 5));

	std::cout << map.size() << std::endl;
	delete user1;
	delete user2;
	delete user3;
	delete user4;
	delete user5;
}
