#include "tests.hpp"
#include <cstdlib>
#include <iostream>

int N;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "usage: ./main [N]" << std::endl;
		return 1;
	}
	N = std::atoi(argv[1]);
	if (N < 3) {
		std::cout << "error: bad or too low argument" << std::endl;
		return 1;
	}
	vector();
	std::cout << std::endl;
	stack();
	std::cout << std::endl;
	map();
	std::cout << std::endl;
	advanced();
	std::cout << std::endl;
	return 0;
}
