#include <iostream>
#ifdef STD
namespace ft = std;
# include <stack>
#else
# include "../stack.hpp"
#endif

template <typename T>
void	printAttr(ft::stack<T>& st)
{
	std::cout << "      Empty\t:  " << ((st.empty()) ? "true\n" : "false\n");
	std::cout << "      Size\t:  " << st.size() << "\n";
	std::cout << "      Content\t:  [";
	while (st.size() != 0)
	{
		std::cout << st.top();
		st.pop();
		if (st.size() != 0)
			std::cout << ", ";
	}
	std::cout << "]\n";
}

void	stack_test()
{
	std::cout << "STACK:\n";

	std::cout << "  Member functions:\n";

	{
		std::cout << "    Constructor:\n";
		ft::stack<int>	st;
		printAttr(st);
	}

	std::cout << "\n";

	{
		std::cout << "    Empty (true):\n";
		ft::stack<int>	st;
		printAttr(st);
	}

	std::cout << "\n";

	{
		std::cout << "    Empty (false):\n";
		ft::stack<int>	st;
		int				arr[] = { 359, 65, 92, 15, 14, 3 };
		for (size_t i = 0; i < 6; i++)
			st.push(arr[i]);
		printAttr(st);
	}

	std::cout << "\n";

	{
		std::cout << "    Size:\n";
		ft::stack<int>	st;
		int				arr[] = { 359, 65, 92, 15, 14, 3 };
		for (size_t i = 0; i < 6; i++)
			st.push(arr[i]);
		printAttr(st);
	}

	std::cout << "\n";

	{
		std::cout << "    Top:\n";
		ft::stack<int>	st;
		int				arr[] = { 359, 65, 92, 15, 14, 3 };
		for (size_t i = 0; i < 6; i++)
			st.push(arr[i]);
		std::cout << "      Content\t:  [" << st.top() << "]\n";
	}

	std::cout << "\n";

	{
		std::cout << "    Push:\n";
		ft::stack<int>	st;
		int				arr[] = { 359, 65, 92, 15, 14, 3 };
		for (size_t i = 0; i < 6; i++)
			st.push(arr[i]);
		printAttr(st);
	}

	std::cout << "\n";

	{
		std::cout << "    Pop:\n";
		ft::stack<int>	st;
		int				arr[] = { 359, 65, 92, 15, 14, 3 };
		for (size_t i = 0; i < 6; i++)
			st.push(arr[i]);
		st.pop();
		printAttr(st);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator == (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> st(arr1, arr1 + 6);
		std::cout << "      s == s\t:  " << (st == st ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator == (false):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> st1(arr1, arr1 + 6);
		ft::vector<int> st2(arr2, arr2 + 6);
		std::cout << "      s1 == s2\t:  " << (st1 == st2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator != (false):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> st(arr1, arr1 + 6);
		std::cout << "      s != s\t:  " << (st != st ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator != (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> st1(arr1, arr1 + 6);
		ft::vector<int> st2(arr2, arr2 + 6);
		std::cout << "      s1 != s2\t:  " << (st1 != st2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator < (false):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> st(arr1, arr1 + 6);
		std::cout << "      s < s\t:  " << (st < st ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator < (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> st1(arr1, arr1 + 6);
		ft::vector<int> st2(arr2, arr2 + 6);
		std::cout << "      s1 < s2\t:  " << (st1 < st2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator <= (false):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> st1(arr1, arr1 + 6);
		ft::vector<int> st2(arr2, arr2 + 6);
		std::cout << "      s2 <= s1\t:  " << (st2 <= st1 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator <= (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> st1(arr1, arr1 + 6);
		ft::vector<int> st2(arr2, arr2 + 6);
		std::cout << "      s1 <= s2\t:  " << (st1 <= st2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator > (false):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> st(arr1, arr1 + 6);
		std::cout << "      s > s\t:  " << (st > st ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator > (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> st1(arr1, arr1 + 6);
		ft::vector<int> st2(arr2, arr2 + 6);
		std::cout << "      s2 > s1\t:  " << (st2 > st1 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator >= (false):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> st1(arr1, arr1 + 6);
		ft::vector<int> st2(arr2, arr2 + 6);
		std::cout << "      s1 >= s2\t:  " << (st1 >= st2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator >= (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> st1(arr1, arr1 + 6);
		ft::vector<int> st2(arr2, arr2 + 6);
		std::cout << "      s2 >= s1\t:  " << (st2 >= st1 ? "true\n" : "false\n");
	}
}
