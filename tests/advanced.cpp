#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <map>
#include "map.hpp"
#include <vector>
#include "vector.hpp"
#include <stack>
#include "stack.hpp"
#include <list>
#include "utilities.hpp"

// Utility

class User
{
private:
	int id;
	std::string name;
public:
	explicit User(int id) : id(id), name("default") {}

	bool operator<(const User &rhs) const
	{
		if (id < rhs.id)
			return true;
		if (rhs.id < id)
			return false;
		return name < rhs.name;
	}

	bool operator>(const User &rhs) const
	{
		return rhs < *this;
	}

	bool operator<=(const User &rhs) const
	{
		return !(rhs < *this);
	}

	bool operator>=(const User &rhs) const
	{
		return !(*this < rhs);
	}
};

User *user1;
User *user2;
User *user3;
User *user4;
User *user5;

template<typename T>
bool equal(ft::map<User*, T> &map1, std::map<User*, T> &map2)
{
	if (map1.empty() && map2.empty())
		return true;
	if (map1.size() != map2.size())
		return false;
	typename ft::map<User*, T>::iterator it1 = map1.begin();
	typename std::map<User*, T>::iterator it2 = map2.begin();
	while (it1 != map1.end())
	{
		if (it1->first != it2->first || it1->second != it2->second)
			return false;
		it1++;
		it2++;
	}
	return true;
}

template <typename T, typename U>
bool equal(ft::stack<T, U> stack1, std::stack<T, U> stack2)
{
	if (stack1.size() != stack2.size())
		return false;
	for (typename ft::stack<T>::size_type i = stack1.size(); i > 0; --i)
	{
		if (stack1.top() != stack2.top())
			return false;
		stack1.pop();
		stack2.pop();
	}
	return true;
}

void run_case(std::string case_name, ft::map<User*, int> (*cf1)(), std::map<User*, int> (*cf2)())
{
	time_t ft_start = timestamp();
	ft::map<User*, int> v1 = cf1();
	time_t ft_end = timestamp();

	time_t std_start = timestamp();
	std::map<User*, int> v2 = cf2();
	time_t std_end = timestamp();

	print_result(case_name, equal(v1, v2), ft_end - ft_start, std_end - std_start);
}

void run_case(std::string case_name, ft::stack<User*, std::vector<User*> > (*cf1)(), std::stack<User*, std::vector<User*> > (*cf2)())
{
	time_t ft_start = timestamp();
	ft::stack<User*, std::vector<User*> > v1 = cf1();
	time_t ft_end = timestamp();

	time_t std_start = timestamp();
	std::stack<User*, std::vector<User*> > v2 = cf2();
	time_t std_end = timestamp();

	print_result(case_name, equal(v1, v2), ft_end - ft_start, std_end - std_start);
}

void run_case(std::string case_name, ft::stack<User*, std::deque<User*> > (*cf1)(), std::stack<User*, std::deque<User*> > (*cf2)())
{
	time_t ft_start = timestamp();
	ft::stack<User*, std::deque<User*> > v1 = cf1();
	time_t ft_end = timestamp();

	time_t std_start = timestamp();
	std::stack<User*, std::deque<User*> > v2 = cf2();
	time_t std_end = timestamp();

	print_result(case_name, equal(v1, v2), ft_end - ft_start, std_end - std_start);
}

void run_case(std::string case_name, ft::stack<User*, std::list<User*> > (*cf1)(), std::stack<User*, std::list<User*> > (*cf2)())
{
	time_t ft_start = timestamp();
	ft::stack<User*, std::list<User*> > v1 = cf1();
	time_t ft_end = timestamp();

	time_t std_start = timestamp();
	std::stack<User*, std::list<User*> > v2 = cf2();
	time_t std_end = timestamp();

	print_result(case_name, equal(v1, v2), ft_end - ft_start, std_end - std_start);
}

// Tests

template<typename T>
T map_iterators_validate()
{
	T map_tmp;
	map_tmp.insert(std::make_pair(user1, 0));
	map_tmp.insert(std::make_pair(user2, 0));
	map_tmp.insert(std::make_pair(user3, 0));
	map_tmp.insert(std::make_pair(user4, 0));
	map_tmp.insert(std::make_pair(user5, 0));
	typename T::iterator iterator = map_tmp.begin();
	while (map_tmp.size())
		map_tmp.erase(iterator++);
	map_tmp.insert(std::make_pair(user2, 0));
	typename T::iterator iterator2 = map_tmp.begin();
	map_tmp.insert(std::make_pair(user3, 0));
	map_tmp.insert(std::make_pair(user4, 0));
	map_tmp.insert(std::make_pair(user1, 0));
	T map(iterator2, map_tmp.end());
	return map;
}

template<typename T>
T stack_containers_compatibility()
{
	T stack;
	stack.push(user1);
	stack.push(user2);
	stack.push(user3);
	stack.push(user4);
	stack.push(user5);
	return stack;
}

void advanced()
{
	user1 = new User(1);
	user2 = new User(2);
	user3 = new User(3);
	user4 = new User(4);
	user5 = new User(5);
	print_title("Advanced tests");
	run_case("[ Map ] Validate iter-s with insert/erase", &map_iterators_validate< ft::map<User*, int> >, &map_iterators_validate< std::map<User*, int> >);
	run_case("[Stack] Compatibility with std::vector", &stack_containers_compatibility< ft::stack<User*, std::vector<User*> > >, &stack_containers_compatibility< std::stack<User*, std::vector<User*> > >);
	run_case("[Stack] Compatibility with std::deque", &stack_containers_compatibility< ft::stack<User*, std::deque<User*> > >, &stack_containers_compatibility< std::stack<User*, std::deque<User*> > >);
	run_case("[Stack] Compatibility with std::list", &stack_containers_compatibility< ft::stack<User*, std::list<User*> > >, &stack_containers_compatibility< std::stack<User*, std::list<User*> > >);
	delete user1;
	delete user2;
	delete user3;
	delete user4;
	delete user5;
}
