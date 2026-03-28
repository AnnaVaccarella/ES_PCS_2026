#include<iostream>
#include"rational.hpp"

int main(void)
{
	rational<int> a(6,4);
	rational<int> b(3,6);
	
	rational<int> c = a+b;
	rational<int> d = a-b;
	rational<int> e = a*b;
	rational<int> f = a/b;
	
	std::cout << a << "\n";
	std::cout<< b << "\n";
	std::cout << c << "\n";
	std::cout << d << "\n";
	std::cout << e << "\n";
	std::cout << f << "\n";
	
	return 0;
}