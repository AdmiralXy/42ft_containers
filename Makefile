CC = c++
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98 -Isrc -I.

NAME_UNIT_TESTS = main_tests
NAME_BENCHMARK = main_benchmark

SRCS_UNIT_TESTS = tests/tests.cpp tests/utilities.cpp tests/vector.cpp
OBJS_UNIT_TESTS = $(SRCS_UNIT_TESTS:%.cpp=%.o)

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)
	@echo "Building: \033[0;34m$<\033[0m"

$(NAME_UNIT_TESTS): $(OBJS_UNIT_TESTS)
	@$(CC) $(CFLAGS) $(OBJS_UNIT_TESTS) -o $(NAME_UNIT_TESTS)
	@echo "Binary \033[0;32m$(NAME_UNIT_TESTS)\033[0m successfully linked!"

all: $(SRCS_UNIT_TESTS)

clean:
	@$(RM) $(OBJS_UNIT_TESTS)
	@echo "Cleanup: \033[0;34mobject files\033[0m"

fclean: clean
	@$(RM) $(NAME_UNIT_TESTS)
	@echo "Cleanup: \033[0;34mlinked files\033[0m"

re: clean all

tests: $(NAME_UNIT_TESTS)
	./$(NAME_UNIT_TESTS) 10000000
	@make fclean -s

leaks: $(NAME_UNIT_TESTS)
	valgrind --leak-check=full --leak-resolution=med --vgdb=no -s ./$(NAME_UNIT_TESTS) 100000
	@make fclean -s