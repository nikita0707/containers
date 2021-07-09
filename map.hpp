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
				protected:
					Compare	comp;
				public:
					value_compare(Compare c) : comp(c) {}
					bool	operator()(const value_type& x, const value_type& y) const
					{ return (comp(x.first, y.first)); }
			};
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
		private:
			typedef RBTree<key_type, value_type, ft::Select1st<value_type>, key_compare, allocator_type>	tree_type;
		public:
			typedef typename tree_type::iterator								iterator;
			typedef typename tree_type::const_iterator							const_iterator;
			typedef typename tree_type::reverse_iterator						reverse_iterator;
			typedef typename tree_type::const_reverse_iterator					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef size_t														size_type;

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _comp(comp), tree(comp, alloc) {}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: _comp(comp), tree(comp, alloc) { tree.insert_range_unique(first, last); }

			map(const map& x) : _comp(x._comp), tree(x.tree) {}

			~map() {}

			map& operator= (const map& x)
			{
				if (this != &x)
					tree = x.tree;
				return (*this);
			}

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

			mapped_type&			operator[](const key_type& k)
			{
				iterator	i = tree.lower_bound(k);
				
				if (i == tree.end() || _comp(k, (*i).first))
					i = tree.insert_unique(i, value_type(k, mapped_type()));
				return (*i).second;
			}

			mapped_type&			at(const key_type& key)
			{
				iterator	i = lower_bound(key);
				if (i == end() || _comp(key, (*i).first))
					throw std::out_of_range("map::at");
				return (*i).second;
			}
			const mapped_type&		at(const key_type& key) const
			{
				const_iterator	i = lower_bound(key);
				if (i == end() || _comp(key, (*i).first))
					throw std::out_of_range("map::at");
				return (*i).second;
			}

			pair<iterator, bool>	insert(const value_type& val) { return tree.insert_unique(val); }

			iterator				insert(iterator position, const value_type& val) { return tree.insert_unique(position, val); }

			template <class InputIterator>
			void					insert(InputIterator first, InputIterator last) { tree.insert_range_unique(first, last); }

			void					erase(iterator position) { tree.erase(position); }

			size_type				erase(const key_type& k) { return tree.erase(k); }

			void					erase(iterator first, iterator last) { tree.erase(first, last); }

			void					swap(map& x) { tree.swap(x.tree); }

			void					clear() { tree.clear(); }

			key_compare				key_comp() const { return _comp; }

			value_compare			value_comp() const { return value_compare(_comp); }

			iterator				find(const key_type& k) { return tree.find(k); }

			const_iterator			find(const key_type& k) const { return tree.find(k); }

			size_type				count(const key_type& k) const { return tree.find(k) == tree.end() ? 0 : 1; }

			iterator				lower_bound(const key_type& k) { return tree.lower_bound(k); }

			const_iterator			lower_bound(const key_type& k) const { return tree.lower_bound(k); }

			iterator				upper_bound(const key_type& k) { return tree.upper_bound(k); }

			const_iterator			upper_bound(const key_type& k) const { return tree.upper_bound(k); }

			pair<iterator,iterator>	equal_range(const key_type& k) { return tree.equal_range(k); }
			
			pair<const_iterator,const_iterator>	equal_range(const key_type& k) const { return tree.equal_range(k); }

			template <typename K1, typename T1, typename C1, typename A1>
			friend bool				operator==(const map<K1, T1, C1, A1>& lhs, const map<K1, T1, C1, A1>& rhs);

			template <typename K1, typename T1, typename C1, typename A1>
			friend bool				operator<(const map<K1, T1, C1, A1>& lhs, const map<K1, T1, C1, A1>& rhs);

		private:
			key_compare				_comp;
			tree_type				tree;
	};

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool						operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return lhs.tree == rhs.tree; }

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool						operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return lhs.tree < rhs.tree; }

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool						operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return !(lhs == rhs); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool						operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return rhs < lhs; }

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool						operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return !(rhs < lhs); }

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool						operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{ return !(lhs < rhs); }

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs )
	{ lhs.swap(rhs); }
}

#endif
