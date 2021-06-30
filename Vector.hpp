#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "iterator.hpp"
# include "reverse_iterator.hpp"

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

			explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), start(nullptr), finish(nullptr) {}

			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type()) : _alloc(alloc), start(nullptr), finish(nullptr)
			{
				start = _alloc.allocate(n);
				finish = start;
				for (difference_type i = 0; i < n; i++)
				{
					_alloc.construct(finish, val);
					finish++;
				}
			}

			template <class InputIterator>
         	vector(InputIterator first, InputIterator last,
			 		const allocator_type& alloc = allocator_type()) : _alloc(alloc), start(nullptr), finish(nullptr)
			{
				difference_type	n = ft::distance(first, last);
				start = _alloc.allocate(n);
				finish = start;
				while (first != last)
				{
					_alloc.construct(finish, *first);
					first++;
					finish++;
				}
			}

			vector(const vector& x) : _alloc(x._alloc), start(nullptr), finish(nullptr)
			{
				iterator	first = x.begin();
				iterator	last = x.end();
				difference_type	n = ft::distance(x.begin(), x.end());
				start = _alloc.allocate(n);
				finish = start;
				while (first != last)
				{
					_alloc.construct(finish, *first);
					first++;
					finish++;
				}
			}

			~vector() {} //clear

			vector&	operator=(const vector& other)
			{
				if (&other != this)
				{
					// clear insert
				}
				return (*this);
			}

			iterator				begin() { return start; }
			const_iterator			begin() const { return start; }
			iterator				end() { return finish; }
			const_iterator			end() const { return finish; }
			reverse_iterator		rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator		rend() { return reverse_iterator(begin()); }
			const_reverse_iterator	rend() const { return reverse_iterator(begin()); }
		private:
			allocator_type	_alloc;
			pointer			start;
			pointer			finish;
	};
}

#endif
