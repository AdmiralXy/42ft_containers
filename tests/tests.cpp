#include "tests.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "usage: ./main [N]" << std::endl;
		return 1;
	}
	int N = std::atoi(argv[1]);
	if (N < 1) {
		std::cout << "error: bad argument" << std::endl;
		return 1;
	}
	vector(N);
	return 0;
}