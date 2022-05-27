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

class TemplateMap
{
public:
	static std::map<int, int> getSmallMap()
	{
		std::srand(SEED);
		std::map<int, int> map;
		for (int i = 0; i < 15; ++i)
			map.insert(std::make_pair(std::rand(), std::rand()));
		return map;
	}

	static std::map<int, int> getMediumMap()
	{
		std::srand(SEED);
		std::map<int, int> map;
		for (int i = 0; i < 500; ++i)
			map.insert(std::make_pair(std::rand(), std::rand()));
		return map;
	}

	static std::map<int, int> getLargeMap()
	{
		std::srand(SEED);
		std::map<int, int> map;
		for (int i = 0; i < 5000; ++i)
			map.insert(std::make_pair(std::rand(), std::rand()));
		return map;
	}

	static std::vector<std::pair<int, int> > getLargeVector()
	{
		std::srand(SEED);
		std::vector<std::pair<int, int> > vector;
		for (int i = 0; i < 5000; ++i)
			vector.insert(vector.end(), std::make_pair(std::rand(), std::rand()));
		return vector;
	}
};

std::map<int, int> smallMap = TemplateMap::getSmallMap();
std::map<int, int> mediumMap = TemplateMap::getMediumMap();
std::map<int, int> largeMap = TemplateMap::getLargeMap();

std::vector<std::pair<int, int> > largeVector = TemplateMap::getLargeVector();

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
	std::srand(SEED);
	T map(mediumMap.begin(), mediumMap.end());
	return map;
}

template<typename T>
T constructor_copy()
{
	std::srand(SEED);
	T map_tmp(mediumMap.begin(), mediumMap.end());
	T map(map_tmp);
	return map;
}

template<typename T>
T operator_assign()
{
	std::srand(SEED);
	T map_tmp(mediumMap.begin(), mediumMap.end());
	T map;
	map = map_tmp;
	return map;
}

template<typename T>
T begin()
{
	T map_tmp(mediumMap.begin(), mediumMap.end());
	T map;
	map.insert(*(map_tmp.begin()));
	map.insert(*(++map_tmp.begin()));
	map.insert(*(map.begin()));
	return map;
}

template<typename T>
T end()
{
	T map_tmp(mediumMap.begin(), mediumMap.end());
	T map;
	map.insert(*(--map_tmp.end()));
	map.insert(*(--(--map_tmp.end())));
	map.insert(*(--map.end()));
	return map;
}

template<typename T>
T rbegin()
{
	T map_tmp(mediumMap.begin(), mediumMap.end());
	T map;
	map.insert(*(map_tmp.rbegin()));
	map.insert(*(++map_tmp.rbegin()));
	map.insert(*(map.rbegin()));
	return map;
}

template<typename T>
T rend()
{
	T map_tmp(mediumMap.begin(), mediumMap.end());
	T map;
	map.insert(*(--map_tmp.rend()));
	map.insert(*(--(--map_tmp.rend())));
	map.insert(*(--map.rend()));
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

// TODO add return validate
template<typename T>
T insert_val()
{
	std::srand(SEED);
	T map;
	for (int i = 0; i < N; ++i)
		map.insert(std::make_pair(std::rand(), std::rand()));
	return map;
}

template<typename T>
T insert_pos_val()
{
	std::srand(SEED);
	T map;
	for (int i = 0; i < N; ++i)
		map.insert(map.end(), std::make_pair(std::rand(), std::rand()));
	return map;
}

template<typename T>
T insert_iterators()
{
	std::srand(SEED);
	T map;
	map.insert(largeVector.begin(), largeVector.end());
	return map;
}

template<typename T>
T erase_position()
{
	// TODO add test
	T map(mediumMap.begin(), mediumMap.end());
	return map;
}

template<typename T>
T erase_key()
{
	// TODO add test
	T map(mediumMap.begin(), mediumMap.end());
	return map;
}

template<typename T>
T erase_iterators()
{
	// TODO add test
	T map(mediumMap.begin(), mediumMap.end());
	return map;
}

template<typename T>
T swap()
{
	T map_tmp(mediumMap.begin(), mediumMap.end());
	T map(smallMap.begin(), smallMap.end());
	map.swap(map_tmp);
	return map;
}

template<typename T>
T clear()
{
	T map(mediumMap.begin(), mediumMap.end());
	map.clear();
	return map;
}

template<typename T>
T key_comp()
{
	// TODO add test
	T map(mediumMap.begin(), mediumMap.end());
	map.clear();
	return map;
}

template<typename T>
T value_comp()
{
	// TODO add test
	T map(mediumMap.begin(), mediumMap.end());
	map.clear();
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
	run_case("operator[]", &operator_index< ft::map<int, int> >, &operator_index< std::map<int, int> >);
//	run_case("insert(val)", &insert_val< ft::map<int, int> >, &insert_val< std::map<int, int> >);
//	run_case("insert(position, val)", &insert_pos_val< ft::map<int, int> >, &insert_pos_val< std::map<int, int> >);
//	run_case("insert(iterators)", &insert_iterators< ft::map<int, int> >, &insert_iterators< std::map<int, int> >);
	run_case("erase(position)", &erase_position< ft::map<int, int> >, &erase_position< std::map<int, int> >);
	run_case("erase(key)", &erase_key< ft::map<int, int> >, &erase_key< std::map<int, int> >);
	run_case("erase(iterators)", &erase_iterators< ft::map<int, int> >, &erase_iterators< std::map<int, int> >);
	run_case("swap", &swap< ft::map<int, int> >, &swap< std::map<int, int> >);
	run_case("clear", &clear< ft::map<int, int> >, &clear< std::map<int, int> >);
	run_case("key_comp", &key_comp< ft::map<int, int> >, &key_comp< std::map<int, int> >);
	run_case("value_comp", &value_comp< ft::map<int, int> >, &value_comp< std::map<int, int> >);
}
