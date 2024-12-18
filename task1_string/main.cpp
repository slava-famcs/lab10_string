#include "my_string.h"
#include <utility>
#include <iostream>

int main() {
	String str("string");
	String str2(5, 'a');
	String str3(str);
	String str4(str);
	String str5(std::move(str4));
	String str6 = str5;
	String str7 = std::move(str6);

	std::cout << str.length() << '\n';
	std::cout << str.empty() << '\n';
	std::cout << str4.empty() << '\n';
	std::cout << str.c_str() << '\n';
	std::cout << str[2] << '\n';
	const String str52(str);
	std::cout << str52[2] << '\n';
	std::cout << str.front() << '\n';
	std::cout << str52.front() << '\n';
	std::cout << str.back() << '\n';
	std::cout << str52.back() << '\n';
	str.push_back('s');
	std::cout << str.back() << '\n';

	return 0;
}