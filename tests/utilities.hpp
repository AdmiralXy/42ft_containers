#ifndef INC_42FT_CONTAINERS_TESTS_UTILITIES_H
#define INC_42FT_CONTAINERS_TESTS_UTILITIES_H

#include <string>

#define SEED 3384584830

extern int N;

void print_title(std::string test_name);
void print_line(std::string str1, std::string str2, std::string str3, std::string str4, std::string str5);
void print_result(std::string case_name, bool isSuccess, time_t ft_time, time_t std_time);
time_t timestamp(void);

#endif
