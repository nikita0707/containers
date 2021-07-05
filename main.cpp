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
#include "set.hpp"
#include <time.h>

#include "tester/tester.hpp"
#include "test/test.hpp"

class qwe
{
	public:
		qwe() {std::cout << "born\n";}
		~qwe() {std::cout << "die\n";}
		int i = 42;
};

void test()
{
	vector_test();
	stack_test();
	map_test();
	set_test();
	
	// test_vector();
	// std::cout << "\n";
	// test_stack();
	// std::cout << "\n";
	// test_map();
}

int main()
{
	clock_t	startc, endc;
	startc = clock();
	for (size_t i = 0; i < 1; i++)
		test();
	endc = clock();
	printf("The above code block was executed in %.4f second(s)\n", (((double) endc - startc) / ((double) CLOCKS_PER_SEC)));
}
