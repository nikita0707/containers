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
		pair&		operator=( const pair& other )
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
		public:
			RBTree() {}
			RBTree(const Compare& comp, const allocator_type& alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _size(0) { create_end_node(); }
			RBTree(const RBTree& x) : _comp(x._comp), _alloc(x._alloc), _size(0) { create_end_node(); }
			~RBTree() {}                                // impl
			iterator	begin()
			{
				node	tmp = root;
				while (tmp->left)
					tmp = tmp->left;
				return iterator(tmp);
			}
			const_iterator	begin() const
			{
				node	tmp = root;
				while (tmp->left)
					tmp = tmp->left;
				return const_iterator(tmp);
			}
			iterator				end() { return iterator(end_node); }
			const_iterator			end() const { return const_iterator(end_node); }
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

				if (res.second)
					return _res(insert(res.first, res.second, val), true);
				return _res(iterator(res.first), false);
			}
		protected:
			typedef RBNode<value_type>*										link_type;
			typedef const RBNode<value_type>*								const_link_type;
		private:
			Compare															_comp;
			allocator_type													_alloc;
			node_allocator_type												node_alloc;
			node															root;
			node															end_node;
			size_type														_size;
			KeyOfValue														get_key;

			void	create_end_node()
			{
				end_node = node_alloc.allocate(1);
				end_node->left = nullptr;
				end_node->right = nullptr;
				end_node->parent = nullptr;
				end_node->color = black;
				root = end_node;
			}

			node	create_node(const value_type& x)
			{
				node	tmp = node_alloc.allocate(1);
				node_alloc.construct(&(tmp->value), x);
				return tmp;
			}

			ft::pair<node, node>	get_insert_unique_pos(const key_type k)
			{
				typedef ft::pair<node, node>	res;
				node	x = root;
				node	y = end_node;
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

			void					tree_rotate_left(node x)
			{
				node const y = x->right;

				x->right = y->left;
				if (y->left !=0)
					y->left->parent = x;
				y->parent = x->parent;
				if (x == root)
					root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void					tree_rotate_right(node x)
			{
				node const y = x->left;
				
				x->left = y->right;
				if (y->right != 0)
					y->right->parent = x;
				y->parent = x->parent;
				if (x == root)
					root = y;
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
					p->left = x;
				else
					p->right = x;
				while (x != root && x->parent->color == red)
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
								tree_rotate_left(x);
							}
							x->parent->color = black;
							xpp->color = red;
							tree_rotate_right(xpp);
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
								tree_rotate_right(x);
							}
							x->parent->color = black;
							xpp->color = red;
							tree_rotate_left(xpp);
						}
					}
				}
				root->color = black;
			}

			iterator				insert(node x, node p, const value_type& val)
			{
				bool insert_left = (x != 0 || p == end_node || _comp(get_key(val), get_key(p->value)));
				node	z = create_node(val);
				insert_and_rebalance(insert_left, z, p);
				++_size;
				return iterator(z);
			}
	};
}

#endif
