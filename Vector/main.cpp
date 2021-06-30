#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "../iterator_traits.hpp"
#include "../iterator.hpp"

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
	std::vector<int> vec(arr, arr + 8);
	auto it = vec.begin();
	std::vector<int>::iterator it2;
	std::cout << it[2] << std::endl;
	std::cout << *it << std::endl;
	auto dif = 3 + it;
	std::cout << *dif << std::endl;


	// int arr[] = {1, 2, 3, 4};
	// std::vector<int> vec(arr, arr+4);
	// // ft::Vector<int> vec(arr, arr+4);
	// vec.push_back(3);
	// auto it = vec.begin();
	// std::cout << "cap = " << vec.capacity() << std::endl;
	// std::cout << *it << std::endl;
	// it++;
	// std::cout << *it << std::endl;
	// it++;
	// std::cout << *it << std::endl;
	// it++;
	// std::cout << *it << std::endl;
	// it++;
	// std::cout << *it << std::endl;
	// it++;
	// std::cout << *it << std::endl;
	// it++;
	// std::cout << *it << std::endl;
	// it++;
	// std::cout << *it << std::endl;
	// it++;
	// std::cout << *it << std::endl;
	// it++;
}
