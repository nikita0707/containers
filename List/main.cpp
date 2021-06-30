#include "List.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <string>

int main()
{
	int arr[] = {1, 2, 3, 4};
	std::vector<int> vec(arr, arr+4);
	// ft::Vector<int> vec(arr, arr+4);
	vec.push_back(3);
	auto it = vec.begin();
	std::cout << "cap = " << vec.capacity() << std::endl;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	it++;
	std::cout << *it << std::endl;
	it++;
}
