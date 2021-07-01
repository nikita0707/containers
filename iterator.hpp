#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <stddef.h>

namespace ft
{
	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <typename T>
	struct bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type			value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer				pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference				reference;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category		iterator_category;
	};

	template <typename T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef T*																			pointer;
			typedef T&																			reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;

			random_access_iterator() : ptr(nullptr) {}

			random_access_iterator(const random_access_iterator& copy) : ptr(copy.ptr) {}

			random_access_iterator(pointer ptr) : ptr(ptr) {}

			random_access_iterator&	operator=(const random_access_iterator& other)
			{
				if (this != &other)
					this->ptr = other.ptr;
				return (*this);
			}

			virtual ~random_access_iterator() {}

			pointer	base() const { return this->ptr; }

			reference	operator*() const { return *(this->ptr); }

			pointer	operator->() { return this->ptr; }

			random_access_iterator&	operator++() { ++(this->ptr); return *this; }

			random_access_iterator&	operator++(int) { random_access_iterator temp(this->ptr); ++(this->ptr); return temp; }

			random_access_iterator&	operator--() { --(this->ptr); return *this; }

			random_access_iterator&	operator--(int) { random_access_iterator temp(this->ptr); --(this->ptr); return temp; }

			random_access_iterator	operator+(difference_type n) const { return this->ptr + n; }

			random_access_iterator	operator-(difference_type n) const { return this->ptr - n; }

			random_access_iterator&	operator+=(difference_type n) { this->ptr += n; return *this; }

			random_access_iterator&	operator-=(difference_type n) { this->ptr -= n; return *this; }

			reference				operator[](difference_type n) { return *(this->ptr + n); }
		private:
			pointer	ptr;
	};

	template <typename T>
	bool	operator==(const ft::random_access_iterator<T> lhs,
						const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() == rhs.base()); }

	template <typename L, typename R>
	bool	operator==(const ft::random_access_iterator<L> lhs,
						const ft::random_access_iterator<R> rhs)
	{ return (lhs.base() == rhs.base()); }

	template <typename T>
	bool	operator!=(const ft::random_access_iterator<T> lhs,
						const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() != rhs.base()); }

	template <typename L, typename R>
	bool	operator!=(const ft::random_access_iterator<L> lhs,
						const ft::random_access_iterator<R> rhs)
	{ return (lhs.base() != rhs.base()); }

	template <typename T>
	bool	operator<(const ft::random_access_iterator<T> lhs,
						const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() < rhs.base()); }

	template <typename L, typename R>
	bool	operator<(const ft::random_access_iterator<L> lhs,
						const ft::random_access_iterator<R> rhs)
	{ return (lhs.base() < rhs.base()); }

	template <typename T>
	bool	operator>(const ft::random_access_iterator<T> lhs,
						const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() > rhs.base()); }

	template <typename L, typename R>
	bool	operator>(const ft::random_access_iterator<L> lhs,
						const ft::random_access_iterator<R> rhs)
	{ return (lhs.base() > rhs.base()); }

	template <typename T>
	bool	operator<=(const ft::random_access_iterator<T> lhs,
						const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <typename L, typename R>
	bool	operator<=(const ft::random_access_iterator<L> lhs,
						const ft::random_access_iterator<R> rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <typename T>
	bool	operator>=(const ft::random_access_iterator<T> lhs,
						const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <typename L, typename R>
	bool	operator>=(const ft::random_access_iterator<L> lhs,
						const ft::random_access_iterator<R> rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type	operator-(const ft::random_access_iterator<T> lhs,
																		const ft::random_access_iterator<T> rhs)
	{ return (lhs.base() - rhs.base()); }

	template <typename L, typename R>
	typename ft::random_access_iterator<L>::difference_type	operator-(const ft::random_access_iterator<L> lhs,
																		const ft::random_access_iterator<R> rhs)
	{ return (lhs.base() - rhs.base()); }

	template <typename T>
	ft::random_access_iterator<T>	operator+(typename ft::random_access_iterator<T>::difference_type n,
												const ft::random_access_iterator<T> it)
	{ return ft::random_access_iterator<T>(it.base() + n); }

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type	distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type	n = 0;
		while (first != last)
		{
			++n;
			++first;
		}
		return (n);
	}

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
		{
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2,
								Compare comp)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}
}

#endif
