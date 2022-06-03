#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <map>
#include "map.hpp"
#include "utilities.hpp"

// Utility

template<typename T>
bool equal(ft::map<T, T> &map1, std::map<T, T> &map2)
{
	if (map1.empty() && map2.empty())
		return true;
	if (map1.size() != map2.size())
		return false;
	typename ft::map<T, T>::iterator it1 = map1.begin();
	typename std::map<T, T>::iterator it2 = map2.begin();
	while (it1 != map1.end())
	{
		if (it1->first != it2->first || it1->second != it2->second)
			return false;
		it1++;
		it2++;
	}
	return true;
}

void run_case(std::string case_name, ft::map<int, int> (*cf1)(), std::map<int, int> (*cf2)())
{
	time_t ft_start = timestamp();
	ft::map<int, int> v1 = cf1();
	time_t ft_end = timestamp();

	time_t std_start = timestamp();
	std::map<int, int> v2 = cf2();
	time_t std_end = timestamp();

	print_result(case_name, equal(v1, v2), ft_end - ft_start, std_end - std_start);
}

class Random
{
private:
	std::map<int, int> *smallMap;
	std::map<int, int> *mediumMap;
	std::map<int, int> *largeMap;
	std::vector<std::pair<int, int> > *largeVector;
public:
	~Random()
	{
		delete smallMap;
		delete mediumMap;
		delete largeMap;
		delete largeVector;
	}

	std::map<int, int> *getSmallMap()
	{
		if (smallMap)
			return smallMap;
		std::srand(SEED);
		smallMap = new std::map<int, int>;
		for (int i = 0; i < 15; ++i)
			smallMap->insert(std::make_pair(std::rand(), std::rand()));
		return smallMap;
	}

	std::map<int, int> *getMediumMap()
	{
		if (mediumMap)
			return mediumMap;
		std::srand(SEED);
		mediumMap = new std::map<int, int>;
		for (int i = 0; i < 500; ++i)
			mediumMap->insert(std::make_pair(std::rand(), std::rand()));
		return mediumMap;
	}

	std::map<int, int> *getLargeMap()
	{
		if (largeMap)
			return largeMap;
		std::srand(SEED);
		largeMap = new std::map<int, int>;
		for (int i = 0; i < N; ++i)
			largeMap->insert(std::make_pair(std::rand(), std::rand()));
		return largeMap;
	}

	std::vector<std::pair<int, int> > *getLargeVector()
	{
		if (largeVector)
			return largeVector;
		std::srand(SEED);
		largeVector = new std::vector<std::pair<int, int> >;
		for (int i = 0; i < N; ++i)
			largeVector->insert(largeVector->end(), std::make_pair(std::rand(), std::rand()));
		return largeVector;
	}
};

Random randomData;

// Tests

template<typename T>
T default_constructor()
{
	T map;
	return map;
}

template<typename T>
T constructor_iterators()
{
	T map(randomData.getLargeVector()->begin(), randomData.getLargeVector()->end());
	return map;
}

template<typename T>
T constructor_copy()
{
	T map_tmp(randomData.getLargeVector()->begin(), randomData.getLargeVector()->end());
	const T& map(map_tmp);
	return map;
}

template<typename T>
T operator_assign()
{
	T map_tmp(randomData.getLargeVector()->begin(), randomData.getLargeVector()->end());
	T map;
	map = map_tmp;
	return map;
}

template<typename T>
T begin()
{
	T map_tmp(randomData.getSmallMap()->begin(), randomData.getSmallMap()->end());
	T map;
	map.insert(*(map_tmp.begin()));
	map.insert(*(++map_tmp.begin()));
	map.insert(*(map.begin()));
	return map;
}

template<typename T>
T end()
{
	T map_tmp(randomData.getSmallMap()->begin(), randomData.getSmallMap()->end());
	T map;
	map.insert(*(--map_tmp.end()));
	map.insert(*(--(--map_tmp.end())));
	map.insert(*(--map.end()));
	return map;
}

template<typename T>
T rbegin()
{
	T map_tmp(randomData.getSmallMap()->begin(), randomData.getSmallMap()->end());
	T map;
	map.insert(*(map_tmp.rbegin()));
	map.insert(*(++map_tmp.rbegin()));
	map.insert(*(map.rbegin()));
	return map;
}

template<typename T>
T rend()
{
	T map_tmp(randomData.getSmallMap()->begin(), randomData.getSmallMap()->end());
	T map;
	map.insert(*(--map_tmp.rend()));
	map.insert(*(--(--map_tmp.rend())));
	map.insert(*(--map.rend()));
	return map;
}

template<typename T>
T empty()
{
	std::map<int, int> std_map;
	T tmp_map1(randomData.getSmallMap()->begin(), randomData.getSmallMap()->end());
	T tmp_map2;
	std_map.insert(std::make_pair(tmp_map1.empty(), tmp_map2.empty()));
	T map(std_map.begin(), std_map.end());
	return map;
}

template<typename T>
T size()
{
	std::map<int, int> std_map;
	T tmp_map(randomData.getSmallMap()->begin(), randomData.getSmallMap()->end());
	std_map.insert(std::make_pair(tmp_map.size(), tmp_map.size()));
	T map(std_map.begin(), std_map.end());
	return map;
}

template<typename T>
T max_size()
{
	std::map<int, int> std_map;
	T tmp_map(randomData.getSmallMap()->begin(), randomData.getSmallMap()->end());
	std_map.insert(std::make_pair(tmp_map.max_size() > 0, tmp_map.max_size() > 0));
	T map(std_map.begin(), std_map.end());
	return map;
}

template<typename T>
T at()
{
	T map;
	try
	{
		map.at(0);
	}
	catch (...)
	{
		map.insert(std::make_pair(33, 33));
	}
	try
	{
		map.at(33);
	}
	catch (...)
	{
		map.insert(std::make_pair(0, 0));
	}
	return map;
}

template<typename T>
T operator_index()
{
	std::srand(SEED);
	T map;
	for (int i = 0; i < N; ++i)
		map[std::rand()] = std::rand();
	map[N / 2] = std::rand();
	map[N / 2] = std::rand();
	return map;
}

template<typename T>
T insert_val()
{
	std::srand(SEED);
	T map;
	for (int i = 0; i < N; ++i)
		map.insert(std::make_pair(std::rand(), std::rand()));
	map.insert(std::make_pair(map.insert(std::make_pair(std::rand(), std::rand())).second - (N / 2), std::rand()));
	return map;
}

template<typename T>
T insert_pos_val()
{
	std::srand(SEED);
	T map;
	for (int i = 0; i < N; ++i)
		map.insert(map.end(), std::make_pair(std::rand(), std::rand()));
	map.insert(map.end(), std::make_pair(map.insert(map.end(), std::make_pair(std::rand(), std::rand()))->second - (N / 2),  std::rand()));
	return map;
}

template<typename T>
T insert_iterators()
{
	T map;
	map.insert(randomData.getLargeVector()->begin(), randomData.getLargeVector()->end());
	return map;
}

template<typename T>
T erase_position()
{
	T map(randomData.getMediumMap()->begin(), randomData.getMediumMap()->end());
	map.erase(map.begin());
	map.erase((--map.end()));
	while (map.size())
		map.erase(map.begin());
	return map;
}

template<typename T>
T erase_key()
{
	T map(randomData.getMediumMap()->begin(), randomData.getMediumMap()->end());
	map.erase(map.begin()->first);
	map.erase((--map.end())->first);
	while (map.size())
		map.erase(map.begin()->first);
	return map;
}

template<typename T>
T erase_iterators()
{
	T map(randomData.getMediumMap()->begin(), randomData.getMediumMap()->end());
	map.erase(map.begin(), map.end());
	return map;
}

template<typename T>
T swap()
{
	T map_tmp(randomData.getMediumMap()->begin(), randomData.getMediumMap()->end());
	T map(randomData.getSmallMap()->begin(), randomData.getSmallMap()->end());
	map.swap(map_tmp);
	return map;
}

template<typename T>
T clear()
{
	T map(randomData.getMediumMap()->begin(), randomData.getMediumMap()->end());
	map.clear();
	return map;
}

template<typename T>
T key_comp()
{
	std::map<int, int> map_tmp;
	T map_tested;
	map_tmp.insert(std::make_pair(map_tested.key_comp()(5995, 4607), map_tested.key_comp()(4607, 5995)));
	map_tmp.insert(std::make_pair(map_tested.key_comp()(-654066, 682065), map_tested.key_comp()(682065, -654066)));
	map_tmp.insert(std::make_pair(map_tested.key_comp()(84689, 84689), map_tested.key_comp()(84689, 84689)));
	T map(map_tmp.begin(), map_tmp.end());
	return map;
}

template<typename T>
T value_comp()
{
	std::map<int, int> map_tmp;
	T map_tested;
	map_tmp.insert(std::make_pair(map_tested.value_comp()(std::make_pair(4607, 5995), std::make_pair(5995, 4607)), map_tested.value_comp()(std::make_pair(4607, 5995), std::make_pair(5995, 4607))));
	map_tmp.insert(std::make_pair(map_tested.value_comp()(std::make_pair(46057, 1235995), std::make_pair(5932195, 460721)), map_tested.value_comp()(std::make_pair(-4607, 599215), std::make_pair(5912395, 1234607))));
	map_tmp.insert(std::make_pair(map_tested.value_comp()(std::make_pair(1254364607, 2135995), std::make_pair(53214995, 46425607)), map_tested.value_comp()(std::make_pair(2134607, 5921395), std::make_pair(59575695, 4123607))));
	T map(map_tmp.begin(), map_tmp.end());
	return map;
}

template<typename T>
T find()
{
	std::map<int, int> std_map;
	std_map.insert(std::make_pair(1, 1));
	std_map.insert(std::make_pair(2, 2));
	std_map.insert(std::make_pair(3, 3));
	std_map.insert(std::make_pair(4, 4));
	std_map.insert(std::make_pair(5, 5));
	T map_tmp(std_map.begin(), std_map.end());
	T map;
	map.insert(std::make_pair((*map_tmp.find(5)).first, 1));
	map.insert(std::make_pair((*map_tmp.find(3)).first, 2));
	map.insert(std::make_pair((*--map_tmp.find(36)).first, 3));
	map.insert(std::make_pair((*--map_tmp.find(84)).first, 4));
	map.insert(std::make_pair((*map_tmp.find(1)).first, 5));
	return map;
}

template<typename T>
T count()
{
	T map;
	std::map<char,int> std_map;
	std_map['a'] = 101;
	std_map['c'] = 202;
	std_map['f'] = 303;
	for (char c = 'a'; c < 'h'; c++)
	{
		if (std_map.count(c) > 0)
			map.insert(std::make_pair(1, 0));
		else
			map.insert(std::make_pair(0, 1));
	}
	return map;
}

template<typename T>
T lower_bound()
{
	std::srand(SEED);
	T map_tmp(randomData.getMediumMap()->begin(), randomData.getMediumMap()->end());
	std::map<int, int> std_map;
	std_map.insert(std::make_pair((*map_tmp.lower_bound(randomData.getLargeVector()->begin()->first)).first, std::rand()));
	std_map.insert(std::make_pair((*--map_tmp.lower_bound((--(randomData.getMediumMap()->end()))->first + 100)).first, std::rand()));
	T map(std_map.begin(), std_map.end());
	return map;
}

template<typename T>
T upper_bound()
{
	std::srand(SEED);
	T map_tmp(randomData.getMediumMap()->begin(), randomData.getMediumMap()->end());
	std::map<int, int> std_map;
	std_map.insert(std::make_pair((*map_tmp.upper_bound(randomData.getLargeVector()->begin()->first)).first, std::rand()));
	std_map.insert(std::make_pair((*--map_tmp.upper_bound((--(randomData.getMediumMap()->end()))->first + 100)).first, std::rand()));
	T map(std_map.begin(), std_map.end());
	return map;
}

template<typename T>
T equal_range()
{
	std::srand(SEED);
	T map_tmp(randomData.getMediumMap()->begin(), randomData.getMediumMap()->end());
	std::map<int, int> std_map;
	ft::pair<typename T::iterator, typename T::iterator> equal_range = map_tmp.equal_range((++(++randomData.getLargeVector()->begin()))->first);
	typename T::iterator lower_bound = equal_range.first;
	typename T::iterator upper_bound = equal_range.second;
	std_map.insert(std::make_pair(upper_bound->first, std::rand()));
	std_map.insert(std::make_pair((++upper_bound)->first, std::rand()));
	std_map.insert(std::make_pair(lower_bound->first, std::rand()));
	std_map.insert(std::make_pair((++lower_bound)->first, std::rand()));
	(void)lower_bound;
	T map(std_map.begin(), std_map.end());
	return map;
}

template<typename T>
T get_allocator()
{
	T map;
	typename T::pointer ptr = map.get_allocator().allocate(5);
	if (ptr)
		map.insert(std::make_pair(5, 5));
	map.get_allocator().deallocate(ptr, 5);
	return map;
}

template<typename T>
T relational_operators()
{
	std::srand(SEED);
	std::map<int, int> std_map_tmp1;
	std::map<int, int> std_map_tmp2;
	for (int i = 0; i < 500; ++i)
		std_map_tmp1.insert(std::make_pair(std::rand(), std::rand()));
	for (int i = 0; i < 500; ++i)
		std_map_tmp2.insert(std::make_pair(std::rand(), std::rand()));
	T map1(std_map_tmp1.begin(), std_map_tmp1.end());
	T map2(std_map_tmp2.begin(), std_map_tmp2.end());
	T map3(std_map_tmp1.begin(), std_map_tmp1.end());;

	std::map<int, int> std_map;
	std_map.insert(std::make_pair(map1 == map2, 0));
	std_map.insert(std::make_pair(map1 == map3, 0));

	std_map.insert(std::make_pair(map1 != map2, 0));
	std_map.insert(std::make_pair(map1 != map3, 0));

	std_map.insert(std::make_pair(map1 < map2, 0));
	std_map.insert(std::make_pair(map1 < map3, 0));

	std_map.insert(std::make_pair(map1 <= map2, 0));
	std_map.insert(std::make_pair(map1 <= map3, 0));

	std_map.insert(std::make_pair(map1 > map2, 0));
	std_map.insert(std::make_pair(map1 > map3, 0));

	std_map.insert(std::make_pair(map1 >= map2, 0));
	std_map.insert(std::make_pair(map1 >= map3, 0));

	T map(std_map.begin(), std_map.end());
	return map;
}

void map()
{
	print_title("Map");
	run_case("Constructor", &default_constructor< ft::map<int, int> >, &default_constructor< std::map<int, int> >);
	run_case("Constructor(iterators)", &constructor_iterators< ft::map<int, int> >, &constructor_iterators< std::map<int, int> >);
	run_case("Copy constructor", &constructor_copy< ft::map<int, int> >, &constructor_copy< std::map<int, int> >);
	run_case("operator=", &operator_assign< ft::map<int, int> >, &operator_assign< std::map<int, int> >);
	run_case("begin", &begin< ft::map<int, int> >, &begin< std::map<int, int> >);
	run_case("end", &end< ft::map<int, int> >, &end< std::map<int, int> >);
	run_case("rbegin", &rbegin< ft::map<int, int> >, &rbegin< std::map<int, int> >);
	run_case("rend", &rend< ft::map<int, int> >, &rend< std::map<int, int> >);
	run_case("empty", &empty< ft::map<int, int> >, &empty< std::map<int, int> >);
	run_case("size", &size< ft::map<int, int> >, &size< std::map<int, int> >);
	run_case("max_size", &max_size< ft::map<int, int> >, &max_size< std::map<int, int> >);
	run_case("at", &at< ft::map<int, int> >, &at< std::map<int, int> >);
	run_case("operator[]", &operator_index< ft::map<int, int> >, &operator_index< std::map<int, int> >);
	run_case("insert(val)", &insert_val< ft::map<int, int> >, &insert_val< std::map<int, int> >);
	run_case("insert(position, val)", &insert_pos_val< ft::map<int, int> >, &insert_pos_val< std::map<int, int> >);
	run_case("insert(iterators)", &insert_iterators< ft::map<int, int> >, &insert_iterators< std::map<int, int> >);
	run_case("erase(position)", &erase_position< ft::map<int, int> >, &erase_position< std::map<int, int> >);
	run_case("erase(key)", &erase_key< ft::map<int, int> >, &erase_key< std::map<int, int> >);
	run_case("erase(iterators)", &erase_iterators< ft::map<int, int> >, &erase_iterators< std::map<int, int> >);
	run_case("swap", &swap< ft::map<int, int> >, &swap< std::map<int, int> >);
	run_case("clear", &clear< ft::map<int, int> >, &clear< std::map<int, int> >);
	run_case("key_comp", &key_comp< ft::map<int, int> >, &key_comp< std::map<int, int> >);
	run_case("value_comp", &value_comp< ft::map<int, int> >, &value_comp< std::map<int, int> >);
	run_case("find", &find< ft::map<int, int> >, &find< std::map<int, int> >);
	run_case("count", &count< ft::map<int, int> >, &count< std::map<int, int> >);
	run_case("lower_bound", &lower_bound< ft::map<int, int> >, &lower_bound< std::map<int, int> >);
	run_case("upper_bound", &upper_bound< ft::map<int, int> >, &upper_bound< std::map<int, int> >);
	run_case("equal_range", &equal_range< ft::map<int, int> >, &equal_range< std::map<int, int> >);
	run_case("get_allocator", &get_allocator< ft::map<int, int> >, &get_allocator< std::map<int, int> >);
	run_case("Relational operators", &relational_operators< ft::map<int, int> >, &relational_operators< std::map<int, int> >);
}
