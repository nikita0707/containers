#ifndef RBNODE_HPP
# define RBNODE_HPP

namespace ft
{
	enum NodeColor
	{
		red,
		black,
	};

	template <typename Val>
	struct RBNode
	{
		bool					color;
		RBNode					*parent;
		RBNode					*left;
		RBNode					*right;
		Val						value;
	};

}

#endif
