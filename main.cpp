#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "Vector.hpp"

class qwe
{
	public:
		qwe() {std::cout << "born\n";}
		~qwe() {std::cout << "die\n";}
		int i = 42;
};

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

	std::cout << std::is_integral<bool>::value << "\n";
	std::cout << ft::is_integral<bool>::value << "\n";
	ft::vector<qwe>	vec(8);
	qwe zxc;
	// vec.reserve(10);
	auto				begin = vec.begin();
	auto				end = vec.end();
	std::cout << "cap = " << vec.capacity() << "\n";
	std::cout << "size = " << vec.size() << "\n";
	while (begin != end)
	{
		std::cout << (*begin).i << " ";
		// std::cout << *begin << " ";
		++begin;
	}
	std::cout << "\n";
	std::cout << (*(vec.erase(vec.begin() + 2))).i << "\n";
	begin = vec.begin();
	end = vec.end();
	std::cout << "cap = " << vec.capacity() << "\n";
	std::cout << "size = " << vec.size() << "\n";
	while (begin != end)
	{
		std::cout << (*begin).i << " ";
		// std::cout << *begin << " ";
		++begin;
	}
	std::cout << "\n";
}
