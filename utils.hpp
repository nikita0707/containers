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
	std::pair<T1,T2>	make_pair(T1 t, T2 u) { return ft::pair<T1, T2>(t, u); }

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

	template <typename Key, typename Value, typename Alloc = std::allocator<ft::pair<Key, Value> > >
	ft::pair<Key, Value>	mapFiller(Key key, Value value)
	{
		Alloc					alloc;
		ft::pair<Key, Value>	pair = alloc.allocate(1);
		pair->first = key;
		pair->second = value;
		return (pair);
	}

	template <typename Key, typename Val, typename Compare = std::less<Val>, typename Alloc = std::allocator<Val> >
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
		protected:
			typedef RBNode<value_type>*										link_type;
			typedef const RBNode<value_type>*								const_link_type;
		private:
			typedef typename Alloc::template rebind<RBNode<Val> >::other	node_allocator_type;
			typedef RBNode<Val>												node;
			allocator_type													_alloc;
			node_allocator_type												node_alloc;
			node															root;

			link_type	create_node(const value_type& x)
			{
				link_type	tmp = node_alloc.allocate(1);
				node_alloc.construct(tmp->value, x);
				return tmp;
			}
	};
}

#endif
