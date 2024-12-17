﻿#pragma once
#ifndef STRING_H_
#define STRING_H_

class String {
public:
	String(); // конструктор по умолчанию
	String(const char*); // конструктор от С строки
	String(const int&, const char&); // констр., иниц. объект стр. из count симв. ch
	String(const String&) = default; // конструктор копирования
	String(String&&) = default; // конструктор перемещения
	~String(); // деструктор
	String& operator=(const String&) = default; // оператор копирования
	String& operator=(String&&) = default; // оператор перемещения

private:
	size_t size_;
	char* string_;
};

#endif // STRING_H_