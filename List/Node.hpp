#ifndef NODE_HPP
# define NODE_HPP

namespace ft
{
	template <typename T>
	struct			Node
	{
		T			data;
		struct Node	*prev;
		struct Node	*next;
	};
}

#endif
