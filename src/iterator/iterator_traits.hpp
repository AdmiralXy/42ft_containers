#ifndef INC_42FT_CONTAINERS_ITERATOR_TRAITS_HPP
#define INC_42FT_CONTAINERS_ITERATOR_TRAITS_HPP

namespace ft
{
	// Empty types, used to distinguish different iterators
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	// Default iterator trait
	template<typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;
	};

	// Partial specialization for pointer types.
	template<typename Tp>
	struct iterator_traits<Tp*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef Tp							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef Tp*							pointer;
		typedef Tp&							reference;
	};

	// Partial specialization for const pointer types.
	template<typename Tp>
	struct iterator_traits<const Tp*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef Tp							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef const Tp*					pointer;
		typedef const Tp&					reference;
	};

	// Common iterator class
	template<typename Category, typename Tp, typename Distance = std::ptrdiff_t, typename Pointer = Tp*, typename Reference = Tp&>
	struct iterator
	{
		typedef Category  iterator_category;
		typedef Tp        value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
	};
}

#endif
