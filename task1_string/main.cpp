#include "my_string.h"
#include <iostream>

void print(String&);

int main() {
	String str = String("MyString");

	std::cout << str.length() << '\n';

	std::cout << str.empty() << '\n';

	str.push_back('!');
	str.push_back('!');
	print(str);

	str.pop_back();
	print(str);

	String newStr = str;
	newStr.clear();
	std::cout << newStr.empty() << '\n';

	str.insert(9, String(" in C++"));
	print(str);
	str.insert(5, " bread");
	print(str);
	str.insert(22, " Hello", 5);
	print(str);
	str.insert(6, "Bobby", 3);
	print(str);

	str.erase(6, 10);
	print(str);

	return 0;
}

void print(String& str) {
	for (size_t i = 0; i < str.length(); ++i) {
		std::cout << *(str.c_str() + i);
	}
	std::cout << '\n';
}