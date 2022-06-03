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
				insert(ft::make_pair(first->first, first->second));
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

		mapped_type& at(const key_type& k)
		{
			iterator pair = find(k);
			return pair == end() ? throw std::out_of_range("out of bounds exception") : pair->second;
		}

		const mapped_type& at(const key_type& k) const
		{
			iterator pair = find(k);
			return pair == end() ? throw std::out_of_range("out of bounds exception") : pair->second;
		}

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
				_tree.add(ft::make_pair(first->first, first->second));
				++first;
			}
		}

		void erase(iterator position)
		{
			_tree.erase(position->first);
		}

		size_type erase(const key_type& k)
		{
			return _tree.erase(k);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				_tree.erase((first++)->first);
		}

		void swap(map& x)
		{
			std::swap(_alloc, x._alloc);
			std::swap(_comp, x._comp);
			_tree.swap(x._tree);
		}

		void clear()
		{
			_tree.clear();
		}

		// Observers

		key_compare key_comp() const
		{
			return _comp;
		}

		value_compare value_comp() const
		{
			return value_compare(key_comp());
		}

		// Operations

		iterator find(const key_type& k)
		{
			return _tree.find(k).first;
		}

		const_iterator find(const key_type& k) const
		{
			return _tree.find(k).first;
		}

		size_type count(const key_type& k) const
		{
			return find(k) == iterator(end) ? 0 : 1;
		}

		iterator lower_bound(const key_type& k)
		{
			return _tree.lower_bound(k);
		}

		const_iterator lower_bound(const key_type& k) const
		{
			return _tree.lower_bound(k);
		}

		iterator upper_bound(const key_type& k)
		{
			return _tree.upper_bound(k);
		}

		const_iterator upper_bound(const key_type& k) const
		{
			return _tree.upper_bound(k);
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		ft::pair<iterator, iterator> equal_range(const key_type& k)
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		// Allocator

		allocator_type get_allocator() const
		{
			return _alloc;
		}

		// Relational operators

		friend bool operator==(const map& lhs, const map& rhs)
		{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		friend bool operator!=(const map& lhs, const map& rhs)
		{
			return !(lhs == rhs);
		}

		friend bool operator<(const map& lhs, const map& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		friend bool operator<=(const map& lhs, const map& rhs)
		{
			return !(rhs < lhs);
		}

		friend bool operator>(const map& lhs, const map& rhs)
		{
			return rhs < lhs;
		}

		friend bool operator>=(const map& lhs, const map& rhs)
		{
			return !(lhs < rhs);
		}
    };

	// Swap

	template<typename Key, typename T, typename Compare, typename Alloc>
	inline void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
