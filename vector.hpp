#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"
# include <sstream>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::random_access_iterator<value_type>					iterator;
			typedef ft::random_access_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;

			explicit vector(const allocator_type& alloc = allocator_type())
			: _alloc(alloc), start(0), finish(0), end_of_storage(0) {}

			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type())
			: _alloc(alloc), start(0), finish(0), end_of_storage(0)
			{
				start = _alloc.allocate(n);
				finish = start;
				end_of_storage = start + n;
				for (size_type i = 0; i < n; i++)
				{
					_alloc.construct(finish, val);
					++finish;
				}
			}

			template <class InputIterator,
						typename = typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type>
         	vector(InputIterator first, InputIterator last,
			 		const allocator_type& alloc = allocator_type())
			: _alloc(alloc), start(0), finish(0), end_of_storage(0)
			{
				difference_type	n = ft::distance(first, last);
				start = _alloc.allocate(n);
				finish = start;
				end_of_storage = start + n;
				while (first != last)
				{
					_alloc.construct(finish, *first);
					++first;
					++finish;
				}
			}

			vector(const vector& x)
			: _alloc(x._alloc), start(0), finish(0), end_of_storage(0)
			{
				insert(begin(), x.begin(), x.end());
			}

			~vector() { clear(); _alloc.deallocate(start, capacity()); }

			vector&	operator=(const vector& other)
			{
				if (&other != this)
				{
					clear();
					insert(begin(), other.begin(), other.end());
				}
				return (*this);
			}

			//						Iterators

			iterator				begin() { return start; }
			const_iterator			begin() const { return start; }
			iterator				end() { return finish; }
			const_iterator			end() const { return finish; }
			reverse_iterator		rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator		rend() { return reverse_iterator(begin()); }
			const_reverse_iterator	rend() const { return reverse_iterator(begin()); }

			//						Capacity

			size_type				size() const { return finish - start; }
			size_type				max_size() const { return _alloc.max_size(); }
			void					resize(size_type n, value_type val = value_type())
			{
				if (n > max_size())
					throw std::length_error("vector::insert ");
				if (n < size())
				{
					while (size() > n)
					{
						--finish;
						_alloc.destroy(finish);
					}
				}
				else if (n > size())
					insert(end(), n - size(), val);
			}
			size_type				capacity() const { return end_of_storage - start; }
			bool					empty() const { return size() == 0; }
			void					reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (capacity() < n)
				{
					size_type	old_size = size();
					size_type	old_capacity = capacity();
					pointer		old_start = start;
					pointer		old_finish = finish;
					start = _alloc.allocate(n);
					finish = start;
					end_of_storage = start + n;
					while (old_start != old_finish)
					{
						_alloc.construct(finish, *old_start);
						_alloc.destroy(old_start);
						++old_start;
						++finish;
					}
					old_start -= old_size;
					_alloc.deallocate(old_start, old_capacity);
				}
			}

			//						Element access

			reference				operator[](size_type n) { return *(start + n); }
			const_reference			operator[](size_type n) const { return *(start + n); }
			reference				at(size_type n)
			{
				std::ostringstream	ss;
				ss << "vector::at: n (which is " << n << ") >= this->size() (which is " << size() << ")";
				if (n >= size())
					throw std::out_of_range(ss.str());
				return ((*this)[n]);
			}
			const_reference			at(size_type n) const
			{
				std::ostringstream	ss;
				ss << "vector::at: n (which is " << n << ") >= this->size() (which is " << size() << ")";
				if (n >= size())
					throw std::out_of_range(ss.str());
				return ((*this)[n]);
			}
			reference				front() { return *start; }
			const_reference			front() const { return *start; }
			reference				back() { return *(finish - 1); }
			const_reference			back() const { return *(finish - 1); }

			//						Modifiers

			template <class InputIterator,
						typename = typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type>
			void					assign(InputIterator first, InputIterator last)
			{
				size_type	n = ft::distance(first, last);
				if (n > capacity())
				{
					clear();
					_alloc.deallocate(start, capacity());
					start = _alloc.allocate(n);
					finish = start;
					end_of_storage = start + n;
				}
				else
				{
					if (n != capacity())
					{
						iterator	temp = start + n;
						iterator	end = this->end();
						while (temp != end)
						{
							_alloc.destroy(&(*temp));
							++temp;
						}
					}
					finish = start;
				}
				while (first != last)
				{
					_alloc.construct(finish, *first);
					++finish;
					++first;
				}
			}
			void					assign(size_type n, const value_type& val) 
			{
				if (n > capacity())
				{
					clear();
					_alloc.deallocate(start, capacity());
					start = _alloc.allocate(n);
					finish = start;
					end_of_storage = start + n;
				}
				else
				{
					if (n != capacity())
					{
						iterator	temp = start + n;
						iterator	end = this->end();
						while (temp != end)
						{
							_alloc.destroy(&(*temp));
							++temp;
						}
					}
					finish = start;
				}
				for (size_type i = 0; i < n; i++)
				{
					_alloc.construct(finish, val);
					++finish;
				}
			}
			void					push_back(const value_type& val)
			{
				if (finish == end_of_storage)
				{
					size_type	new_capacity = capacity() * 2;
					if (new_capacity == 0)
						new_capacity = 1;
					reserve(new_capacity);
				}
				_alloc.construct(finish, val);
				++finish;
			}
			void					pop_back()
			{
				_alloc.destroy(finish);
				--finish;
			}
			iterator				insert(iterator position, const value_type& val)
			{
				size_type	pos_idx = &(*position) - start;
				insert(position, 1, val);
				return (start + pos_idx);
			}
			void					insert(iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				if (size() + n <= capacity())
				{
					value_type	copy(val);
					iterator	tmp = start + size() + n - 1;
					while (tmp != position + n - 1)
					{
						_alloc.construct(&(*tmp), *(tmp - n));
						--tmp;
					}
					for (size_type i = 0; i < n; i++)
					{
						_alloc.construct(&(*tmp), copy);
						--tmp;
					}
					finish += n;
				}
				else
				{
					size_type	pos_idx = &(*position) - start;
					size_type	new_capacity = size() * 2;
					if (new_capacity < size() + n)
						new_capacity = size() + n;
					if (new_capacity > max_size())
						throw std::length_error("vector::insert ");
					size_type	old_size = size();
					size_type	old_capacity = capacity();
					pointer		old_start = start;
					start = _alloc.allocate(new_capacity);
					finish = start;
					end_of_storage = start + new_capacity;
					for (size_type i = 0; i < old_size + n; i++)
					{
						if (i >= pos_idx && i < pos_idx + n)
							_alloc.construct(finish, val);
						else
						{
							_alloc.construct(finish, *old_start);
							_alloc.destroy(old_start);
							++old_start;
						}
						++finish;
					}
					old_start -= old_size;
					_alloc.deallocate(old_start, old_capacity);
				}
			}
			template <class InputIterator,
						typename = typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type>
    		void					insert(iterator position, InputIterator first, InputIterator last)
			{
				size_type	n = ft::distance(first, last);
				if (n == 0)
					return ;
				if (size() + n <= capacity())
				{
					iterator	tmp = start + size() + n - 1;
					while (tmp != position + n - 1)
					{
						_alloc.construct(&(*tmp), *(tmp - n));
						--tmp;
					}
					for (size_type i = 0; i < n; i++)
					{
						--last;
						_alloc.construct(&(*tmp), *last);
						--tmp;
					}
					finish += n;
				}
				else
				{
					size_type	pos_idx = &(*position) - start;
					size_type	new_capacity = size() * 2;
					if (new_capacity < size() + n)
						new_capacity = size() + n;
					if (new_capacity > max_size())
						throw std::length_error("vector::insert ");
					size_type	old_size = size();
					size_type	old_capacity = capacity();
					pointer		old_start = start;
					start = _alloc.allocate(new_capacity);
					finish = start;
					end_of_storage = start + new_capacity;
					for (size_type i = 0; i < old_size + n; i++)
					{
						if (i >= pos_idx && i < pos_idx + n)
						{
							_alloc.construct(finish, *first);
							++first;
						}
						else
						{
							_alloc.construct(finish, *old_start);
							_alloc.destroy(old_start);
							++old_start;
						}
						++finish;
					}
					old_start -= old_size;
					_alloc.deallocate(old_start, old_capacity);
				}
			}
			iterator				erase(iterator position)
			{
				return (erase(position, position + 1));
			}
			iterator				erase(iterator first, iterator last)
			{
				size_type	n = ft::distance(start, &(*first));
				pointer		temp = start + n;
				pointer		last_ptr = &(*last);
				while (last_ptr != finish)
				{
					_alloc.construct(temp, *last_ptr);
					++temp;
					++last_ptr;
				}
				pointer		new_finish = temp;
				while (temp != finish)
				{
					_alloc.destroy(temp);
					++temp;
				}
				finish = new_finish;
				return (iterator(start + n));
			}
			void					swap(vector& x)
			{
				if (&x == this)
					return ;
				allocator_type	temp_alloc = _alloc;
				pointer			temp_start = start;
				pointer			temp_finish = finish;
				pointer			temp_end_of_storage = end_of_storage;
				_alloc = x._alloc;
				start = x.start;
				finish = x.finish;
				end_of_storage = x.end_of_storage;
				x._alloc = temp_alloc;
				x.start = temp_start;
				x.finish = temp_finish;
				x.end_of_storage = temp_end_of_storage;
			}
			void					clear()
			{
				while (finish != start)
				{
					--finish;
					_alloc.destroy(finish);
				}
			}

			//						Allocator

			allocator_type			get_allocator() const { return allocator_type(_alloc); }
		private:
			allocator_type	_alloc;
			pointer			start;
			pointer			finish;
			pointer			end_of_storage;
	};

	//								Non-member function overloads

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T, Alloc>::const_iterator	beginl = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator	beginr = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator	endl = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator	endr = rhs.end();
		while (beginl != endl)
		{
			if (beginr == endr || *beginl != *beginr)
				return (false);
			++beginl;
			++beginr;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
