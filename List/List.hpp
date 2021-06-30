#ifndef LIST_HPP
# define LIST_HPP

# include <stddef.h>
# include <string>
# include "../ReverseIterator.hpp"
# include "Iterators.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class List
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ft::ListIterator<T> iterator;
			typedef ft::ConstListIterator<T> const_iterator;
			typedef ft::ReverseIterator<iterator> reverse_iterator;
			typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef size_t size_type;

			explicit List(const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				create_first_node();
			}

			explicit List(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				create_first_node();
				for (size_type i = 0; i < n; i++)
					push_front(T(val));
			}

			template <class InputIterator>
  			List(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				create_first_node();
				while (first != last)
				{
					push_front(T(*first));
					first++;
				}
			}

			List(const List& x) : _alloc(x._alloc)
			{
				create_first_node();
				const_iterator	begin = x.begin();
				const_iterator	end = x.end();

				while (begin != end)
				{
					push_front(T(*begin));
					begin++;
				}
			}

			List	&operator=(const List& other)
			{}

			~List()
			{
				// while (head)
				// {
				// 	Node<T> *temp = head;
				// 	head = head->next;
				// 	delete temp;
				// }
			}

			void	push_front(const value_type& val)
			{
				Node<T> *temp = create_node(val);
				temp->prev = head->prev;
				temp->next = head;
				head->prev->next = temp;
				head->prev = temp;
				head = temp;
				size++;
			}

			iterator	begin() { return iterator(head); }
			const_iterator	begin() const { return const_iterator(head); }
			iterator	end() { return iterator(tail); }
			const_iterator	end() const { return const_iterator(tail); }

		private:
			typedef typename allocator_type::template rebind<Node<T> >::other node_allocator;
			Node<T>		*head;
			Node<T>		*tail;
			size_type	size;

			allocator_type	_alloc;
			node_allocator	_node_alloc;

			Node<T>*	create_node(const T& data)
			{
				Node<T>*	node = _node_alloc.allocate(1);
				_node_alloc.construct(node, Node<T>());
				node->data = data;
				node->prev = nullptr;
				node->next = nullptr;
				return node;
			}

			void		create_first_node()
			{
				T	end = T();
				head = create_node(end);
				head->prev = head;
				head->next = head;
				tail = head;
			}

			void		delete_node(Node<T>* node)
			{
				if (node->prev != nullptr)
					node->prev->next = node->next;
				if (node->next != nullptr)
					node->next->prev = node->prev;
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}
	};
}

#endif
