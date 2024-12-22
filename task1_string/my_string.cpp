/* деактивация предупреждений компилятора
т.к. функция std::strcpy() из библ. cstring помечена как устаревшая */
#define _CRT_SECURE_NO_WARNINGS

#include "my_string.h"
#include <cstring>
#include <exception>
#include <stdexcept>

String::String() : size_(0), capacity_(0), string_(nullptr) {}

String::String(const char* str) {
	if (str) { // если копируемся не от пустой строки
		size_ = std::strlen(str);
		capacity_ = size_;
		string_ = new char[size_];
		std::strcpy(string_, str);
	}
	else {
		size_ = capacity_ = 0;
		string_ = nullptr;
	}
}

String::String(const int& count, const char& ch) : size_(count), capacity_(count) {
	string_ = new char[count];
	for (size_t i = 0; i < count; ++i) {
		string_[i] = ch;
	}
}

String::String(String&& other) noexcept : string_(other.string_), size_(other.size_),
capacity_(other.capacity_) {
	other = String();
}

String& String::operator=(String&& other) noexcept {
	if (this != &other) {
		string_ = nullptr;
		delete string_; // предварит. освобождаем старую память
		string_ = other.string_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		other = String();
	}
	return *this;
}

String::~String() {
	size_ = capacity_ = 0;
	string_ = nullptr;
	delete string_;
}

int String::length() const {
	return (int) size_;
}

bool String::empty() const {
	return !size_;
}

const char* String::c_str() const {
	char* tmp = new char[size_ + 1]; // +1 для заверш. симв.
	for (size_t i = 0; i < size_; ++i) {
		tmp[i] = string_[i];
	}
	tmp[size_] = '\0';
	return tmp;
}

char& String::operator[](const size_t& index) {
	if (index >= size_) {
		throw std::out_of_range("index is outside the array");
	}
	return string_[index];
}

const char& String::operator[](const size_t& index) const {
	if (index >= size_) {
		throw std::out_of_range("index is outside the array");
	}
	return string_[index];
}

char& String::front() {
	if (!size_) {
		throw std::out_of_range("the string is empty");
	}
	return string_[0];
}

const char& String::front() const {
	if (!size_) {
		throw std::out_of_range("the string is empty");
	}
	return string_[0];
}

char& String::back() {
	if (!size_) {
		throw std::out_of_range("the string is empty");
	}
	return string_[size_ - 1];
}

const char& String::back() const {
	if (!size_) {
		throw std::out_of_range("the string is empty");
	}
	return string_[size_ - 1];
}

void String::reserve(const int& capacity) {
	if (capacity > capacity_) {
		char* tmp = new char[capacity];
		for (size_t i = 0; i < size_; ++i) {
			tmp[i] = string_[i];
		}
		string_ = nullptr;
		delete string_;
		string_ = tmp;
		capacity_ = capacity;
	}
}

void String::push_back(const char& ch) {
	if (size_ == capacity_) {
		reserve(capacity_ > 0 ? capacity_ * 2 : 1);
	}
	string_[size_] = ch;
	++size_;
}

void String::pop_back() {
	if (!size_) {
		throw "the string is empty";
	}
	--size_; // посл. симв. остался в памяти, но уже как мусор
}

void String::clear() {
	size_ = 0;
}

void String::insert(const int& index, const String& str) {
	if (index > size_) {
		throw std::out_of_range("index is outside the array");
	}
	for (size_t i = size_; i > index; --i) {
		string_[i + str.size_ - 1] = string_[i - 1]; // cдвиг вправо
	}
	try {
		for (size_t i = 0; i < str.size_; ++i) {
			string_[index + i] = str.string_[i];
		}
	}
	catch (const std::bad_alloc&) {
		reserve(size_ + str.size_);
		insert(index, str); // рекурсивный вызов
	}
	size_ = (index + str.size_) > size_ ? (index + str.size_) : size_;
}

void String::insert(const int& index, const char* str, const int& count) {
	if (index > size_) {
		throw std::out_of_range("index is outside the array");
	}
	for (size_t i = size_; i > index; --i) {
		string_[i + count - 1] = string_[i - 1];
	}
	try {
		for (size_t i = 0; i < count; ++i) {
			string_[index + i] = str[i];
		}
	}
	catch (const std::bad_alloc&) {
		reserve(size_ + count);
		insert(index, str, count);
	}
	size_ = (index + count) > size_ ? (index + count) : size_;
}

void String::erase(const int& index, int count = 1) {
	if (index >= size_) {
		throw std::out_of_range("index is outside the array");
	}
	count = std::min(count, length() - index);
	for (size_t i = index; i < size_ - count; ++i) {
		string_[i] = string_[i + count]; // cдвиг влево
	}
	size_ -= count;
}