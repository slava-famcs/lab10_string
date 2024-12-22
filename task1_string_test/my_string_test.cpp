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
}

TEST_F(StringTest, clearTest) {
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
	newString.insert(0, String("Microsoft"));
	ASSERT_EQ(newString.length(), 9);
	EXPECT_STREQ(newString.c_str(), "Microsoft");

	// TODO insert не выделяет доп. память, когда вставляешь не в конец, а в середину
}