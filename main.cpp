#include <iostream>
#include "src/vector.hpp"
#include <vector>

template <typename T>
void print_vector(ft::vector<T> &vector)
{
	typename ft::vector<T>::iterator iterator;
	iterator = vector.begin();
	for (int i = 0; iterator != vector.end(); iterator++, i++)
	{
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

template <typename T>
void print_vector(std::vector<T> &vector)
{
	typename std::vector<T>::iterator iterator;
	iterator = vector.begin();
	for (int i = 0; iterator != vector.end(); iterator++, i++)
	{
		std::cout << vector[i] << " ";
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
	std::vector<std::string> v;
	v.reserve(15);
	for (int i = 0; i < 15; ++i)
	{
		v.push_back("hello world!");
	}
	ft::vector<std::string> vector;
	vector.assign(v.begin(), v.end());
	vector.assign(10, "test!");
	ft::vector<std::string> leaks;
	leaks = vector;
	leaks.erase(leaks.begin());
	leaks.erase(leaks.begin() + 1, leaks.begin() + 4);
}
