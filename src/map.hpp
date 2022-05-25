#ifndef INC_42FT_CONTAINERS_MAP_H
#define INC_42FT_CONTAINERS_MAP_H

#include <memory>
#include "utility/tree.hpp"
#include "iterator/reverse_iterator.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
    public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
	public:
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map<Key, T, Compare, Alloc>;
        protected:
			Compare comp;
			explicit value_compare(Compare c) : comp(c) {}
        public:
			bool operator()(const value_type &lhs, const value_type &rhs) const {
				return comp(lhs.first, rhs.first);
			}
		};
	public:
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef ft::Tree<Key, T, Compare, Alloc>							rep_type;
		typedef typename rep_type::iterator									iterator;
		typedef typename rep_type::const_iterator 							const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef typename allocator_type::size_type							size_type;
	private:
		Compare _comp;
		allocator_type _alloc;
		rep_type _tree;
	public:
		// Constructors & destructor

		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		: _comp(comp), _alloc(alloc) {}

		template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

        map(const map& x) { *this = x; }

        ~map() {}

        map& operator=(const map& x)
        {
            _alloc = x._alloc;
            _comp = x._comp;
            _tree = x._tree;
			return *this;
        }

        // Iterators

        iterator begin() { return _tree.begin(); }

        const_iterator begin() const { return _tree.begin(); }

        iterator end() { return _tree.end(); }

        const_iterator end() const { return _tree.end(); }

        reverse_iterator rbegin() { return reverse_iterator(_tree.rbegin()); }

        const_reverse_iterator rbegin() const { return reverse_iterator(_tree.rbegin()); }

        reverse_iterator rend() { return reverse_iterator(_tree.rend()); }

        const_reverse_iterator rend() const { return reverse_iterator(_tree.rend()); }

        // Capacity

        bool empty() const
		{
			return !_tree.size();
		}

        size_type size() const
		{
			return _tree.size();
		}

        size_type max_size() const
		{
			return _alloc.max_size();
		}

        // Element access

        mapped_type& operator[](const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
		}

		// Modifiers

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			return _tree.add(val);
		}

		iterator insert(iterator position, const value_type& val)
		{
			(void)position;
			return _tree.add(val).first;
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

		//void erase(iterator position);
		//size_type erase(const key_type& k);
		//void erase(iterator first, iterator last);
		//void swap(map& x);
		//void clear();

		// Observers
		//key_compare key_comp() const;
		//value_compare value_comp() const;

		// Operations

		//iterator find(const key_type& k);
		//const_iterator find(const key_type& k) const;
		//size_type count(const key_type& k) const;
		//iterator lower_bound(const key_type& k);
		//const_iterator lower_bound(const key_type& k) const;
		//iterator upper_bound(const key_type& k);
		//const_iterator upper_bound(const key_type& k) const;
		//ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
		//ft::pair<iterator, iterator>             equal_range(const key_type& k);

		// Allocator

		//allocator_type get_allocator() const;
    };
}

#endif
