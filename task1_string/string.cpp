#include "String.h"
#include <cstring> // for strlen(), strcpy()

String::String() {
	size_ = 0;
	string_ = new char[size_] {'\0'};
}

String::String(const char* str) {
	size_ = std::strlen(str);
	string_ = new char[size_ + 1];
	std::strcpy(string_, str); // char* strcpy(char* destination, const char* source);
}

String::String(const int& count, const char& ch) {
	string_ = new char[count];
	for (int i = 0; i < count; ++i) {
		string_[i] = ch;
	}
}

String::~String() {
	delete string_;
	string_ = nullptr;
}