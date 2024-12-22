#include "my_string.h"
#include <utility>
#include <iostream>

int main() {
	String str = String("MyString");

	std::cout << str.length() << '\n';

	std::cout << str.empty() << '\n';

	str.push_back('!');
	str.push_back('!');


	for (size_t i = 0; i < str.length(); ++i) {
		std::cout << *(str.c_str() + i);
	}
	std::cout << '\n';

	return 0;
}