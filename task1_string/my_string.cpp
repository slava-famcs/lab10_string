#include "my_string.h"

void String::copyString(char* destination, const char* str) {
	if (size_ < getLength(str)) {
		throw "line sizes error";
	}
	int i;
	for (i = 0; *str != '\0'; ++i) {
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
	string_ = new char[count + 1];
	for (int i = 0; i < count; ++i) {
		string_[i] = ch;
	}
	string_[count] = '\0';
}

String::~String() {
	delete string_;
	string_ = nullptr;
}

int String::length() const {
	return size_;
}

bool String::empty() const {
	return size_;
}

const char* String::c_str() const {
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
	return string_[size_ - 1];
}

const char& String::back() const {
	if (!size_) {
		throw "the string is empty";
	}
	return string_[size_ - 1];
}

void String::reserve(int capacity) {
	char* newString = new char[capacity];
	copyString(newString, string_);
	delete string_;
	string_ = newString;
}