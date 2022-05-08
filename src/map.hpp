#ifndef INC_42FT_CONTAINERS_MAP_H
#define INC_42FT_CONTAINERS_MAP_H

#include <memory>
#include "iterator/tree_iterator.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< pair<const Key,T> > >
	class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
    public:
        class value_compare : public std::binary_function<value_type, value_type, bool> {
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
		typedef ft::tree_iterator<value_type >								iterator;
		typedef ft::tree_iterator<value_type >								const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
        typedef typename allocator_type::size_type							size_type;
    private:
		Compare _comp;
        allocator_type _alloc;
        Tree<value_type> _tree;
    public:

        // Constructors & destructor

        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		: _comp(comp), _alloc(alloc) {}

        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc) {}

        map(const map& x) { *this = x; }

        ~map() {}

        map& operator=(const map& x)
        {
            _alloc = x._alloc;
            _comp = x._comp;
            _tree = x._tree;
        }

        // Iterators

        iterator begin() { return iterator(_tree.begin()); }

        //const_iterator begin() const;
        //iterator end();
        //const_iterator end() const;
        //reverse_iterator rbegin();
        //const_reverse_iterator rbegin() const;
        //reverse_iterator rend();
        //const_reverse_iterator rend() const;

        // Capacity

        //bool empty() const;
        //size_type size() const;
        //size_type max_size() const;

        // Element access

        //mapped_type& operator[](const key_type& k);

		// Modifiers

		//pair<iterator,bool> insert (const value_type& val);
		//iterator insert (iterator position, const value_type& val);

		//template <class InputIterator>
		//void insert (InputIterator first, InputIterator last);

		//void erase (iterator position);
		//size_type erase (const key_type& k);
		//void erase (iterator first, iterator last);
		//void swap (map& x);
		//void clear();

		// Observers
		//key_compare key_comp() const;
		//value_compare value_comp() const;

		// Operations

		//iterator find (const key_type& k);
		//const_iterator find (const key_type& k) const;
		//size_type count (const key_type& k) const;
		//iterator lower_bound (const key_type& k);
		//const_iterator lower_bound (const key_type& k) const;
		//iterator upper_bound (const key_type& k);
		//const_iterator upper_bound (const key_type& k) const;
		//pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		//pair<iterator,iterator>             equal_range (const key_type& k);

		// Allocator

		//allocator_type get_allocator() const;
    };
}

#endif
