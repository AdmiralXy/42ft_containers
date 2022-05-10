#ifndef INC_42FT_CONTAINERS_REVERSE_ITERATOR_HPP
#define INC_42FT_CONTAINERS_REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "../utility/utility.hpp"

namespace ft
{
	template <class T>
	class reverse_iterator
	{
	protected:
		T							current;
		typedef iterator_traits<T>	_traits_type;
	public:
		typedef T											iterator_type;
		typedef typename _traits_type::iterator_category	iterator_category;
		typedef typename _traits_type::value_type			value_type;
		typedef typename _traits_type::difference_type		difference_type;
		typedef typename _traits_type::reference			reference;
		typedef typename _traits_type::pointer				pointer;

		reverse_iterator() : current()
		{

		}

		explicit reverse_iterator(iterator_type _x) : current(_x)
		{

		}

		reverse_iterator(const reverse_iterator& _x) : current(_x.current)
		{

		}

		~reverse_iterator()
		{

		}

		reverse_iterator &operator=(const reverse_iterator &obj)
		{
			current = obj.current;
			return *this;
		}

		iterator_type base() const
		{
			return current;
		}

		reference operator*()
		{
			return *current;
		}

		pointer operator->()
		{
			return &(operator*());
		}

		reverse_iterator &operator++()
		{
			--current;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			current--;
			return tmp;
		}

		reverse_iterator &operator--()
		{
			++current;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			current++;
			return tmp;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(current - n);
		}

		reverse_iterator &operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(current + n);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		bool operator==(reverse_iterator const &obj) const
		{
			return current == obj.current;
		};

		bool operator!=(reverse_iterator const &obj) const
		{
			return current != obj.current;
		};

		bool operator<(reverse_iterator const &obj) const
		{
			return current < obj.current;
		};

		bool operator>(reverse_iterator const &obj) const
		{
			return current > obj.current;
		};

		bool operator<=(reverse_iterator const &obj) const
		{
			return current <= obj.current;
		};

		bool operator>=(reverse_iterator const &obj) const
		{
			return current >= obj.current;
		};
	};
}

#endif
