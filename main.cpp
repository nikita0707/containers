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
	// int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
	// std::vector<int> vec(arr, arr + 8);
	// auto it = vec.begin();
	// std::cout << it[2] << std::endl;
	// std::cout << *it << std::endl;
	// auto dif = 3 + it;
	// std::cout << *dif << std::endl;
	// std::cout << vec.max_size() << std::endl;
	// std::cout << vec.capacity() << std::endl;
	// vec.resize(0);
	// std::cout << vec.capacity() << std::endl;
	// std::cout << vec.empty() << std::endl;
	// try
	// {
	// 	vec.reserve(vec.max_size() + 1);
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	
	ft::vector<qwe> vec2(5);
	std::cout << "\n\n\n";
	vec2.reserve(7);
	std::cout << "\n\n\n";
	qwe zxc;
	std::cout << vec2.capacity() << std::endl;
	std::cout << vec2.size() << std::endl;
	vec2.insert(vec2.end() + 4, 5, zxc);
	std::cout << vec2.capacity() << std::endl;
	std::cout << vec2.size() << std::endl;
	std::cout << "\n\n\n";
	

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
