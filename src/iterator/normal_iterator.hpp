#ifndef INC_42FT_CONTAINERS_NORMAL_ITERATOR_HPP
#define INC_42FT_CONTAINERS_NORMAL_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "../utility/utility.hpp"

namespace ft
{
	using ft::iterator_traits;
	using ft::iterator;
	template<typename Iterator, typename Container>
	class normal_iterator
	{
	protected:
		Iterator current;
		typedef iterator_traits<Iterator>		_traits_type;
	public:
		typedef Iterator									iterator_type;
		typedef typename _traits_type::iterator_category	iterator_category;
		typedef typename _traits_type::value_type			value_type;
		typedef typename _traits_type::difference_type		difference_type;
		typedef typename _traits_type::reference			reference;
		typedef typename _traits_type::pointer				pointer;

		normal_iterator() : current(Iterator())
		{

		}

		explicit normal_iterator(const Iterator& _i) : current(_i)
		{

		}

		// Allow iterator to const_iterator conversion
		template<typename Iter>
		explicit normal_iterator(const normal_iterator<Iter, typename ft::enable_if<(std::__are_same<Iter, typename Container::pointer>::__value), Container>::__type>& _i) : current(_i.base())
		{

		}

		// Forward iterator requirements
		reference operator*() const
		{
			return *current;
		}

		pointer operator->() const
		{
			return current;
		}

		normal_iterator& operator++()
		{
			++current;
			return *this;
		}

		normal_iterator operator++(int)
		{
			return normal_iterator(current++);
		}

		// Bidirectional iterator requirements

		normal_iterator& operator--()
		{
			--current;
			return *this;
		}

		int operator-(normal_iterator const &_n) const
		{
			return current - _n.current;
		}

		int operator+(normal_iterator const &_n) const
		{
			return current + _n.current;
		}

		normal_iterator operator--(int)
		{
			return normal_iterator(current--);
		}

		// Random access iterator requirements

		reference operator[](difference_type _n) const
		{
			return current[_n];
		}

		normal_iterator& operator+=(difference_type _n)
		{
			current += _n;
			return *this;
		}

		normal_iterator operator+(difference_type _n) const
		{
			return normal_iterator(current + _n);
		}

		normal_iterator& operator-=(difference_type _n)
		{
			current -= _n;
			return *this;
		}

		normal_iterator operator-(difference_type _n) const
		{
			return normal_iterator(current - _n);
		}

		const Iterator& base() const
		{
			return current;
		}
	};

	// Forward iterator requirements

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator==(const normal_iterator<IteratorL, Container>& _lhs,
			   const normal_iterator<IteratorR, Container>& _rhs)
	{ return _lhs.base() == _rhs.base(); }

	template<typename Iterator, typename Container>
	inline bool
	operator==(const normal_iterator<Iterator, Container>& _lhs,
			   const normal_iterator<Iterator, Container>& _rhs)
	{ return _lhs.base() == _rhs.base(); }

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator!=(const normal_iterator<IteratorL, Container>& _lhs,
			   const normal_iterator<IteratorR, Container>& _rhs)
	{ return _lhs.base() != _rhs.base(); }

	template<typename Iterator, typename Container>
	inline bool
	operator!=(const normal_iterator<Iterator, Container>& _lhs,
			   const normal_iterator<Iterator, Container>& _rhs)
	{ return _lhs.base() != _rhs.base(); }

	// Random access iterator requirements

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator<(const normal_iterator<IteratorL, Container>& _lhs,
			  const normal_iterator<IteratorR, Container>& _rhs)
	{ return _lhs.base() < _rhs.base(); }

	template<typename Iterator, typename Container>
	inline bool
	operator<(const normal_iterator<Iterator, Container>& _lhs,
			  const normal_iterator<Iterator, Container>& _rhs)
	{ return _lhs.base() < _rhs.base(); }

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator>(const normal_iterator<IteratorL, Container>& _lhs,
			  const normal_iterator<IteratorR, Container>& _rhs)
	{ return _lhs.base() > _rhs.base(); }

	template<typename Iterator, typename Container>
	inline bool
	operator>(const normal_iterator<Iterator, Container>& _lhs,
			  const normal_iterator<Iterator, Container>& _rhs)
	{ return _lhs.base() > _rhs.base(); }

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator<=(const normal_iterator<IteratorL, Container>& _lhs,
			   const normal_iterator<IteratorR, Container>& _rhs)
	{ return _lhs.base() <= _rhs.base(); }

	template<typename Iterator, typename Container>
	inline bool
	operator<=(const normal_iterator<Iterator, Container>& _lhs,
			   const normal_iterator<Iterator, Container>& _rhs)
	{ return _lhs.base() <= _rhs.base(); }

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator>=(const normal_iterator<IteratorL, Container>& _lhs,
			   const normal_iterator<IteratorR, Container>& _rhs)
	{ return _lhs.base() >= _rhs.base(); }

	template<typename Iterator, typename Container>
	inline bool
	operator>=(const normal_iterator<Iterator, Container>& _lhs,
			   const normal_iterator<Iterator, Container>& _rhs)
	{ return _lhs.base() >= _rhs.base(); }
}

#endif
