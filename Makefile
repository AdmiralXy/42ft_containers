CC = c++
RM = rm -f
# TODO remove -g flag
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98 -I. -Iincludes -Iiterator -Iutility -g

NAME_UNIT_TESTS = ctests
NAME_BENCHMARK_FT = ft_cbenchmark
NAME_BENCHMARK_STD = std_cbenchmark

SRCS_UNIT_TESTS = tests/tests.cpp tests/utilities.cpp tests/vector.cpp tests/stack.cpp tests/map.cpp tests/advanced.cpp
OBJS_UNIT_TESTS = $(SRCS_UNIT_TESTS:%.cpp=%.o)

SRCS_BENCHMARK = benchmark/benchmark.cpp

INCLUDES = includes/iterator/iterator_traits.hpp \
		includes/iterator/normal_iterator.hpp \
		includes/iterator/reverse_iterator.hpp \
		includes/utility/enable_if.hpp \
		includes/utility/equal.hpp \
		includes/utility/is_integral.hpp \
		includes/utility/lexicographical_compare.hpp \
		includes/utility/pair.hpp \
		includes/utility/tree.hpp \
		includes/utility/utility.hpp \
		includes/map.hpp \
		includes/stack.hpp \
		includes/vector.hpp

%.o: %.cpp $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)
	@echo "Building: \033[0;34m$<\033[0m"

all: $(NAME_UNIT_TESTS) $(NAME_BENCHMARK_STD) $(NAME_BENCHMARK_FT)

$(NAME_UNIT_TESTS): $(OBJS_UNIT_TESTS)
	@$(CC) $(CFLAGS) $(OBJS_UNIT_TESTS) -o $(NAME_UNIT_TESTS)
	@echo "Binary \033[0;32m$(NAME_UNIT_TESTS)\033[0m successfully linked!"

$(NAME_BENCHMARK_STD): $(OBJS_BENCHMARK)
	@$(CC) -DCONTAINER_TYPE=1 $(CFLAGS) $(SRCS_BENCHMARK) -o $(NAME_BENCHMARK_STD)
	@echo "Binary \033[0;32m$(NAME_BENCHMARK_STD)\033[0m successfully linked!"

$(NAME_BENCHMARK_FT): $(OBJS_BENCHMARK)
	@$(CC) -DCONTAINER_TYPE=0 $(CFLAGS) $(SRCS_BENCHMARK) -o $(NAME_BENCHMARK_FT)
	@echo "Binary \033[0;32m$(NAME_BENCHMARK_FT)\033[0m successfully linked!"

clean:
	@$(RM) $(OBJS_UNIT_TESTS) $(OBJS_BENCHMARK)
	@echo "Cleanup: \033[0;34mobject files\033[0m"

fclean: clean
	@$(RM) $(NAME_UNIT_TESTS) $(NAME_BENCHMARK_STD) $(NAME_BENCHMARK_FT)
	@echo "Cleanup: \033[0;34mlinked files\033[0m"

re: clean all

tests: $(NAME_UNIT_TESTS)
	./$(NAME_UNIT_TESTS) 10000000
	@make fclean -s

leaks: $(NAME_UNIT_TESTS)
	valgrind --leak-check=full --leak-resolution=med --vgdb=no -s ./$(NAME_UNIT_TESTS) 100000
	@make fclean -s
