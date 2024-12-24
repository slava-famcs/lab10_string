#include "pch.h"
#include "../task1_string/my_string.cpp"

class StringTest : public ::testing::Test {
protected:
	String myString = String("MyString");
	String newString;
};

TEST_F(StringTest, lengthTest) {
	EXPECT_EQ(myString.length(), 8);
	EXPECT_EQ(newString.length(), 0);
}

TEST_F(StringTest, emptyTest) {
	EXPECT_FALSE(myString.empty());
	EXPECT_TRUE(newString.empty());
}

TEST_F(StringTest, c_strTest) {
	ASSERT_EQ(std::strlen(myString.c_str()), 8);
	EXPECT_STREQ(myString.c_str(), "MyString");
	EXPECT_EQ(*(myString.c_str() + 8), '\0');
}

TEST_F(StringTest, accessOperatorTest) {
	EXPECT_EQ(myString[0], 'M');
	EXPECT_EQ(myString[4], 'r');
	EXPECT_THROW(myString[8], std::out_of_range);
}

TEST_F(StringTest, frontTest) {
	EXPECT_EQ(myString.front(), 'M');
	EXPECT_THROW(newString.front(), std::out_of_range);
}

TEST_F(StringTest, backTest) {
	EXPECT_EQ(myString.back(), 'g');
	EXPECT_THROW(newString.back(), std::out_of_range);
}

TEST_F(StringTest, reserveTest) {
	myString.reserve(15);
	// проверить можно лишь не изм. ли размер и не изм. ли содержимое строки
	// т.к. у массивов нет методов, позволяющих узнать их вместимость
	ASSERT_EQ(myString.length(), 8);
	EXPECT_STREQ(myString.c_str(), "MyString");
	newString.reserve(5);
	ASSERT_EQ(newString.length(), 0);
	EXPECT_TRUE(newString.empty());

	// TODO сделать метод getCapacity() и через него сделать этот тест

}

TEST_F(StringTest, pushBackTest) {
	myString.push_back('!');
	ASSERT_EQ(myString.length(), 9);
	EXPECT_STREQ(myString.c_str(), "MyString!");
	newString.push_back('H');
	newString.push_back('i');
	ASSERT_EQ(newString.length(), 2);
	EXPECT_STREQ(newString.c_str(), "Hi");
}

TEST_F(StringTest, popBackTest) {
	myString.pop_back();
	ASSERT_EQ(myString.length(), 7);
	EXPECT_STREQ(myString.c_str(), "MyStrin");
	EXPECT_THROW(newString.pop_back(), std::out_of_range);
}

TEST_F(StringTest, clearTest) {
	EXPECT_FALSE(myString.empty());
	myString.clear();
	EXPECT_TRUE(myString.empty());
}

TEST_F(StringTest, insertTest) {
	myString.insert(8, String(" in C++"));
	ASSERT_EQ(myString.length(), 15);
	EXPECT_STREQ(myString.c_str(), "MyString in C++");
	myString.insert(8, String(" is"));
	ASSERT_EQ(myString.length(), 18);
	EXPECT_STREQ(myString.c_str(), "MyString is in C++");
	myString.insert(0, String("Hi "));
	ASSERT_EQ(myString.length(), 21);
	EXPECT_STREQ(myString.c_str(), "Hi MyString is in C++");
	EXPECT_THROW(myString.insert(52, String("Saint Petersburg")), std::out_of_range);

	newString.insert(0, String("Microsoft"));
	ASSERT_EQ(newString.length(), 9);
	EXPECT_STREQ(newString.c_str(), "Microsoft");
	newString.insert(5, String(" "));
	ASSERT_EQ(newString.length(), 10);
	EXPECT_STREQ(newString.c_str(), "Micro soft");
	newString.insert(10, String(" company"));
	ASSERT_EQ(newString.length(), 18);
	EXPECT_STREQ(newString.c_str(), "Micro soft company");
	EXPECT_THROW(newString.insert(42, String("something")), std::out_of_range);

	myString.insert(21, "Hello", 4);
	ASSERT_EQ(myString.length(), 25);
	EXPECT_STREQ(myString.c_str(), "Hi MyString is in C++Hell");
	myString.insert(2, " all ", 4);
	ASSERT_EQ(myString.length(), 29);
	EXPECT_STREQ(myString.c_str(), "Hi all MyString is in C++Hell");
	myString.insert(0, "Computer", 4);
	ASSERT_EQ(myString.length(), 33);
	EXPECT_STREQ(myString.c_str(), "CompHi all MyString is in C++Hell");

	newString.clear();
	newString.insert(0, "FAMCS-BSU", 5);
	ASSERT_EQ(newString.length(), 5);
	EXPECT_STREQ(newString.c_str(), "FAMCS");
}

TEST_F(StringTest, eraseTest) {
	EXPECT_THROW(newString.erase(0), std::out_of_range);
	EXPECT_THROW(myString.erase(100), std::out_of_range);
	myString.erase(8);
	ASSERT_EQ(myString.length(), 7);
	EXPECT_STREQ(myString.c_str(), "MyStrin");
	myString.erase(3, 3);
	ASSERT_EQ(myString.length(), 4);
	EXPECT_STREQ(myString.c_str(), "Myin");
	myString.erase(1, myString.length());
	EXPECT_TRUE(myString.empty());
}

TEST_F(StringTest, operatorPlusConcatenationTest) {
	String result = myString + newString;
	ASSERT_EQ(result.length(), 8);
	EXPECT_STREQ(result.c_str(), "MyString");
	newString.insert(0, "World");
	result = myString + newString;
	ASSERT_EQ(result.length(), 13);
	EXPECT_STREQ(result.c_str(), "MyStringWorld");
}

TEST_F(StringTest, operatorPlusEqualConcatenationTest) {
	myString += newString;
	ASSERT_EQ(myString.length(), 8);
	EXPECT_STREQ(myString.c_str(), "MyString");
	newString += myString;
	ASSERT_EQ(newString.length(), 8);
	EXPECT_STREQ(newString.c_str(), "MyString");
	myString += myString;
	ASSERT_EQ(myString.length(), 16);
	EXPECT_STREQ(myString.c_str(), "MyStringMyString");
}

TEST_F(StringTest, compareTest) {
	EXPECT_EQ(myString.compare(newString), 1);
	EXPECT_EQ(myString.compare(myString), 0);
	EXPECT_EQ(myString.compare(String("MyBigString")), -1);
	EXPECT_EQ(newString.compare(String()), 0);
	EXPECT_EQ(newString.compare(String("str")), -1);
	EXPECT_EQ(myString.compare(""), 1);
	EXPECT_EQ(myString.compare("MyString"), 0);
	EXPECT_EQ(myString.compare("MyBigString"), -1);
	EXPECT_EQ(newString.compare(""), 0);
	EXPECT_EQ(newString.compare("smth"), -1);
}

TEST_F(StringTest, relationalOperatorsTest) {
	EXPECT_TRUE(myString > newString);
	EXPECT_FALSE(newString > myString);
	EXPECT_TRUE(myString >= newString);
	EXPECT_FALSE(newString >= myString);
	EXPECT_TRUE(myString >= myString);
	EXPECT_FALSE(myString < newString);
	EXPECT_TRUE(newString < myString);
	EXPECT_FALSE(myString <= newString);
	EXPECT_TRUE(newString <= myString);
	EXPECT_TRUE(newString <= newString);
	EXPECT_TRUE(myString == myString);
	EXPECT_TRUE(newString == newString);
	EXPECT_FALSE(myString == newString);
	EXPECT_FALSE(myString != myString);
	EXPECT_FALSE(newString != newString);
	EXPECT_TRUE(myString != newString);

	EXPECT_TRUE(myString < "MyString123");
	EXPECT_TRUE(myString <= "MyString123");
	EXPECT_TRUE("MyString123" > myString);
	EXPECT_TRUE("MyString123" >= myString);
	EXPECT_FALSE(myString == "MyString123");
	EXPECT_TRUE(myString != "MyString123");
	EXPECT_TRUE("MyString" == myString);
	EXPECT_FALSE("MyString" != myString);
}