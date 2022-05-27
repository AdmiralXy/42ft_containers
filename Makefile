CC = c++
RM = rm -f
# TODO remove -g flag
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98 -Isrc -I. -Iiterator -Iutility -g

NAME_UNIT_TESTS = ctests
NAME_BENCHMARK = cbenchmark

SRCS_UNIT_TESTS = tests/tests.cpp tests/utilities.cpp tests/vector.cpp tests/stack.cpp tests/map.cpp
OBJS_UNIT_TESTS = $(SRCS_UNIT_TESTS:%.cpp=%.o)

SRCS_BENCHMARK = benchmark/benchmark.cpp
OBJS_BENCHMARK = $(SRCS_BENCHMARK:%.cpp=%.o)

INCLUDES = src/iterator/iterator_traits.hpp \
		src/iterator/normal_iterator.hpp \
		src/iterator/reverse_iterator.hpp \
		src/iterator/tree_iterator.hpp \
		src/utility/enable_if.hpp \
		src/utility/equal.hpp \
		src/utility/is_integral.hpp \
		src/utility/lexicographical_compare.hpp \
		src/utility/pair.hpp \
		src/utility/tree.hpp \
		src/utility/utility.hpp \
		src/map.hpp \
		src/stack.hpp \
		src/vector.hpp

%.o: %.cpp $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)
	@echo "Building: \033[0;34m$<\033[0m"

all: $(NAME_UNIT_TESTS) $(NAME_BENCHMARK)

$(NAME_UNIT_TESTS): $(OBJS_UNIT_TESTS)
	@$(CC) $(CFLAGS) $(OBJS_UNIT_TESTS) -o $(NAME_UNIT_TESTS)
	@echo "Binary \033[0;32m$(NAME_UNIT_TESTS)\033[0m successfully linked!"

$(NAME_BENCHMARK): $(OBJS_BENCHMARK)
	@$(CC) $(CFLAGS) $(OBJS_BENCHMARK) -o $(NAME_BENCHMARK)
	@echo "Binary \033[0;32m$(NAME_BENCHMARK)\033[0m successfully linked!"

clean:
	@$(RM) $(OBJS_UNIT_TESTS) $(OBJS_BENCHMARK)
	@echo "Cleanup: \033[0;34mobject files\033[0m"

fclean: clean
	@$(RM) $(NAME_UNIT_TESTS) $(NAME_BENCHMARK)
	@echo "Cleanup: \033[0;34mlinked files\033[0m"

re: clean all

tests: $(NAME_UNIT_TESTS)
	./$(NAME_UNIT_TESTS) 10000000
	@make fclean -s

leaks: $(NAME_UNIT_TESTS)
	valgrind --leak-check=full --leak-resolution=med --vgdb=no -s ./$(NAME_UNIT_TESTS) 100000
	@make fclean -s
