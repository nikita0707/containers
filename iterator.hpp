#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "iterator_traits.hpp"
# include "RBNode.hpp"

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

			random_access_iterator() : ptr(0) {}

			random_access_iterator(const random_access_iterator& copy) : ptr(copy.ptr) {}

			random_access_iterator(pointer ptr) : ptr(ptr) {}

			template <typename Iter>
			random_access_iterator(const random_access_iterator<Iter>& i) : ptr(i.base()) {}

			random_access_iterator&	operator=(const random_access_iterator& other)
			{
				if (this != &other)
					ptr = other.ptr;
				return (*this);
			}

			virtual ~random_access_iterator() {}

			pointer					base() const { return ptr; }

			reference				operator*() const { return *(ptr); }

			pointer					operator->() { return ptr; }

			random_access_iterator&	operator++() { ++(ptr); return *this; }

			random_access_iterator	operator++(int) { random_access_iterator temp(ptr); ++(ptr); return temp; }

			random_access_iterator&	operator--() { --(ptr); return *this; }

			random_access_iterator	operator--(int) { random_access_iterator temp(ptr); --(ptr); return temp; }

			random_access_iterator	operator+(difference_type n) const { return ptr + n; }

			random_access_iterator	operator-(difference_type n) const { return ptr - n; }

			random_access_iterator&	operator+=(difference_type n) { ptr += n; return *this; }

			random_access_iterator&	operator-=(difference_type n) { ptr -= n; return *this; }

			reference				operator[](difference_type n) { return *(ptr + n); }
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
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
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
									InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!(*first1 == *first2))
				return false;
		return true;
	}

	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!p(*first1, *first2))
				return false;
		return true;
	}

	template <typename T>
	class RBTree_iterator : public ft::bidirectional_iterator<T>
	{
		public:
			typedef T													value_type;
			typedef typename ft::bidirectional_iterator<T>::iterator_category	iterator_category;
			typedef typename ft::bidirectional_iterator<T>::difference_type		difference_type;
			typedef typename ft::bidirectional_iterator<T>::pointer				pointer;
			typedef typename ft::bidirectional_iterator<T>::reference			reference;
			typedef RBTree_iterator<T>											_Self;
			typedef RBNode<T>*													_Base_ptr;
			typedef RBNode<T>*													_Link_type;
			RBTree_iterator() : _M_node() {}
			explicit RBTree_iterator(_Base_ptr x) : _M_node(x) {}
			RBTree_iterator(const RBTree_iterator& copy) : _M_node(copy._M_node) {}
			~RBTree_iterator() {}
			RBTree_iterator	&operator=(const RBTree_iterator& other)
			{
				if (this != &other)
					_M_node = other._M_node;
				return (*this);
			}
			reference	operator*() const { return _M_node->value; }
			pointer		operator->() const { return &(_M_node->value); }
			_Self&		operator++() { _M_node = RBTreeIncrement(); return *this; }
			_Self		operator++(int) { _Self tmp = *this; _M_node = RBTreeIncrement(); return tmp; }
			_Self&		operator--() { _M_node = RBTreeDecrement(); return *this; }
			_Self		operator--(int) { _Self tmp = *this; _M_node = RBTreeDecrement(); return tmp; }
			friend bool	operator==(const _Self&x, const _Self&y) { return x._M_node == y._M_node; }
			friend bool	operator!=(const _Self&x, const _Self&y) { return x._M_node != y._M_node; }
			_Base_ptr	_M_node;
		private:
			_Base_ptr	RBTreeIncrement()
			{
				_Base_ptr	x = _M_node;
				if (x->right != 0)
				{
					x = x->right;
					while (x->left != 0)
						x = x->left;
				}
				else
				{
					_Base_ptr	y = x->parent;
					while (x == y->right)
					{
						x = y;
						y = y->parent;
					}
					if (x->right != y)
						x = y;
				}
				return x;
			}
			_Base_ptr	RBTreeDecrement()
			{
				_Base_ptr	x = _M_node;
				if (x->color == red && x->parent->parent == x)
					x = x->right;
				else if (x->left != 0)
				{
					_Base_ptr	y = x->left;
					while (y->right != 0)
						y = y->right;
					x = y;
				}
				else
				{
					_Base_ptr	y = x->parent;
					while (x == y->left)
					{
						x = y;
						y = y->parent;
					}
					x = y;
				}
				return x;
			}
	};

	template <typename T>
	class RBTree_const_iterator : public ft::bidirectional_iterator<const T>
	{
		public:
			typedef T															value_type;
			typedef typename ft::bidirectional_iterator<T>::iterator_category	iterator_category;
			typedef typename ft::bidirectional_iterator<T>::difference_type		difference_type;
			typedef typename ft::bidirectional_iterator<const T>::pointer		pointer;
			typedef typename ft::bidirectional_iterator<const T>::reference		reference;
			typedef RBTree_const_iterator<T>									_Self;
			typedef const RBNode<T>*											_Base_ptr;
			typedef const RBNode<T>*											_Link_type;
			typedef RBTree_iterator<T>											iterator;
			RBTree_const_iterator() : _M_node() {}
			explicit RBTree_const_iterator(_Base_ptr x) : _M_node(x) {}
			RBTree_const_iterator(const RBTree_const_iterator& copy) : _M_node(copy._M_node) {}
			template <typename Iter>
			RBTree_const_iterator(const RBTree_iterator<Iter>& i) : _M_node(i._M_node) {}
			~RBTree_const_iterator() {}
			RBTree_const_iterator	&operator=(const RBTree_const_iterator& other)
			{
				if (this != &other)
					_M_node = other._M_node;
				return (*this);
			}
			iterator	_M_const_cast() const { return iterator(const_cast<_Base_ptr>(_M_node)); }
			reference	operator*() const { return _M_node->value; }
			pointer		operator->() const { return &(_M_node->value); }
			_Self&		operator++() { _M_node = RBTreeIncrement(); return *this; }
			_Self		operator++(int) { _Self tmp = *this; _M_node = RBTreeIncrement(); return tmp; }
			_Self&		operator--() { _M_node = RBTreeDecrement(); return *this; }
			_Self		operator--(int) { _Self tmp = *this; _M_node = RBTreeDecrement(); return tmp; }
			friend bool	operator==(const _Self&x, const _Self&y) { return x._M_node == y._M_node; }
			friend bool	operator!=(const _Self&x, const _Self&y) { return x._M_node != y._M_node; }
			_Base_ptr	_M_node;
		private:
			_Base_ptr		RBTreeIncrement()
			{
				_Base_ptr	x = _M_node;
				if (x->right != 0)
				{
					x = x->right;
					while (x->left != 0)
						x = x->left;
				}
				else
				{
					_Base_ptr	y = x->parent;
					while (x == y->right)
					{
						x = y;
						y = y->parent;
					}
					if (x->right != y)
						x = y;
				}
				return x;
			}
			_Base_ptr		RBTreeDecrement()
			{
				_Base_ptr	x = _M_node;
				if (x->color == red && x->parent->parent == x)
					x = x->right;
				else if (x->left != 0)
				{
					_Base_ptr	y = x->left;
					while (y->right != 0)
						y = y->right;
					x = y;
				}
				else
				{
					_Base_ptr	y = x->parent;
					while (x == y->left)
					{
						x = y;
						y = y->parent;
					}
					x = y;
				}
				return x;
			}
	};
}

#endif
