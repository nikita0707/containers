#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <string>
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include <time.h>

class qwe
{
	public:
		qwe() {std::cout << "born\n";}
		~qwe() {std::cout << "die\n";}
		int i = 42;
};

void test()
{
	// int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

	// std::cout << std::is_integral<bool>::value << "\n";
	// std::cout << ft::is_integral<bool>::value << "\n";
	// std::vector<qwe>	vec(8);
	// qwe zxc;
	// // vec.reserve(10);
	// auto				begin = vec.begin();
	// auto				end = vec.end();
	// std::cout << "cap = " << vec.capacity() << "\n";
	// std::cout << "size = " << vec.size() << "\n";
	// while (begin != end)
	// {
	// 	std::cout << (*begin).i << " ";
	// 	// std::cout << *begin << " ";
	// 	++begin;
	// }
	// std::cout << "\n";
	// std::cout << (*(vec.erase(vec.begin() + 2))).i << "\n";
	// begin = vec.begin();
	// end = vec.end();
	// std::cout << "cap = " << vec.capacity() << "\n";
	// std::cout << "size = " << vec.size() << "\n";
	// while (begin != end)
	// {
	// 	std::cout << (*begin).i << " ";
	// 	// std::cout << *begin << " ";
	// 	++begin;
	// }
	// std::cout << "\n";

	ft::stack<int>	stack1;
	ft::stack<int>	stack2;
	std::cout << (stack1 < stack2);
}

int main()
{
	clock_t	startc, endc;
	startc = clock();
	for (size_t i = 0; i < 50; i++)
		test();
	endc = clock();
	printf("The above code block was executed in %.4f second(s)\n", ((double) endc - startc) / ((double) CLOCKS_PER_SEC));
}
