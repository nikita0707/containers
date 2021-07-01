#ifndef UTILS_HPP
# define UTILS_HPP

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
}

#endif
