#pragma once
#ifndef STRING_H_
#define STRING_H_

class String {
public:
	String(); // конструктор по умолчанию
	String(const char*); // конструктор от С строки
	String(const int&, const char&); // констр., иниц. объект стр. из count симв. ch
	String(const String&) = default; // конструктор копирования
	String(String&&); // конструктор перемещения
	~String(); // деструктор
	String& operator=(const String&) = default; // оператор копирования
	String& operator=(String&&) = default; // оператор перемещения

	int length();
	bool empty() const;
	char* c_str() const;
	char& operator[](size_t);
	const char& operator[](size_t) const;
	char& front();
	const char& front() const;
	char& back();
	const char& back() const;
	void reserve(int);
	void push_back(char);

private:
	size_t size_;
	char* string_;

	void copyString(char*, const char*);
	size_t getLength(const char*);
};

#endif // STRING_H_