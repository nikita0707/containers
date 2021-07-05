#ifndef UTILS_HPP
# define UTILS_HPP

# include "reverse_iterator.hpp"
# include "iterator.hpp"
# include "RBNode.hpp"

namespace ft
{
	template <bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };

	template<typename Tname, Tname v>
	struct integral_constant
	{
		static constexpr Tname					value = v;
		typedef Tname							value_type;
		typedef integral_constant<Tname, v>		type;
		constexpr operator value_type() const noexcept { return value; }
	};

	typedef integral_constant<bool, true>		true_type;
	typedef integral_constant<bool, false>		false_type;

	template<typename>
	struct is_integral_helper : public false_type {};

	template<>
	struct is_integral_helper<bool> : public true_type {};

	template<>
	struct is_integral_helper<char> : public true_type {};

	template<>
	struct is_integral_helper<signed char> : public true_type {};

	template<>
	struct is_integral_helper<unsigned char> : public true_type {};

	template<>
	struct is_integral_helper<char16_t> : public true_type {};

	template<>
	struct is_integral_helper<char32_t> : public true_type {};

	template<>
	struct is_integral_helper<wchar_t> : public true_type {};

	template<>
	struct is_integral_helper<short> : public true_type {};

	template<>
	struct is_integral_helper<unsigned short> : public true_type {};

	template<>
	struct is_integral_helper<int> : public true_type {};

	template<>
	struct is_integral_helper<unsigned int> : public true_type {};

	template<>
	struct is_integral_helper<long> : public true_type {};

	template<>
	struct is_integral_helper<unsigned long> : public true_type {};

	template<>
	struct is_integral_helper<long long> : public true_type {};

	template<>
	struct is_integral_helper<unsigned long long> : public true_type {};

	template <class T>
	struct is_integral : public is_integral_helper<T>::type {};

	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;
		first_type	first;
		second_type	second;
		pair() : first(), second() {}
		pair(const T1& x, const T2& y) : first(x), second(y) {}
		template<class U1, class U2>
		pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
		pair&		operator=(const pair& other)
		{
			if (this != &other)
			{
				first = other.first;
				second = other.second;
			}
			return (*this);
		}
	};

	template <class T1, class T2>
	ft::pair<T1,T2>		make_pair(T1 t, T2 u) { return ft::pair<T1, T2>(t, u); }

	template <class T1, class T2>
	bool operator==(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == lhs.second);
	}

	template<class T1, class T2>
	bool operator!=(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
	{
		return (!(lhs == rhs));
	}

	template<class T1, class T2>
	bool operator<(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
	{
		return ((lhs.first < rhs.first) || ((lhs.first == rhs.first) && lhs.second < rhs.second));
	}

	template<class T1, class T2>
	bool operator<=(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
	{
		return (!(rhs < lhs));
	}

	template<class T1, class T2>
	bool operator>(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>=(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <typename T>
	void	swap(T& a, T& b)
	{
		T	tmp = a;
		a = b;
		b = tmp;
	}

	template <typename Arg1, typename Arg2, typename Result>
	struct binary_function
	{
		typedef Arg1	first_argument_type;
		typedef Arg2	second_argument_type;
		typedef Result	result_type;
	};

	template <typename T>
	struct Idenity
	{
		T&			operator()(T& x) const { return x; }
		const T&	operator()(const T& x) const { return x; }
	};

	template <typename Pair>
	struct Select1st
	{
		typename Pair::first_type&			operator()(Pair& x) const { return x.first; }
		const typename Pair::first_type&	operator()(const Pair& x) const { return x.first; }
	};

	template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Val> >
	class RBTree
	{
		public:
			typedef Key														key_type;
			typedef Val														value_type;
			typedef value_type*												pointer;
			typedef const value_type*										const_pointer;
			typedef value_type&												reference;
			typedef const value_type&										const_reference;
			typedef size_t													size_type;
			typedef ptrdiff_t												difference_type;
			typedef Alloc													allocator_type;
			typedef ft::RBTree_iterator<value_type>							iterator;
			typedef ft::RBTree_const_iterator<value_type>					const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		private:
			typedef typename Alloc::template rebind<RBNode<Val> >::other	node_allocator_type;
			typedef RBNode<value_type>*										node;
			typedef const RBNode<value_type>*								const_node;
		public:
			RBTree() {}
			RBTree(const Compare& comp, const allocator_type& alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _size(0) { create_header(); }
			RBTree(const RBTree& x) : _comp(x._comp), _alloc(x._alloc), _size(x._size)
			{
				create_header();
				if (x.header->parent != 0)
					header->parent = copy(x);
			}
			RBTree&	operator=(const RBTree& x)
			{
				if (this != &x)
				{
					clear();
					_comp = x._comp;
					get_key = x.get_key;
					if (x.header->parent != 0)
						header->parent = copy(x);
				}
				return (*this);
			}
			~RBTree() { erase(header->parent); node_alloc.deallocate(header, 1); }

			iterator	begin() { return iterator(header->left); }
			const_iterator	begin() const { return const_iterator(header->left); }
			iterator				end() { return iterator(header); }
			const_iterator			end() const { return const_iterator(header); }
			reverse_iterator		rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator		rend() { return reverse_iterator(begin()); }
			const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }
			
			bool					empty() const { return !_size; }
			size_type				size() const { return _size; }
			size_type				max_size() const { return node_alloc.max_size(); }

			pair<iterator, bool>	insert_unique(const value_type& val)
			{
				typedef pair<iterator, bool>	_res;
				ft::pair<node, node>	res = get_insert_unique_pos(get_key(val));

				_res	ret;
				if (res.second)
					return _res(insert(res.first, res.second, val), true);
				return _res(iterator(res.first), false);
			}

			iterator				insert_unique(iterator position, const value_type& val)
			{
				pair<node, node>	res = insert_hint_unique_pos(position, get_key(val));

				iterator	ret;
				if (res.second)
					return insert(res.first, res.second, val);
				return iterator(res.first);
			}

			template <typename InputIterator>
			void					insert_range_unique(InputIterator first, InputIterator last)
			{
				for (; first != last; ++first)
					insert_unique(end(), *first);
			}

			void					erase(iterator position)
			{
				if (position != end())
					erase_aux(position);
			}

			size_type				erase(const key_type& k)
			{
				ft::pair <iterator, iterator>	p = _equal_range(k);
				const size_type					old_size = _size;

				erase_aux(p.first, p.second);
				return old_size - _size;
			}

			void					erase(iterator first, iterator last)
			{
				erase_aux(first, last);
			}

			void					swap(RBTree& t)
			{
				ft::swap(header, t.header);
				ft::swap(_size, t._size);
			}

			void					clear()
			{
				erase(header->parent);
				reset_header();
				_size = 0;
			}

			iterator				find(const key_type& k)
			{
				iterator	j = lower_bound(header->parent, header, k);
				if (j == end() || _comp(k, get_key(j._M_node->value)))
					return end();
				return j;
			}
			
			const_iterator			find(const key_type& k) const
			{
				const_iterator	j = lower_bound(header->parent, header, k);
				if (j == end() || _comp(k, get_key(j._M_node->value)))
					return end();
				return j;
			}

			iterator				lower_bound(const key_type& k) { return lower_bound(header->parent, header, k); }
			
			const_iterator			lower_bound(const key_type& k) const { return lower_bound(header->parent, header, k); }

			iterator				upper_bound(const key_type& k) { return upper_bound(header->parent, header, k); }

			const_iterator			upper_bound(const key_type& k) const { return upper_bound(header->parent, header, k); }

			pair<iterator,iterator>	equal_range(const key_type& k) { return _equal_range(k); }
			
			pair<const_iterator,const_iterator>	equal_range(const key_type& k) const { return _equal_range(k); }

		protected:
			typedef RBNode<value_type>*										link_type;
			typedef const RBNode<value_type>*								const_link_type;
		private:
			Compare															_comp;
			allocator_type													_alloc;
			node_allocator_type												node_alloc;
			node															header;
			size_type														_size;
			KeyOfValue														get_key;

			void	reset_header()
			{
				header->left = header;
				header->right = header;
				header->parent = 0;
			}

			void	create_header()
			{
				header = node_alloc.allocate(1);
				reset_header();
				header->color = red;
			}

			node	create_node(const value_type& x)
			{
				node	tmp = node_alloc.allocate(1);
				node_alloc.construct(&(tmp->value), x);
				tmp->left = 0;
				tmp->right = 0;
				tmp->parent = 0;
				tmp->color = black;
				return tmp;
			}

			ft::pair<node, node>	get_insert_unique_pos(const key_type k)
			{
				typedef ft::pair<node, node>	res;
				node	x = static_cast<node>(header->parent);
				node	y = header;
				bool	comp = true;
				while (x != 0)
				{
					y = x;
					comp = _comp(k, get_key(x->value));
					x = comp ? x->left : x->right;
				}
				iterator	j = iterator(y);
				if (comp)
				{
					if (j == begin())
						return res(x, y);
					else
						--j;
				}
				if (_comp(get_key(j._M_node->value), k))
					return res(x, y);
				return res(j._M_node, 0);
			}

			void					tree_rotate_left(node x, node& r)
			{
				node const y = x->right;

				x->right = y->left;
				if (y->left !=0)
					y->left->parent = x;
				y->parent = x->parent;
				if (x == r)
					r = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void					tree_rotate_right(node x, node& r)
			{
				node const y = x->left;
				
				x->left = y->right;
				if (y->right != 0)
					y->right->parent = x;
				y->parent = x->parent;
				if (x == r)
					r = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			void					insert_and_rebalance(const bool insert_left, node x, node p)
			{
				x->parent = p;
				x->left = 0;
				x->right = 0;
				x->color = red;
				if (insert_left)
				{
					p->left = x;
					if (p == header)
					{
						header->parent = x;
						header->right = x;
					}
					else if (p == header->left)
						header->left = x;
				}
				else
				{
					p->right = x;
					if (p == header->right)
						header->right = x;
				}
				node&	r = header->parent;
				while (x != r && x->parent->color == red)
				{
					node const xpp = x->parent->parent;
					if (x->parent == xpp->left)
					{
						node const y = xpp->right;
						if (y && y->color == red)
						{
							x->parent->color = black;
							y->color = black;
							xpp->color = red;
							x = xpp;
						}
						else
						{
							if (x == x->parent->right)
							{
								x = x->parent;
								tree_rotate_left(x, r);
							}
							x->parent->color = black;
							xpp->color = red;
							tree_rotate_right(xpp, r);
						}
					}
					else
					{
						node const y = xpp->left;
						if (y && y->color == red)
						{
							x->parent->color = black;
							y->color = black;
							xpp->color = red;
							x = xpp;
						}
						else
						{
							if (x == x->parent->left)
							{
								x = x->parent;
								tree_rotate_right(x, r);
							}
							x->parent->color = black;
							xpp->color = red;
							tree_rotate_left(xpp, r);
						}
					}
				}
				r->color = black;
			}

			iterator				insert(node x, node p, const value_type& val)
			{
				bool insert_left = (x != 0 || p == header || _comp(get_key(val), get_key(p->value)));
				node	z = create_node(val);
				insert_and_rebalance(insert_left, z, p);
				++_size;
				return iterator(z);
			}

			node					leftmost() { return header->left; }

			node					rightmost() { return header->right; }

			pair<node, node>		insert_hint_unique_pos(iterator pos, const key_type& k)
			{
				typedef pair<node, node>	_res;

				if (pos._M_node == header)
				{
					node	rig = rightmost();
					if (_size > 0 && _comp(get_key(rig->value), k))
						return _res(0, rig);
					else
						return get_insert_unique_pos(k);
				}
				else if (_comp(k, get_key(pos._M_node->value)))
				{
					node	lft = leftmost();
					iterator	before = pos;
					if (pos._M_node == lft)
						return _res(lft, lft);
					else if (_comp(get_key((--before)._M_node->value), k))
					{
						if (before._M_node->right == 0)
							return _res(0, before._M_node);
						else
							return _res(pos._M_node, pos._M_node);
					}
					else
						return get_insert_unique_pos(k);
				}
				else if (_comp(get_key(pos._M_node->value), k))
				{
					node	rig = rightmost();
					iterator	after = pos;
					if (pos._M_node == rig)
						return _res(0, rig);
					else if (_comp(k, get_key((++after)._M_node->value)))
					{
						if (pos._M_node->right == 0)
							return _res(0, pos._M_node);
						else
							return _res(after._M_node, after._M_node);
					}
					else
						return get_insert_unique_pos(k);
				}
				else
					return _res(pos._M_node, 0);
			}

			node					minimum(node x)
			{
				while (x->left)
					x = x->left;
				return (x);
			}

			node					maximum(node x)
			{
				while (x->right)
					x = x->right;
				return (x);
			}

			node					rebalance_for_erase(node z)
			{
				node&	root = header->parent;
				node&	lft = header->left;
				node&	rig = header->right;
				node	y = z;
				node	x = 0;
				node	x_parent = 0;

				if (y->left == 0)
					x = y->right;
				else if (y->right == 0)
					x = y->left;
				else
				{
					y = y->right;
					while (y->left != 0)
						y = y->left;
					x = y->right;
				}
				if (y != z)
				{
					z->left->parent = y;
					y->left = z->left;
					if (y != z->right)
					{
						x_parent = y->parent;
						if (x) x->parent = y->parent;
							y->parent->left = x;
						y->right = z->right;
						z->right->parent = y;
					}
					else
						x_parent = y;
					if (root == z)
						root = y;
					else if (z->parent->left == z)
						z->parent->left = y;
					else
						z->parent->right = y;
					y->parent = z->parent;
					ft::swap(y->color, z->color);
					y = z;
				}
				else
				{
					x_parent = y->parent;
					if (x)
						x->parent = y->parent;
					if (root == z)
						root = x;
					else if (z->parent->left == z)
						z->parent->left = x;
					else
						z->parent->right = x;
					if (lft == z)
					{
						if (z->right == 0)
							lft = z->parent;
						else
							lft = minimum(x);
					}
					if (rig == z)
					{
						if (z->left == 0)
							rig = z->parent;
						else
							rig = maximum(x);
					}
				}
				if (y->color != red)
				{
					while (x != root && (x == 0 || x->color == black))
						if (x == x_parent->left)
						{
							node	w = x_parent->right;
							if (w->color == red)
							{
								w->color = black;
								x_parent->color = red;
								tree_rotate_left(x_parent, root);
								w = x_parent->right;
							}
							if ((w->left == 0 || w->left->color == black) && \
								(w->right == 0 || w->right->color == black))
							{
								w->color = red;
								x = x_parent;
								x_parent = x_parent->parent;
							}
							else
							{
								if (w->right == 0 || w->right->color == black)
								{
									w->left->color = black;
									w->color = red;
									tree_rotate_right(w, root);
									w = x_parent->right;
								}
								w->color = x_parent->color;
								x_parent->color = black;
								if (w->right)
									w->right->color = black;
								tree_rotate_left(x_parent, root);
								break;
							}
						}
						else
						{
							node	w = x_parent->left;
							if (w->color == red)
							{
								w->color = black;
								x_parent->color = red;
								tree_rotate_right(x_parent, root);
								w = x_parent->left;
							}
							if ((w->right == 0 || w->right->color == black) && \
								(w->left == 0 || w->left->color == black))
							{
								w->color = red;
								x = x_parent;
								x_parent = x_parent->parent;
							}
							else
							{
								if (w->left == 0 || w->left->color == black)
								{
									w->right->color = black;
									w->color = red;
									tree_rotate_left(w, root);
									w = x_parent->left;
								}
								w->color = x_parent->color;
								x_parent->color = black;
								if (w->left)
									w->left->color = black;
								tree_rotate_right(x_parent, root);
								break;
							}
						}
					if (x)
						x->color = black;
				}
				return y;
			}

			void					drop_node(node p)
			{
				_alloc.destroy(&(p->value));
				node_alloc.deallocate(p, 1);
			}

			void					erase_aux(iterator position)
			{
				node	y = rebalance_for_erase(position._M_node);

				drop_node(y);
				--_size;
			}

			iterator				lower_bound(node x, node y, const key_type& k)
			{
				while (x != 0)
				{
					if (!_comp(get_key(x->value), k))
					{
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return iterator(y);
			}

			const_iterator			lower_bound(const_node x, const_node y, const key_type& k) const
			{
				while (x != 0)
				{
					if (!_comp(get_key(x->value), k))
					{
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return const_iterator(y);
			}

			iterator				upper_bound(node x, node y, const key_type& k)
			{
				while (x != 0)
				{
					if (_comp(k, get_key(x->value)))
					{
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return iterator(y);
			}

			const_iterator			upper_bound(const_node x, const_node y, const key_type& k) const
			{
				while (x != 0)
				{
					if (_comp(k, get_key(x->value)))
					{
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				return const_iterator(y);
			}

			ft::pair<iterator, iterator>	_equal_range(const key_type& k)
			{
				typedef ft::pair<iterator, iterator> _res;
				node	x = header->parent;
				node	y = header;

				while (x != 0)
				{
					if (_comp(get_key(x->value), k))
						x = x->right;
					else if (_comp(k, get_key(x->value)))
					{
						y = x;
						x = x->left;
					}
					else
					{
						node	xu(x);
						node	yu(y);
						y = x;
						x = x->left;
						xu = xu->right;
						return _res(lower_bound(x, y, k), upper_bound(xu, yu, k));
					}
				}
				return _res(iterator(y), iterator(y));
			}

			ft::pair<const_iterator, const_iterator>	_equal_range(const key_type& k) const
			{
				typedef ft::pair<const_iterator, const_iterator> _res;
				node	x = header->parent;
				node	y = header;

				while (x != 0)
				{
					if (_comp(get_key(x->value), k))
						x = x->right;
					else if (_comp(k, get_key(x->value)))
					{
						y = x;
						x = x->left;
					}
					else
					{
						node	xu(x);
						node	yu(y);
						y = x;
						x = x->left;
						xu = xu->right;
						return _res(lower_bound(x, y, k), upper_bound(xu, yu, k));
					}
				}
				return _res(const_iterator(y), const_iterator(y));
			}

			void					erase_aux(iterator first, iterator last)
			{
				if (first == begin() && last == end())
					clear();
				else
					while (first != last)
						erase_aux(first++);
			}

			void					erase(node x)
			{
				while (x != 0)
				{
					erase(x->right);
					node y = x->left;
					drop_node(x);
					x = y;
				}
			}

			node					clone_node(node x)
			{
				node	tmp = create_node(x->value);

				tmp->color = x->color;
				return tmp;
			}

			node					copy(node x, node p)
			{
				node	top = clone_node(x);

				top->parent = p;
				if (x->right)
					top->right = copy(x->right, top);
				p = top;
				x = x->left;
				while (x != 0)
				{
					node	y = clone_node(x);
					p->left = y;
					y->parent = p;
					if (x->right)
						y->right = copy(x->right, y);
					p = y;
					x = x->left;
				}
				return top;
			}

			node					copy(const RBTree& x)
			{
				node	root = copy(x.header->parent, header);
				header->left = minimum(root);
				header->right = maximum(root);
				_size = x._size;
				return root;
			}
	};
}

#endif
