#include "utilities.hpp"
#include "vector.hpp"
#include <vector>

int N = 100;

// Utility

template<typename T>
bool equal(ft::vector<T> vector1, std::vector<T> vector2)
{
	return ft::equal(vector1.begin(), vector1.end(), vector2.begin()) &&
			vector1.size() == vector2.size();
}

void run_case(std::string case_name, ft::vector<int> (*cf1)(), std::vector<int> (*cf2)())
{
	time_t ft_start = timestamp();
	ft::vector<int> v1 = cf1();
	time_t ft_end = timestamp();

	time_t std_start = timestamp();
	std::vector<int> v2 = cf2();
	time_t std_end = timestamp();

	print_result(case_name, equal(v1, v2), ft_end - ft_start, std_end - std_start);
}

// Tests

template<typename T>
T default_constructor()
{
	T vector;
	return vector;
}

template<typename T>
T constructor_n_val()
{
	T vector(N, 5);
	return vector;
}

template<typename T>
T constructor_iterators()
{
	std::vector<int> v;
	v.assign(N, 3);
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T constructor_copy()
{
	std::vector<int> v;
	v.assign(N, 3);
	T vector_tmp(v.begin(), v.end());
	T vector(vector_tmp);
	return vector;
}

template<typename T>
T operator_assign()
{
	std::vector<int> v;
	v.assign(N, 3);
	T vector_tmp(v.begin(), v.end());
	T vector;
	vector = vector_tmp;
	return vector;
}

template<typename T>
T begin()
{
	std::vector<int> v(10, 10);
	T vector_tmp(3, 3);
	v.push_back(*(vector_tmp.begin()));
	v.push_back(*(vector_tmp.begin() + 1));
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T end()
{
	std::vector<int> v(10, 10);
	T vector_tmp(3, 3);
	v.push_back(*(vector_tmp.end() - 1));
	v.push_back(*(vector_tmp.end() - 2));
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T rbegin()
{
	std::vector<int> v(10, 10);
	T vector_tmp(3, 3);
	v.push_back(*(vector_tmp.rbegin()));
	v.push_back(*(vector_tmp.rbegin() + 1));
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T rend()
{
	std::vector<int> v(10, 10);
	T vector_tmp(3, 3);
	v.push_back(*(vector_tmp.rend() - 1));
	v.push_back(*(vector_tmp.rend() - 2));
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T size()
{
	T vector_tmp(100, 5);
	T vector_tmp2(vector_tmp.size(), vector_tmp.size());
	T vector(vector_tmp2.size(), vector_tmp.size());
	return vector;
}

template<typename T>
T max_size()
{
	T vector_tmp(5, 5);
	T vector_tmp2(5, vector_tmp.max_size());
	T vector(5, vector_tmp2.max_size());
	return vector;
}

template<typename T>
T resize()
{
	std::vector<int> v;
	T vector_tmp(1, 3);
	vector_tmp.resize(N, 5);
	v.push_back(*(vector_tmp.begin()));
	v.push_back(*(vector_tmp.end() - 1));
	v.push_back(vector_tmp.size());
	vector_tmp.resize(N / 2);
	v.push_back(*(vector_tmp.begin()));
	v.push_back(*(vector_tmp.end() - 1));
	v.push_back(vector_tmp.size());
	vector_tmp.resize(1);
	v.push_back(*(vector_tmp.begin()));
	v.push_back(*(vector_tmp.end() - 1));
	v.push_back(vector_tmp.size());
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T capacity()
{
	std::vector<int> v;
	T vector_tmp(3, 3);
	v.push_back(vector_tmp.capacity() > 0);
	v.push_back(vector_tmp.capacity() != 0);
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T empty()
{
	std::vector<int> v;
	T vector_tmp;
	T vector_tmp2(3, 3);
	v.push_back(vector_tmp.empty());
	v.push_back(vector_tmp2.empty());
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T reserve()
{
	std::vector<int> v;
	T vector_tmp(10, 10);
	vector_tmp.reserve(N / 2);
	v.push_back(((int)vector_tmp.capacity()) >= N / 2);
	vector_tmp.reserve(N);
	v.push_back(((int)vector_tmp.capacity()) >= N);
	v.push_back(*(vector_tmp.begin()));
	v.push_back(*(vector_tmp.end() - 1));
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T operator_index()
{
	T vector(2, 15);
	vector[0] = 37;
	vector[1] = 55;
	return vector;
}

template<typename T>
T at()
{
	T vector;
	try
	{
		vector.at(0) = 37;
	}
	catch (...)
	{
		vector.push_back(33);
	}
	try
	{
		vector.at(0) = 57;
	}
	catch (...)
	{
		vector.push_back(0);
	}
	return vector;
}

template<typename T>
T front()
{
	T vector(2, 15);
	vector.front() = 57;
	return vector;
}

template<typename T>
T back()
{
	T vector(2, 15);
	vector.back() = 57;
	return vector;
}

template<typename T>
T assign_iterators()
{
	std::vector<int> v;
	for (int i = 0; i < 25; ++i)
	{
		v.push_back(i);
	}
	T vector(2, 33);
	vector.assign(v.begin(), v.end());
	vector.assign(v.begin(), v.end() - 15);
	vector.assign(v.begin(), v.begin());
	vector.assign(v.begin(), v.begin() + 1);
	return vector;
}

template<typename T>
T assign_n_val()
{
	std::vector<int> v;
	for (int i = 0; i < 25; ++i)
	{
		v.push_back(i);
	}
	T vector(N, 33);
	vector.assign(10, 25);
	vector.assign(0, 1);
	vector.assign(3, 3);
	return vector;
}

template<typename T>
T push_back()
{
	T vector;
	for (int i = 0; i < N; ++i)
	{
		vector.push_back(i);
	}
	return vector;
}

template<typename T>
T pop_back()
{
	std::vector<int> v;
	for (int i = 0; i < 15; ++i)
	{
		v.push_back(i);
	}
	T vector(v.begin(), v.end());
	for (int i = 0; i < 15; ++i)
	{
		v.push_back(vector.size());
		v.push_back(*(vector.end() - 1));
		vector.pop_back();
	}
	vector.assign(v.begin(), v.end());
	return vector;
}

template<typename T>
T insert_pos_val()
{
	std::vector<int> v;

	T vector_tmp;
	v.push_back(*(vector_tmp.insert(vector_tmp.begin(), 44)));
	v.push_back(*(vector_tmp.insert(vector_tmp.begin() + 1, 13)));
	v.push_back(*(vector_tmp.insert(vector_tmp.end() - 2, 58)));

	T vector;
	vector.assign(v.begin(), v.end());
	return vector;
}

template<typename T>
T insert_pos_n_val()
{
	T vector;
	vector.insert(vector.begin(), 5, 3);
	vector.insert(vector.begin(), 2, 0);
	vector.insert(vector.begin(), 0, 14);
	vector.insert(vector.end(), N, 33);
	vector.insert(vector.begin() + 5, 3, 10);
	return vector;
}

template<typename T>
T insert_iterators()
{
	std::vector<int> v(N, 3);
	T vector;
	vector.insert(vector.begin(), v.begin(), v.end());
	vector.insert(vector.end(), v.begin(), v.begin() + 3);
	vector.insert(vector.end() - N / 2, v.end() - N / 3, v.end());
	return vector;
}

template<typename T>
T erase_pos()
{
	std::vector<int> v;
	for (int i = 0; i < 15; ++i)
	{
		v.push_back(i);
	}
	T vector_tmp(v.begin(), v.end());
	v.push_back(*(vector_tmp.erase(vector_tmp.begin())));
	v.push_back(*(vector_tmp.erase(vector_tmp.begin() + 5 / 2)));
	v.push_back(*(vector_tmp.erase(vector_tmp.end() - 1)));
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T erase_iterators()
{
	std::vector<int> v;
	for (int i = 0; i < 15; ++i)
	{
		v.push_back(i);
	}
	T vector_tmp(v.begin(), v.end());
	v.push_back(*(vector_tmp.erase(vector_tmp.begin(), vector_tmp.begin() + 5)));
	T vector(v.begin(), v.end());
	return vector;
}

template<typename T>
T swap()
{
	T vector_tmp(50, 7);
	T vector(10, 3);
	vector.swap(vector);
	vector.swap(vector_tmp);
	return vector;
}

template<typename T>
T clear()
{
	T vector(10, 3);
	vector.clear();
	return vector;
}

template<typename T>
T get_allocator()
{
	T vector(10, 3);
	typename T::pointer ptr = vector.get_allocator().allocate(5);
	if (ptr)
		vector.push_back(7);
	vector.get_allocator().deallocate(ptr, 5);
	return vector;
}

void vector(int n)
{
	N = n;
	print_title("Vector");
	run_case("Constructor", &default_constructor< ft::vector<int> >, &default_constructor< std::vector<int> >);
	run_case("Constructor(n, val)", &constructor_n_val< ft::vector<int> >, &constructor_n_val< std::vector<int> >);
	run_case("Constructor(iterators)", &constructor_iterators< ft::vector<int> >, &constructor_iterators< std::vector<int> >);
	run_case("Copy constructor", &constructor_copy< ft::vector<int> >, &constructor_copy< std::vector<int> >);
	run_case("operator=", &operator_assign< ft::vector<int> >, &operator_assign< std::vector<int> >);
	run_case("begin", &begin< ft::vector<int> >, &begin< std::vector<int> >);
	run_case("end", &end< ft::vector<int> >, &end< std::vector<int> >);
	run_case("rbegin", &rbegin< ft::vector<int> >, &rbegin< std::vector<int> >);
	run_case("rend", &rend< ft::vector<int> >, &rend< std::vector<int> >);
	run_case("size", &size< ft::vector<int> >, &size< std::vector<int> >);
	run_case("max_size", &max_size< ft::vector<int> >, &max_size< std::vector<int> >);
	run_case("resize", &resize< ft::vector<int> >, &resize< std::vector<int> >);
	run_case("capacity", &capacity< ft::vector<int> >, &capacity< std::vector<int> >);
	run_case("empty", &empty< ft::vector<int> >, &empty< std::vector<int> >);
	run_case("reserve", &reserve< ft::vector<int> >, &reserve< std::vector<int> >);
	run_case("operator[]", &operator_index< ft::vector<int> >, &operator_index< std::vector<int> >);
	run_case("at", &at< ft::vector<int> >, &at< std::vector<int> >);
	run_case("front", &front< ft::vector<int> >, &front< std::vector<int> >);
	run_case("back", &back< ft::vector<int> >, &back< std::vector<int> >);
	run_case("assign(iterators)", &assign_iterators< ft::vector<int> >, &assign_iterators< std::vector<int> >);
	run_case("assign(n, val)", &assign_n_val< ft::vector<int> >, &assign_n_val< std::vector<int> >);
	run_case("push_back", &push_back< ft::vector<int> >, &push_back< std::vector<int> >);
	run_case("pop_back", &pop_back< ft::vector<int> >, &pop_back< std::vector<int> >);
	run_case("insert(position, val)", &insert_pos_val< ft::vector<int> >, &insert_pos_val< std::vector<int> >);
	run_case("insert(position, n, val)", &insert_pos_n_val< ft::vector<int> >, &insert_pos_n_val< std::vector<int> >);
	run_case("insert(iterators)", &insert_iterators< ft::vector<int> >, &insert_iterators< std::vector<int> >);
	run_case("erase(position)", &erase_pos< ft::vector<int> >, &erase_pos< std::vector<int> >);
	run_case("erase(iterators)", &erase_iterators< ft::vector<int> >, &erase_iterators< std::vector<int> >);
	run_case("swap", &swap< ft::vector<int> >, &swap< std::vector<int> >);
	run_case("clear", &clear< ft::vector<int> >, &clear< std::vector<int> >);
	run_case("get_allocator", &get_allocator< ft::vector<int> >, &get_allocator< std::vector<int> >);
}
