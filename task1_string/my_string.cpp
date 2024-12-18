#include "my_string.h"

void String::copyString(char* destination, const char* str) {
	if (getLength(destination) < getLength(str)) {
		throw "line sizes error";
	}
	int i;
	for (i = 0; i < getLength(str); ++i) {
		destination[i] = str[i];
	}
	destination[i + 1] = '\0';
}

size_t String::getLength(const char* str) {
	size_t length = 0;
	while (*str != '\0') {
		++length;
		++str;
	}
	return length;
}

String::String() {
	size_ = 0;
	string_ = new char[size_ + 1] {'\0'};
}

String::String(const char* str) {
	size_ = getLength(str);
	string_ = new char[size_ + 1];
	copyString(string_, str);
}

String::String(const int& count, const char& ch) {
	size_ = count;
	string_ = new char[count + 1];
	for (int i = 0; i < count; ++i) {
		string_[i] = ch;
	}
	string_[count] = '\0';
}

String::String(String&& other) : string_(other.string_), size_(other.size_) {
	other.string_ = nullptr;
	other.size_ = 0;
}

String::~String() {
	string_ = nullptr;
	delete[] string_;
}

int String::length() {
	return getLength(string_) - 1;
}

bool String::empty() const {
	return !size_;
}

char* String::c_str() const {
	return string_;
}

char& String::operator[](size_t index) {
	if (index > size_) {
		throw "non-existent index";
	}
	return string_[index];
}

const char& String::operator[](size_t index) const {
	if (index > size_) {
		throw "non-existent index";
	}
	return string_[index];
}

char& String::front() {
	if (!size_) {
		throw "the string is empty";
	}
	return string_[0];
}

const char& String::front() const {
	if (!size_) {
		throw "the string is empty";
	}
	return string_[0];
}

char& String::back() {
	if (!size_) {
		throw "the string is empty";
	}
	int i;
	for (i = 0; string_[i] != '\0'; ++i);
	return string_[i - 2];
}

const char& String::back() const {
	if (!size_) {
		throw "the string is empty";
	}
	int i;
	for (i = 0; string_[i] != '\0'; ++i);
	return string_[i - 2];
}

void String::reserve(int capacity) {
	if (capacity > size_) {
		char* newString = new char[capacity + 1];
		copyString(newString, string_);
		string_ = nullptr;
		delete[] string_;
		string_ = newString;
		size_ = capacity;
	}
}

void String::push_back(char ch) {
	if (getLength(string_) + 1 > size_) {
		reserve(size_ > 0 ? size_ * 2 : 1);
	}
	string_[getLength(string_) - 2] = ch;
	string_[getLength(string_)] = '\0';
}