#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "iterator.hpp"
# include "reverse_iterator.hpp"
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
			: _alloc(alloc), start(nullptr), finish(nullptr), end_of_storage(nullptr) {}

			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type())
			: _alloc(alloc), start(nullptr), finish(nullptr), end_of_storage(nullptr)
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

			template <class InputIterator>
         	vector(InputIterator first, InputIterator last,
			 		const allocator_type& alloc = allocator_type())
			: _alloc(alloc), start(nullptr), finish(nullptr), end_of_storage(nullptr)
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
			: _alloc(x._alloc), start(nullptr), finish(nullptr), end_of_storage(nullptr)
			{
				iterator	first = x.begin();
				iterator	last = x.end();
				difference_type	n = ft::distance(x.begin(), x.end());
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

			~vector() { clear(); _alloc.deallocate(start, capacity()); }

			vector&	operator=(const vector& other)
			{
				if (&other != this)
				{
					clear();
					// insert(end(), other.begin(), other.end());
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
				size_type	pos_idx = &(*position) - start;
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
			template <class InputIterator>
    		void					insert(iterator position, InputIterator first, InputIterator last) {}
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
}

#endif
