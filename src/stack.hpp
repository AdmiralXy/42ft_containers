#ifndef INC_42FT_CONTAINERS_STACK_H
#define INC_42FT_CONTAINERS_STACK_H

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef typename Container::value_type		value_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
		typedef typename Container::size_type		size_type;
		typedef Container							container_type;
	protected:
		container_type c;
	public:
		explicit stack(const container_type& ctnr = container_type()) : c(ctnr)
		{

		}

		stack(const stack& other)
		{
			c = other.c;
		}

		~stack()
		{

		}

		stack& operator=(const stack& other)
		{
			if (this == &other)
				return *this;
			c = other.c;
			return *this;
		}

		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		reference top()
		{
			return c.back();
		}

		const_reference top() const
		{
			return c.back();
		}

		void push(const value_type& val)
		{
			c.push_back(val);
		}

		void pop()
		{
			c.pop_back();
		}

		template <class T1, class Container1>
		friend bool operator==(const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);

		template <class T1, class Container1>
		friend bool operator<(const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);
	};

	template <class T, class Container>
	inline bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.c == rhs.c;
	}

	template <class T, class Container>
	inline bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	inline bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.c < rhs.c;
	}

	template <class T, class Container>
	inline bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	inline bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Container>
	inline bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
