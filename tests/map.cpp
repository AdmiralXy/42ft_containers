#include <ctime>
#include <map>
#include "map.hpp"
#include "utilities.hpp"

// Utility

template<typename T>
bool equal(const ft::map<int, int> &map1, const std::map<int, int> &map2)
{
	return ft::equal(map1.begin(), map1.end(), map2.begin()) &&
			map1.size() == map2.size();
}

void run_case(std::string case_name, ft::map<int, int> (*cf1)(), std::map<int, int> (*cf2)())
{
	time_t ft_start = timestamp();
	ft::map<int, int> v1 = cf1();
	time_t ft_end = timestamp();

	time_t std_start = timestamp();
	std::map<int, int> v2 = cf2();
	time_t std_end = timestamp();

	print_result(case_name, true, ft_end - ft_start, std_end - std_start);
}

// Tests

template<typename T>
T default_constructor()
{
	T map;
	return map;
}

void map()
{
	print_title("Map");
	run_case("Constructor", &default_constructor< ft::map<int, int> >, &default_constructor< std::map<int, int> >);
}
