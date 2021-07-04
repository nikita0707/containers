#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include "utils.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T															key_type;
			typedef T															value_type;
			typedef Compare														key_compare;
			typedef Compare														value_compare;
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
		private:
			typedef RBTree<key_type, value_type, ft::Idenity<value_type>, key_compare, allocator_type>	tree_type;
		public:
			typedef typename tree_type::iterator								iterator;
			typedef typename tree_type::const_iterator							const_iterator;
			typedef typename tree_type::reverse_iterator						reverse_iterator;
			typedef typename tree_type::const_reverse_iterator					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef size_t														size_type;

			explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _comp(comp), tree(comp, alloc) {}

			template <class InputIterator,
						typename = typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type>
			set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
			: _comp(comp), tree(comp, alloc) { tree.insert_range_unique(first, last); }

			set(const set& x) : _comp(x._comp), tree(x.tree) {}

			~set() {}

			set& operator= (const set& x)
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

			pair<iterator, bool>	insert(const value_type& val) { return tree.insert_unique(val); }

			iterator				insert(iterator position, const value_type& val) { return tree.insert_unique(position, val); }

			template <class InputIterator,
						typename = typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type>
			void					insert(InputIterator first, InputIterator last) { tree.insert_range_unique(first, last); }

			void					erase(iterator position) { tree.erase(position); }

			size_type				erase(const key_type& k) { return tree.erase(k); }

			void					erase(iterator first, iterator last) { tree.erase(first, last); }

			void					swap(set& x) { tree.swap(x.tree); }

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

		private:
			key_compare				_comp;
			tree_type				tree;
	};
}

#endif
