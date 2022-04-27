#include "utilities.hpp"
#include "stack.hpp"
#include <stack>
#include "vector.hpp"
#include <vector>

// Utility

template <typename T>
bool equal(ft::stack<T> stack1, std::stack<T> stack2)
{
	if (stack1.size() != stack2.size())
		return false;
	for (typename ft::stack<T>::size_type i = stack1.size(); i > 0; --i)
	{
		if (stack1.top() != stack2.top())
			return false;
		stack1.pop();
		stack2.pop();
	}
	return true;
}

void run_case(std::string case_name, ft::stack<int> (*cf1)(), std::stack<int> (*cf2)())
{
	time_t ft_start = timestamp();
	ft::stack<int> v1 = cf1();
	time_t ft_end = timestamp();

	time_t std_start = timestamp();
	std::stack<int> v2 = cf2();
	time_t std_end = timestamp();

	print_result(case_name, equal(v1, v2), ft_end - ft_start, std_end - std_start);
}

// Tests

template<typename T>
T default_constructor()
{
	T stack;
	return stack;
}

template<typename T>
T empty()
{
	std::stack<int> s;
	T stack;
	s.push(stack.empty());
	stack.push(5);
	s.push(stack.empty());
	stack.push(s.top());
	s.pop();
	stack.push(s.top());
	s.pop();
	return stack;
}

template<typename T>
T size()
{
	std::stack<int> s;
	T stack;
	s.push(stack.size());
	stack.push(5);
	stack.push(3);
	s.push(stack.size());
	stack.push(stack.size());
	stack.push(s.top());
	s.pop();
	stack.push(s.top());
	s.pop();
	return stack;
}

template<typename T>
T top()
{
	T stack;
	stack.push(5);
	stack.push(stack.top());
	stack.push(7);
	stack.push(stack.top());
	stack.push(stack.top());
	stack.pop();
	stack.push(stack.top());
	return stack;
}

template<typename T>
T push()
{
	T stack;
	for (int i = 0; i < N; ++i)
		stack.push(i);
	return stack;
}

template<typename T>
T pop()
{
	T stack;
	for (int i = 0; i < N; ++i)
		stack.push(i);
	for (int i = 0; i < N; ++i)
		stack.pop();
	return stack;
}

template<typename T>
T relational_operators()
{
	T stack1;
	stack1.push(7);
	stack1.push(3);
	stack1.push(1);
	stack1.push(6);
	stack1.push(11);
	T stack2;
	stack2.push(7);
	stack2.push(3);
	stack2.push(1);
	stack2.push(6);
	stack2.push(11);
	T stack3;
	stack3.push(76);
	stack3.push(53);
	stack3.push(1651);
	stack3.push(13);
	stack3.push(191);

	T stack;
	stack.push(stack1 == stack2);
	stack.push(stack1 == stack3);

	stack.push(stack1 != stack2);
	stack.push(stack1 != stack3);

	stack.push(stack1 < stack2);
	stack.push(stack1 < stack3);

	stack.push(stack1 <= stack2);
	stack.push(stack1 <= stack3);

	stack.push(stack1 > stack2);
	stack.push(stack1 > stack3);

	stack.push(stack1 >= stack2);
	stack.push(stack1 >= stack3);

	return stack;
}

void stack()
{
	print_title("Stack");
	run_case("Constructor(default)", &default_constructor< ft::stack<int> >, &default_constructor< std::stack<int> >);
	run_case("empty", &empty< ft::stack<int> >, &empty< std::stack<int> >);
	run_case("size", &size< ft::stack<int> >, &size< std::stack<int> >);
	run_case("top", &top< ft::stack<int> >, &top< std::stack<int> >);
	run_case("push", &push< ft::stack<int> >, &push< std::stack<int> >);
	run_case("pop", &pop< ft::stack<int> >, &pop< std::stack<int> >);
	run_case("Relational operators", &relational_operators< ft::stack<int> >, &relational_operators< std::stack<int> >);
}
