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
		public:
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const key_type, mapped_type>						value_type;
			typedef Compare														key_compare;
			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Alloc>;
				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool	operator()(const value_type& x, const value_type& y) const
					{ return (comp(x.first, y.first)); }
			};
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
		private:
			typedef RBTree<key_type, value_type, Select1st<value_type>, key_compare, allocator_type>	tree_type;
		public:
			typedef typename tree_type::iterator								iterator;
			typedef typename tree_type::const_iterator							const_iterator;
			typedef typename tree_type::reverse_iterator						reverse_iterator;
			typedef typename tree_type::const_reverse_iterator					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef size_t														size_type;

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _comp(comp), _alloc(alloc), tree(comp, alloc) {}

			template <class InputIterator,
						typename = typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: _comp(comp), _alloc(alloc), tree(comp, alloc) { tree.insert_range_unique(first, last); }

			map(const map& x) : _comp(x._comp), _alloc(x._alloc), tree(x.tree) {}

			iterator				begin() { return tree.begin(); }
			const_iterator			begin() const { return tree.begin(); }
			iterator				end() { return tree.end(); }
			const_iterator			end() const { return tree.end(); }
			reverse_iterator		rbegin() { return tree.rbegin(); }
			const_reverse_iterator	rbegin() const { return tree.rbegin(); }
			reverse_iterator		rend() { return tree.rend(); }
			const_reverse_iterator	rend() const { return tree.rend(); }

			bool					empty() const { return tree.empty(); }
			size_type				size() const { return tree.size(); }
			size_type				max_size() const { return tree.max_size(); }

			mapped_type&			operator[](const key_type& k) {}

			pair<iterator, bool>	insert(const value_type& val) { return tree.insert_unique(val); }

			iterator				insert(iterator position, const value_type& val) { return tree.insert_unique(position, val); }

			template <class InputIterator,
						typename = typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type>
			void					insert(InputIterator first, InputIterator last) { tree.insert_range_unique(first, last); }

		private:
			key_compare															_comp;
			allocator_type														_alloc;
			tree_type															tree;
	};
}

#endif
