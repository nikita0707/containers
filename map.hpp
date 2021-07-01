#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "utils.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		class value_compare : public ft::binary_function<value_type, value_type, bool>
		{
			friend class map<Key, T, Compare, Alloc>;
			protected:
				Compare	comp;
				value_compare(Compare c) : comp(c) {}
			public:
				bool	operator()(const value_type& x, const value_type& y) const
				{
					return (comp(x.first, y.first));
				}
		};
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
	};
}

#endif
