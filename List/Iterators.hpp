#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include "Node.hpp"

namespace ft
{
	template <typename T>
	class ListIterator
	{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			Node<T>			*_M_node;
			ListIterator() : _M_node(nullptr) {}
			ListIterator(Node<T> *ptr) : _M_node(ptr) {}
			ListIterator(const ListIterator& copy) : _M_node(copy._M_node) {}
			ListIterator&	operator=(const ListIterator& other) { if (&other != this) { _M_node = other._M_node; } return *this; }
			~ListIterator() {}
			bool			operator==(const ListIterator<T>& other) const { return _M_node == other._M_node; }
			bool			operator!=(const ListIterator<T>& other) const { return _M_node != other._M_node; }
			ListIterator&	operator++() { _M_node = _M_node->next; return *this; }
			ListIterator	operator++(int) { ListIterator<T> temp = *this; _M_node = _M_node->next; return temp; }
			ListIterator&	operator--() { _M_node = _M_node->prev; return *this; }
			ListIterator	operator--(int) { ListIterator<T> temp = *this; _M_node = _M_node->prev; return temp; }
			reference		operator*() const { return _M_node->data; }
			pointer			operator->() const { return &(_M_node->data); }
	};

	template <typename T>
	class ConstListIterator
	{
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			const Node<T>		*_M_node;
			ConstListIterator() : _M_node(nullptr) {}
			ConstListIterator(Node<T> *ptr) : _M_node(ptr) {}
			ConstListIterator(const ConstListIterator& copy) : _M_node(copy._M_node) {}
			ConstListIterator&	operator=(const ConstListIterator& other) { if (&other != this) { _M_node = other._M_node; } return *this; }
			~ConstListIterator() {}
			bool				operator==(const ConstListIterator<T>& other) const { return _M_node == other._M_node; }
			bool				operator!=(const ConstListIterator<T>& other) const { return _M_node != other._M_node; }
			ConstListIterator&	operator++() { _M_node = _M_node->next; return *this; }
			ConstListIterator	operator++(int) { ConstListIterator<T> temp = *this; _M_node = _M_node->next; return temp; }
			ConstListIterator&	operator--() { _M_node = _M_node->prev; return *this; }
			ConstListIterator	operator--(int) { ConstListIterator<T> temp = *this; _M_node = _M_node->prev; return temp; }
			reference			operator*() const { return _M_node->data; }
			pointer				operator->() const { return &(_M_node->data); }
	};
}

#endif
