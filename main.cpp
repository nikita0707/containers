#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <string>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include <time.h>

#include "tester/tester.hpp"

class qwe
{
	public:
		qwe() {std::cout << "born\n";}
		~qwe() {std::cout << "die\n";}
		int i = 42;
};

void test()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

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

	// ft::stack<int>	stack1;
	// ft::stack<int>	stack2;
	// std::cout << (stack1 < stack2);

	// std::map<char, int>	map;
	// std::set<char>	set;

	test_vector();
	std::cout << "\n";
	test_stack();
	std::cout << "\n";
	test_map();

	// ft::vector<ft::pair<int, int> >	vec;
	// vec.push_back(ft::make_pair(1, 1));
	// vec.push_back(ft::make_pair(2, 2));
	// vec.push_back(ft::make_pair(4, 4));
	// vec.push_back(ft::make_pair(3, 3));
	// vec.push_back(ft::make_pair(5, 5));
	// ft::map<int, int>	mymap;
	// ft::map<int, int>	mymap2;
	// mymap.insert(vec.begin(), vec.end());
	// mymap.insert(ft::make_pair(4, 4));
	// mymap2.insert(ft::make_pair(41, 41));
	// mymap2 = mymap;
	// mymap.insert(ft::make_pair(6, 6));
	// mymap.erase(2);
	// auto beg = mymap.begin();
	// auto end = mymap.end();
	// int i = 0;
	// while (beg != end)
	// {
	// 	std::cout << (*beg).second << "\n";
	// 	++beg;
	// 	if (i == 10)
	// 		break;
	// 	i++;
	// }
	// std::cout << "\n";
	// beg = mymap2.begin();
	// end = mymap2.end();
	// while (beg != end)
	// {
	// 	std::cout << (*beg).second << "\n";
	// 	++beg;
	// 	if (i == 10)
	// 		break;
	// 	i++;
	// }
}

int main()
{
	clock_t	startc, endc;
	startc = clock();
	for (size_t i = 0; i < 1; i++)
		test();
	endc = clock();
	printf("The above code block was executed in %.4f second(s)\n", ((double) endc - startc) / ((double) CLOCKS_PER_SEC));
}
