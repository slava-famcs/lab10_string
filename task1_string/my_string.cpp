/* деактивация предупреждений компилятора
т.к. функция std::strcpy() из библ. cstring помечена как устаревшая */
#define _CRT_SECURE_NO_WARNINGS

#include "my_string.h"
#include <cstring>
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
		other.string_ = nullptr;
		delete other.string_;
		other.size_ = other.capacity_ = 0;
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
		throw std::out_of_range("the string is empty");
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

	if (capacity_ < size_ + str.size_) {
		reserve(size_ + str.size_);
	}
	for (size_t i = size_; i > index; --i) {
		string_[i + str.size_ - 1] = string_[i - 1]; // cдвиг вправо
	}

	for (size_t i = 0; i < str.size_; ++i) {
		string_[index + i] = str.string_[i]; // копируем элементы по индексу
	}
	size_ += str.size_;
}

void String::insert(const int& index, const char* str, const int& count) {
	if (index > size_) {
		throw std::out_of_range("index is outside the array");
	}

	if (capacity_ < size_ + count) {
		reserve(size_ + count);
	}
	for (size_t i = size_; i > index; --i) {
		string_[i + count - 1] = string_[i - 1];
	}

	for (size_t i = 0; i < count; ++i) {
		string_[index + i] = str[i];
	}
	size_ += count;
}

void String::erase(int index, int count = 1) {
	--index;
	if (index >= size_) {
		throw std::out_of_range("index is outside the array");
	}
	count = std::min(count, length() - index);
	for (size_t i = index; i < size_ - count; ++i) {
		string_[i] = string_[i + count]; // cдвиг влево
	}
	size_ -= count;
}

String operator+(const String& lvalue, const String& rvalue) {
	String sum;
	sum.reserve(lvalue.size_ + rvalue.size_);
	for (size_t i = 0; i < lvalue.size_; ++i) {
		sum.push_back(lvalue.string_[i]);
	}
	for (size_t i = 0; i < rvalue.size_; ++i) {
		sum.push_back(rvalue.string_[i]);
	}
	return sum;
}

String& String::operator+=(const String other) {
	reserve(size_ + other.size_);
	for (size_t i = 0; i < other.size_; ++i) {
		push_back(other.string_[i]);
	}
	return *this;
}

int String::compare(const String& other) const {
	
}