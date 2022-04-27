#ifndef INC_42FT_CONTAINERS_VECTOR_H
#define INC_42FT_CONTAINERS_VECTOR_H

#include <memory>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "iterator/normal_iterator.hpp"
#include "iterator/reverse_iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T														value_type;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::normal_iterator<pointer, vector>					iterator;
		typedef ft::normal_iterator<const_pointer, vector>				const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef typename allocator_type::size_type						size_type;
	private:
		allocator_type _alloc;
		pointer _start;
		size_type _capacity;
		size_type _size;
	public:

		// Constructors & destructor

		explicit vector(const allocator_type &alloc = allocator_type())
		{
			_alloc = alloc;
			_start = NULL;
			_capacity = 0;
			_size = 0;
		}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		{
			_alloc = alloc;
			_start = _alloc.allocate(n);
			_capacity = n;
			_size = n;
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_start + i, val);
		}

		template<class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0)
		{
			_alloc = alloc;
			_start = NULL;
			_capacity = 0;
			_size = 0;
			insert(begin(), first, last);
		}

		vector(const vector &x)
		{
			_alloc = x.get_allocator();
			_capacity = x._capacity;
			_size = x._size;
			_start = _alloc.allocate(x._capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_start + i, x._start[i]);
		}

		vector& operator=(const vector& x)
		{
			if (this == &x)
				return *this;
			this->clear();
			if (_start)
				_alloc.deallocate(_start, _capacity);
			_capacity = x._capacity;
			_size = x._size;
			_start = _alloc.allocate(_capacity);
			for (size_t i = 0; i < _size; ++i)
				_alloc.construct(_start + i, x._start[i]);
			return *this;
		}

		~vector()
		{
			clear();
			if (_start)
				_alloc.deallocate(_start, _capacity);
		}

		// Iterators

		iterator begin()
		{
			return iterator(_start);
		}

		const_iterator begin() const
		{
			return const_iterator(_start);
		}

		iterator end()
		{
			return iterator(_start + _size);
		}

		const_iterator end() const
		{
			return const_iterator(_start + _size);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end() - 1);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end() - 1);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin() - 1);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin() - 1);
		}

		// Capacity

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return _alloc.max_size();
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (max_size() < n)
				throw std::length_error("not enough memory");
			else if (n < _size)
				destroy(_start + n, _start + _size);
			else
				this->insert(this->end(), n - this->size(), val);
			_size = n;
		}

		size_type capacity() const
		{
			return _capacity;
		}

		bool empty() const
		{
			return !_size;
		}

		void reserve(size_type n)
		{
			if (max_size() < n)
				throw std::length_error("not enough memory");
			else if (_capacity < n)
			{
				n = ceil(((n * 3) / 2) + 1);
				pointer new_start = _alloc.allocate(n);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(new_start + i, _start[i]);
				if (_start) {
					destroy(_start, _start + _size);
					_alloc.deallocate(_start, _capacity);
				}
				_start = new_start;
				_capacity = n;
			}
		}

		// Element access:

		reference operator[](size_type n)
		{
			return _start[n];
		}

		const_reference operator[](size_type n) const
		{
			return _start[n];
		}

		reference at(size_type n)
		{
			if (n >= size())
				throw std::out_of_range("out of bounds exception");
			return _start[n];
		}

		const_reference at(size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("out of bounds exception");
			return _start[n];
		}

		reference front()
		{
			return _start[0];
		}

		const_reference front() const
		{
			return _start[0];
		}

		reference back()
		{
			return _start[_size - 1];
		}

		const_reference back() const
		{
			return _start[_size - 1];
		}

		// Modifiers:

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0)
		{
			erase(begin(), end());
			insert(begin(), first, last);
		}

		void assign(size_type n, const value_type& val)
		{
			value_type tmp = val;
			erase(begin(), end());
			insert(begin(), n, tmp);
		}

		void push_back(const value_type& val)
		{
			if (_capacity < _size + 1)
				this->reserve(_size + 1);
			_alloc.construct(_start + _size, val);
			_size++;
		}

		void pop_back()
		{
			erase(end() - 1);
		}

		iterator insert(iterator position, const value_type& val)
		{
			size_type offset = size() == 0 ? 0 : position - begin();
			value_type val_cpy = val;
			insert(position, static_cast<size_type>(1), val_cpy);
			return begin() + offset;
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			if (n < 1)
				return;
			size_type index = position.base() - _start;
			if (_capacity < _size + n)
				this->reserve(_size + n);
			size_type iter = _size - 1 + n;
			for (size_type i = 0; i < _size - index; ++i)
			{
				_alloc.construct(_start + iter, _start[_size - 1 - i]);
				_alloc.destroy(_start + _size - 1 - i);
				iter--;
			}
			for (size_type i = index; i < index + n; i++)
				_alloc.construct(_start + i, val);
			_size += n;
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0)
		{
			size_type index = position.base() - _start;
			size_type n = last - first;
			if (n < 1)
				return;
			if (_capacity < _size + n)
				this->reserve(_size + n);
			size_type iter = _size - 1 + n;
			for (size_type i = 0; i < _size - index; ++i)
			{
				_alloc.construct(_start + iter, _start[_size - 1 - i]);
				_alloc.destroy(_start + _size - 1 - i);
				iter--;
			}
			for (size_type i = index; i < index + n; i++)
				_alloc.construct(_start + i, *(first++));
			_size += n;
		}

		iterator erase(iterator position)
		{
			return erase(position, position + 1);
		}

		iterator erase(iterator first, iterator last)
		{
			int start = first - begin();
			int end = last - begin();
			int n = end - start;

			_size -= n;
			for (size_t i = start; i < _size; ++i) {
				_alloc.destroy(_start + i);
				_start[i] = _start[i + n];
			}
			return iterator(_start + start);
		}

		void swap(vector& x)
		{
			std::swap(_alloc, x._alloc);
			std::swap(_start, x._start);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
		}

		void clear()
		{
			destroy(_start, _start + _size);
			_size = 0;
		}

		// Allocator:

		allocator_type get_allocator() const
		{
			return _alloc;
		}

	private:
		
		// Utility functions

		void destroy(pointer first, pointer last)
		{
			while (first != last)
				_alloc.destroy(first++);
		}

	};
}

#endif
