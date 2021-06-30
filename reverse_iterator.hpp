#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

# include <string>
# include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator														iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference			reference;
			typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
			reverse_iterator() : _it() {}
			explicit reverse_iterator(iterator_type it) : _it(it) {}
			reverse_iterator(const reverse_iterator& x) : _it(x._it) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& x) : _it(x.base()) {}
			~reverse_iterator() {}
			reverse_iterator&	operator++() { --_it; return *this; }
			reverse_iterator	operator++(int) { reverse_iterator temp = *this; --_it; return temp; }
			reverse_iterator&	operator--() { ++_it; return *this; }
			reverse_iterator	operator--(int) { reverse_iterator temp = *this; ++_it; return temp; }
			reference			operator*() const { iterator_type temp = _it; return *(--temp); }
			pointer				operator->() const { return &(operator*()); }
			iterator_type		base() const { return _it; }
			reverse_iterator		operator+(difference_type n) const { return reverse_iterator(_it - n); }
			reverse_iterator&	operator+=(difference_type n) { _it -= n; return *this; }
			reverse_iterator		operator-(difference_type n) const { return reverse_iterator(_it + n); }
			reverse_iterator&	operator-=(difference_type n) { _it += n; return *this; }
			reference			operator[](difference_type n) const { return base()[-n - 1]; }
		private:
			iterator_type	_it;
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lit, const reverse_iterator<Iterator>& rit)
	{ return lit.base() == rit.base(); }

	template <class LeftIt, class RightIt>
	bool operator==(const reverse_iterator<LeftIt>& lit, const reverse_iterator<LeftIt>& rit)
	{ return lit.base() == rit.base(); }

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lit, const reverse_iterator<Iterator>& rit)
	{ return lit.base() != rit.base(); }

	template <class LeftIt, class RightIt>
	bool operator!=(const reverse_iterator<LeftIt>& lit, const reverse_iterator<LeftIt>& rit)
	{ return lit.base() != rit.base(); }

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lit, const reverse_iterator<Iterator>& rit)
	{ return lit.base() < rit.base(); }

	template <class LeftIt, class RightIt>
	bool operator<(const reverse_iterator<LeftIt>& lit, const reverse_iterator<LeftIt>& rit)
	{ return lit.base() < rit.base(); }

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lit, const reverse_iterator<Iterator>& rit)
	{ return lit.base() <= rit.base(); }

	template <class LeftIt, class RightIt>
	bool operator<=(const reverse_iterator<LeftIt>& lit, const reverse_iterator<LeftIt>& rit)
	{ return lit.base() <= rit.base(); }

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lit, const reverse_iterator<Iterator>& rit)
	{ return lit.base() > rit.base(); }

	template <class LeftIt, class RightIt>
	bool operator>(const reverse_iterator<LeftIt>& lit, const reverse_iterator<LeftIt>& rit)
	{ return lit.base() > rit.base(); }

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lit, const reverse_iterator<Iterator>& rit)
	{ return lit.base() >= rit.base(); }

	template <class LeftIt, class RightIt>
	bool operator>=(const reverse_iterator<LeftIt>& lit, const reverse_iterator<LeftIt>& rit)
	{ return lit.base() >= rit.base(); }

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& lit,
																	const reverse_iterator<Iterator>& rit)
	{ return lit.base() - rit.base(); }

	template <class LeftIt, class RightIt>
	typename reverse_iterator<LeftIt>::difference_type	operator-(const reverse_iterator<LeftIt>& lit,
																const reverse_iterator<RightIt>& rit)
	{ return lit.base() - rit.base(); }

	template <class Iterator>
	reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n,
											const reverse_iterator<Iterator>& it)
	{ return reverse_iterator<Iterator>(it.base() - n); }
}

#endif
