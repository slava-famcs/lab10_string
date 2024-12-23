#pragma once
#ifndef STRING_H_
#define STRING_H_

class String {
public:
	String();
	String(const char*); // конструктор от С строки
	String(const int&, const char&); // констр., иниц. объект стр. из count симв. ch
	String(const String&) = default; // конструктор копирования
	String(String&&) noexcept; // конструктор перемещения
	~String();
	String& operator=(const String&) = default; // оператор копирования
	String& operator=(String&&) noexcept; // оператор перемещения

	int length() const;
	bool empty() const;
	const char* c_str() const;

	char& operator[](const size_t&);
	const char& operator[](const size_t&) const;
	char& front();
	const char& front() const;
	char& back();
	const char& back() const;

	void reserve(const int&);
	void push_back(const char&);
	void pop_back();
	void clear();
	void insert(const int&, const String&);
	void insert(const int&, const char*, const int&);
	void erase(int, int);

private:
	size_t size_;
	size_t capacity_;
	char* string_;
};

#endif // STRING_H_