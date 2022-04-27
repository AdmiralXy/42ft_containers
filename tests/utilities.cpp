#ifndef INC_42FT_CONTAINERS_TESTS_UTILITIES_H
#define INC_42FT_CONTAINERS_TESTS_UTILITIES_H

#include <sys/time.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

void print_title(std::string test_name)
{
	int width = 38;
	std::cout
			<< "\033[1m\033[36m"
			<< std::string(width * 1.38, '-')
			<< test_name
			<< std::string(width * 1.38, '-')
			<< "\033[0m"
			<< std::endl;
	std::cout
			<< std::left
			<< std::setw(width)
			<< std::setfill(' ')
			<< "\033[1m\033[36mFunction\033[0m"
			<< std::left
			<< std::setw(width)
			<< std::setfill(' ')
			<< "\033[1m\033[36mResult\033[0m"
			<< std::left
			<< std::setw(width)
			<< std::setfill(' ')
			<< "\033[1m\033[36mFT Time\033[0m"
			<< std::left
			<< std::setw(width)
			<< std::setfill(' ')
			<< "\033[1m\033[36mSTD Time\033[0m"
			<< std::left
			<< std::setw(width)
			<< std::setfill(' ')
			<< "\033[1m\033[36mDifference\033[0m"
			<< std::endl;
}

void print_line(std::string str1, std::string str2, std::string str3, std::string str4, std::string str5)
{
	std::cout
			<< std::left
			<< std::setw(25)
			<< std::setfill(' ')
			<< str1
			<< std::left
			<< std::setw(36)
			<< std::setfill(' ')
			<< str2
			<< std::left
			<< std::setw(38)
			<< std::setfill(' ')
			<< str3
			<< std::left
			<< std::setw(38)
			<< std::setfill(' ')
			<< str4
			<< std::left
			<< std::setw(0)
			<< std::setfill(' ')
			<< str5
			<< std::endl;
}

void print_result(std::string case_name, bool isSuccess, time_t ft_time, time_t std_time)
{
	std::stringstream ft;
	ft << ft_time;
	std::string ft_str = ft.str();

	std::stringstream std;
	std << std_time;
	std::string std_str = std.str();

	float difference = std_time == 0 ? ft_time : ft_time / (float)std_time;

	std::stringstream diff;

	if (ft_time == std_time)
	{
		ft_str = "\033[1m\033[32m" + ft_str + "ms" + "\033[0m";
		std_str = "\033[1m\033[32m" + std_str + "ms" + "\033[0m";
		diff << "\033[1m\033[37m-\033[0m";
	}
	else if (ft_time < std_time)
	{
		ft_str = "\033[1m\033[32m" + ft_str + "ms" + "\033[0m";
		std_str = "\033[1m\033[31m" + std_str + "ms" + "\033[0m";
		difference = ft_time == 0 ? std_time : std_time / (float)ft_time;
		diff << std::setprecision(2) << "\033[1m\033[32mx" << difference << "\033[0m";
	}
	else
	{
		ft_str = "\033[1m\033[31m" + ft_str + "ms" + "\033[0m";
		std_str = "\033[1m\033[32m" + std_str + "ms" + "\033[0m";
		diff << std::setprecision(2) << "\033[1m\033[31mx" << difference << "\033[0m";
	}

	std::string diff_str = diff.str();

	if (isSuccess)
		print_line(case_name, "\033[1;32mOK\033[0m", ft_str, std_str, diff_str);
	else
		print_line(case_name, "\033[1;31mKO\033[0m", ft_str, std_str, diff_str);
}

time_t	timestamp(void)
{
	struct timeval	time;
	time_t			milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = time.tv_sec * 1000;
	milliseconds += time.tv_usec / 1000;
	return milliseconds;
}

#endif
