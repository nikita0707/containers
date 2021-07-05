#include <iostream>
#include <time.h>
#include <cstdlib>
#include "test/test.hpp"

void	test(char mask)
{
	if (mask & 0b1000)
	{
		vector_test();
		std::cout << "\n";
	}
	if (mask & 0b0100)
	{
		stack_test();
		std::cout << "\n";
	}
	if (mask & 0b0010)
	{
		map_test();
		std::cout << "\n";
	}
	if (mask & 0b0001)
		set_test();
}

void	toLower(char* str)
{
	for (int i = 0; str[i] != 0; ++i)
		str[i] = std::tolower(str[i]);
}

int		wrondArgs()
{
	std::string	suf;
	#ifdef STD
		suf = "std";
	#else
		suf = "ft";
	#endif
	std::cerr << "Usage: ./test_" << suf << " [number_of_repetitions] [container_names(optional)]\n";
	std::cerr << "number_of_repetitions: number of test repetitions. Required for greater accuracy in measuring the speed of containers.\n";
	std::cerr << "container_names: container names to test. Avaliable containers: Vector, Stack, Map, Set.\n";
	return 1;
}

int		main(int argc, char** argv)
{
	char	mask = 0b1111;
	int		count = 1;
	if (argc < 2 || argc > 6)
		return (wrondArgs());
	count = std::atoi(argv[1]);
	if (count < 1)
		return (wrondArgs());
	if (argc > 2)
	{
		mask = 0;
		for (int i = 2; i < argc; ++i)
		{
			toLower(argv[i]);
			std::string	s(argv[i]);
			if (s == "vector")
				mask = mask | 0b1000;
			else if (s == "stack")
				mask = mask | 0b0100;
			else if (s == "map")
				mask = mask | 0b0010;
			else if (s == "set")
				mask = mask | 0b0001;
			else
				return (wrondArgs());
		}
	}
	clock_t	startc, endc;
	startc = clock();
	for (int i = 0; i < count; i++)
		test(mask);
	endc = clock();
	printf("The above code block was executed in %.5f second(s)\n", (((double) endc - startc) / ((double) CLOCKS_PER_SEC)));
	return 0;
}
