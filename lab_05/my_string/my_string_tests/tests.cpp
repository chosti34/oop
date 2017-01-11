#include "stdafx.h"
#include "../MyString.h"

// ѕровер€ет содержимое строки и еЄ длину на равенство с ожидаемыми значени€ми
void VerifyString(const CMyString &str, const char *expectedData, const std::size_t expectedLength)
{
    BOOST_CHECK_EQUAL(str.GetStringData(), expectedData);
    BOOST_CHECK_EQUAL(str.GetLength(), expectedLength);
}

BOOST_AUTO_TEST_SUITE(MyString)
    BOOST_AUTO_TEST_CASE(is_empty_by_default)
    {
        CMyString string;
        VerifyString(string, "", 0);
    }

    BOOST_AUTO_TEST_SUITE(contructor_of_initialization_can_work_correctly_with)
        BOOST_AUTO_TEST_CASE(const_char)
        {
            {
                CMyString string("hello");
                VerifyString(string, "hello", strlen("hello"));
            }

            {
                CMyString string("hello", 2);
                VerifyString(string, "he", strlen("he"));
            }

            {
                const char *str = "world";
                CMyString copy(str);
                VerifyString(copy, str, strlen(str));
            }
        }

        BOOST_AUTO_TEST_CASE(null_pointer)
        {
            CMyString string(nullptr);
            VerifyString(string, "", 0);
        }

        BOOST_AUTO_TEST_CASE(stl_string)
        {
            // non-empty
            {
                std::string str("abcd");
                CMyString copy(str);
                VerifyString(copy, str.c_str(), str.length());
            }

            // empty
            {
                std::string str;
                CMyString copy = str;
                VerifyString(copy, str.c_str(), str.length());
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(can_be_copied_correctly)
        BOOST_AUTO_TEST_CASE(by_copy_constructor)
        {
            // non empty
            {
                CMyString str = "some non empty string";
                CMyString copy(str);
                BOOST_CHECK_EQUAL(str.GetStringData(), copy.GetStringData());
                BOOST_CHECK_EQUAL(str.GetLength(), copy.GetLength());
            }

            // empty
            {
                CMyString str;
                VerifyString(str, "", 0);
                CMyString copy(str);
                VerifyString(copy, str.GetStringData(), str.GetLength());
            }
        }

        BOOST_AUTO_TEST_CASE(by_assignment_operator)
        {
            // non empty
            {
                CMyString str = "Hello, World!";
                CMyString copy;
                copy = str;
                VerifyString(copy, str.GetStringData(), str.GetLength());
            }

            // empty
            {
                CMyString str = "";
                VerifyString(str, "", 0);
                CMyString copy;
                copy = str;
                VerifyString(copy, str.GetStringData(), str.GetLength());
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(can_be_moved_correctly)
        BOOST_AUTO_TEST_CASE(by_move_constructor)
        {
            // non empty
            {
                CMyString donor = "hello";
                CMyString copy(donor);
                CMyString acceptor = std::move(donor);
                VerifyString(donor, "", 0);
                VerifyString(acceptor, copy.GetStringData(), copy.GetLength());
            }

            // empty
            {
                CMyString donor;
                CMyString copy(donor);
                CMyString acceptor = std::move(donor);
                VerifyString(donor, "", 0);
                VerifyString(acceptor, copy.GetStringData(), copy.GetLength());
            }
        }

        BOOST_AUTO_TEST_CASE(by_assignment_operator)
        {
            // non empty
            {
                CMyString donor = "some str";
                CMyString copy;
                copy = donor;
                CMyString acceptor;
                acceptor = std::move(donor);
                VerifyString(donor, "", 0);
                VerifyString(acceptor, copy.GetStringData(), copy.GetLength());
            }

            // empty
            {
                CMyString donor;
                CMyString copy;
                copy = donor;
                CMyString acceptor;
                acceptor = std::move(donor);
                VerifyString(donor, "", 0);
                VerifyString(acceptor, copy.GetStringData(), copy.GetLength());
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_CASE(can_be_assigned_to_itself_correctly)
    {
        // copy assignment operator
        {
            CMyString str1("hello");
            CMyString str2("world");

            str1 = str2;
            str2 = str1;

            str1 = str1;
            str2 = str2;

            VerifyString(str1, str2.GetStringData(), str2.GetLength());
        }

        // move assignment operator
        {
            CMyString str1("hello");
            CMyString str2("world");

            str1 = std::move(str2);
            str2 = std::move(str1);

            str1 = std::move(str1);
            str2 = std::move(str2);

            VerifyString(str1, "", 0);
            VerifyString(str2, "world", 5);
        }
    }

    BOOST_AUTO_TEST_CASE(can_be_cleared_correctly)
    {
        // non empty
        {
            CMyString string("data");
            VerifyString(string, "data", strlen("data"));
            string.Clear();
            VerifyString(string, "", 0);
        }

        // empty
        {
            CMyString str;
            VerifyString(str, "", 0);
            str.Clear();
            VerifyString(str, "", 0);
        }
    }

    BOOST_AUTO_TEST_SUITE(SubString_method)
        BOOST_AUTO_TEST_CASE(returns_correct_substring_of_some_non_empty_str)
        {
            // non-empty
            {
                CMyString str("some string");
                CMyString subStr = str.SubString(5, 6);
                VerifyString(subStr, "string", 6);
            }

            // empty
            {
                CMyString str;
                CMyString subStr = str.SubString(1, 3);
                VerifyString(subStr, "", 0);
            }
        }

        BOOST_AUTO_TEST_CASE(returns_same_string_when_length_parametr_is_incorrect)
        {
            // negative
            {
                CMyString str("some string here");
                CMyString subStr = str.SubString(0, -3);
                VerifyString(subStr, str.GetStringData(), str.GetLength());
            }

            // positive
            {
                CMyString str("some string here");
                CMyString subStr = str.SubString(0, 1000);
                VerifyString(subStr, str.GetStringData(), str.GetLength());
            }
        }

        BOOST_AUTO_TEST_CASE(returns_empty_str_when_start_position_is_incorrect)
        {
            // start position is out of range (positive)
            {
                CMyString str("Hello, World!");
                CMyString subStr = str.SubString(str.GetLength(), 1);
                VerifyString(subStr, "", 0);
            }

            // negative
            {
                CMyString str = "non empty string";
                CMyString subStr = str.SubString(-3, 0);
                VerifyString(subStr, "", 0);
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(binary_plus_operator_of_concatenation_can_work_correctly_with)
        BOOST_AUTO_TEST_CASE(CMyString_and_CMyString)
        {
            CMyString str1 = "Hello ";
            CMyString str2 = "world";
            CMyString result = str1 + str2;
            VerifyString(result, "Hello world", str1.GetLength() + str2.GetLength());
            result = str2 + str1;
            VerifyString(result, "worldHello ", str1.GetLength() + str2.GetLength());

            // with itself
            result = result + result;
            VerifyString(result, "worldHello worldHello ", 2 * (str1.GetLength() + str2.GetLength()));
        }

        BOOST_AUTO_TEST_CASE(CMyString_and_stl_string)
        {
            CMyString str1 = "hello";
            std::string str2 = "goodbye";
            CMyString result = str1 + str2;
            VerifyString(result, "hellogoodbye", str1.GetLength() + str2.length());
            result = str2 + str1;
            VerifyString(result, "goodbyehello", str1.GetLength() + str2.length());
        }

        BOOST_AUTO_TEST_CASE(CMyString_and_const_char)
        {
            CMyString str1 = "one";
            const char *str2 = "two";
            CMyString result = str1 + str2;
            VerifyString(result, "onetwo", str1.GetLength() + strlen(str2));
            result = str2 + str1;
            VerifyString(result, "twoone", str1.GetLength() + strlen(str2));
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(appending_by_plus_assign_operator_can_work_correctly_with)
        BOOST_AUTO_TEST_CASE(MyString)
        {
            // non empty
            {
                CMyString str = "Hello";
                str += CMyString("!");
                VerifyString(str, "Hello!", 6);
            }

            // itself
            {
                CMyString str = "Hello";
                std::size_t oldLength = str.GetLength();
                str += str;
                VerifyString(str, "HelloHello", 2 * oldLength);
            }

            // empty
            {
                CMyString str = "";
                str += CMyString();
                VerifyString(str, "", 0);
            }
        }

        BOOST_AUTO_TEST_CASE(stl_string)
        {
            // non empty
            {
                CMyString str("abcd");
                str += std::string("efg");
                VerifyString(str, "abcdefg", 7);
            }

            // empty
            {
                CMyString str("");
                str += std::string("abcd");
                VerifyString(str, "abcd", 4);
            }
        }

        BOOST_AUTO_TEST_CASE(const_char)
        {
            // non empty
            {
                CMyString str("non empty str");
                str += " abc";
                VerifyString(str, "non empty str abc", 17);
            }

            // empty
            {
                CMyString str = "";
                str += "";
                VerifyString(str, "", 0);
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(equality_operator_works_correctly_with)
        BOOST_AUTO_TEST_CASE(CMyString_and_CMyString)
        {
            CMyString str1;
            CMyString str2;
            BOOST_CHECK(str1 == str2);
            str1 = "string";
            str2 = str1;
            BOOST_CHECK(str1 == str2);
            str1 = "";
            BOOST_CHECK(!(str1 == str2));
        }

        BOOST_AUTO_TEST_CASE(CMyString_and_const_char)
        {
            CMyString str;
            BOOST_CHECK(str == "");
            str = "x";
            BOOST_CHECK(str == "x");
            BOOST_CHECK(!(str == ""));
        }

        BOOST_AUTO_TEST_CASE(CMyString_and_stl_string)
        {
            CMyString str1;
            std::string str2;
            BOOST_CHECK(str1 == str2);
            str2 = "abcd";
            str1 = str2;
            BOOST_CHECK(str1 == str2);
            str2 = "";
            BOOST_CHECK(!(str1 == str2));
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(inequality_operator_works_correctly_with)
        BOOST_AUTO_TEST_CASE(CMyString_and_CMyString)
        {
            CMyString str1 = "1";
            CMyString str2;
            BOOST_CHECK(str1 != str2);
            str2 = "1";
            BOOST_CHECK(!(str1 != str2));
        }

        BOOST_AUTO_TEST_CASE(CMyString_and_const_char)
        {
            CMyString str;
            BOOST_CHECK(str != "abcd");
            BOOST_CHECK(!(str != ""));
        }

        BOOST_AUTO_TEST_CASE(CMyString_and_stl_string)
        {
            CMyString str1;
            std::string str2("str");
            BOOST_CHECK(str1 != str2);
            str2 = "";
            BOOST_CHECK(!(str1 != str2));
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(can_be_less_than)
        BOOST_AUTO_TEST_CASE(MyString)
        {
            // non empty
            {
                CMyString str1("abcd");
                CMyString str2("xyz");
                BOOST_CHECK(str1 < str2);
                str2 = "ab";
                BOOST_CHECK(!(str1 < str2));
            }

            // empty
            {
                CMyString str1 = "";
                CMyString str2 = "abcd";
                BOOST_CHECK(str1 < str2);
                str2 = "";
                BOOST_CHECK(!(str1 < str2));
            }
        }

        BOOST_AUTO_TEST_CASE(stl_string)
        {
            // non empty
            {
                CMyString str1("abcd");
                std::string str2("xyz");
                BOOST_CHECK(str1 < str2);
                str1 = "xyzw";
                BOOST_CHECK(!(str1 < str2));
            }

            // empty
            {
                CMyString str1 = "";
                std::string str2 = "abcd";
                BOOST_CHECK(str1 < str2);
                str1 = "abcde";
                BOOST_CHECK(!(str1 < str2));
            }
        }

        BOOST_AUTO_TEST_CASE(const_char)
        {
            // non empty
            {
                CMyString str1("abcd");
                const char *str2("xyz");
                BOOST_CHECK(str1 < str2);
                str2 = "abcd";
                BOOST_CHECK(!(str1 < str2));
            }

            // empty
            {
                CMyString str1 = "";
                const char *str2 = "abcd";
                BOOST_CHECK(str1 < str2);
                str2 = "";
                BOOST_CHECK(!(str1 < str2));
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(can_be_greater_than)
        BOOST_AUTO_TEST_CASE(MyString)
        {
            // non empty
            {
                CMyString str1("string");
                CMyString str2("String");
                BOOST_CHECK(str1 > str2);
                str1 = "String";
                BOOST_CHECK(!(str1 > str2));
            }

            // empty
            {
                CMyString str1 = "abcd";
                CMyString str2 = "";
                BOOST_CHECK(str1 > str2);
                str1 = "";
                BOOST_CHECK(!(str1 > str2));
            }
        }

        BOOST_AUTO_TEST_CASE(stl_string)
        {
            // non empty
            {
                CMyString str1("string");
                std::string str2("String");
                BOOST_CHECK(str1 > str2);
                str2 = "string";
                BOOST_CHECK(!(str1 > str2));
            }

            // empty
            {
                CMyString str1 = "abcd";
                std::string str2 = "";
                BOOST_CHECK(str1 > str2);
                str2 = "abcd";
                BOOST_CHECK(!(str1 > str2));
            }
        }

        BOOST_AUTO_TEST_CASE(const_char)
        {
            // non empty
            {
                CMyString str1("string");
                const char *str2("String");
                BOOST_CHECK(str1 > str2);
                str2 = "string";
                BOOST_CHECK(!(str1 > str2));
            }

            // empty
            {
                CMyString str1 = "abcd";
                const char *str2 = "";
                BOOST_CHECK(str1 > str2);
                str2 = "abcd";
                BOOST_CHECK(!(str1 > str2));
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(can_be_less_than_or_equal_to)
        BOOST_AUTO_TEST_CASE(MyString)
        {
            // non empty
            {
                CMyString str1("String");
                CMyString str2("string");
                BOOST_CHECK(str1 <= str2);
                str1 = str2;
                BOOST_CHECK(str1 <= str2);
                str1 = "string";
                str2 = "String";
                BOOST_CHECK(!(str1 <= str2));
            }

            // empty
            {
                CMyString str1 = "";
                CMyString str2 = "";
                BOOST_CHECK(str1 <= str2);
                str2 = "str2";
                BOOST_CHECK(str1 <= str2);
                str1 = "str2x";
                BOOST_CHECK(!(str1 <= str2));
            }
        }

        BOOST_AUTO_TEST_CASE(stl_string)
        {
            // non empty
            {
                CMyString str1("String");
                std::string str2("string");
                BOOST_CHECK(str1 <= str2);
                str1 = str2;
                BOOST_CHECK(str1 <= str2);
                str1 = "string";
                str2 = "String";
                BOOST_CHECK(!(str1 <= str2));
            }

            // empty
            {
                CMyString str1 = "";
                std::string str2 = "";
                BOOST_CHECK(str1 <= str2);
                str2 = "str2";
                BOOST_CHECK(str1 <= str2);
                str1 = "str2x";
                BOOST_CHECK(!(str1 <= str2));
            }
        }

        BOOST_AUTO_TEST_CASE(const_char)
        {
            // non empty
            {
                CMyString str1("String");
                const char *str2("string");
                BOOST_CHECK(str1 <= str2);
                str1 = str2;
                BOOST_CHECK(str1 <= str2);
                str1 = "string";
                str2 = "String";
                BOOST_CHECK(!(str1 <= str2));
            }

            // empty
            {
                CMyString str1 = "";
                const char *str2 = "";
                BOOST_CHECK(str1 <= str2);
                str2 = "str2";
                BOOST_CHECK(str1 <= str2);
                str1 = "str2x";
                BOOST_CHECK(!(str1 <= str2));
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(can_be_greater_than_or_equal_to)
        BOOST_AUTO_TEST_CASE(MyString)
        {
            // non empty
            {
                CMyString str1("string");
                CMyString str2("string");
                BOOST_CHECK(str1 >= str2);
                str2 = "String";
                BOOST_CHECK(str1 >= str2);
                str1 = "";
                BOOST_CHECK(!(str1 >= str2));
            }

            // empty
            {
                CMyString str1 = "abcd";
                CMyString str2 = "";
                BOOST_CHECK(str1 >= str2);
                str1 = "";
                BOOST_CHECK(str1 >= str2);
                str2 = "str";
                BOOST_CHECK(!(str1 >= str2));
            }
        }

        BOOST_AUTO_TEST_CASE(stl_string)
        {
            // non empty
            {
                CMyString str1("string");
                std::string str2("String");
                BOOST_CHECK(str1 >= str2);
                str1 = "str";
                BOOST_CHECK(str1 >= str2);
                str2 = "str1";
                BOOST_CHECK(!(str1 >= str2));
            }

            // empty
            {
                CMyString str1 = "abcd";
                std::string str2 = "";
                BOOST_CHECK(str1 >= str2);
                str1 = "";
                BOOST_CHECK(str1 >= str2);
                str2 = "str";
                BOOST_CHECK(!(str1 >= str2));
            }
        }

        BOOST_AUTO_TEST_CASE(const_char)
        {
            // non empty
            {
                CMyString str1("string");
                const char *str2("String");
                BOOST_CHECK(str1 >= str2);
                str2 = "string";
                BOOST_CHECK(str1 >= str2);
                str1 = "";
                BOOST_CHECK(!(str1 >= str2));
            }

            // empty
            {
                CMyString str1 = "abcd";
                const char *str2 = "";
                BOOST_CHECK(str1 >= str2);
                str1 = "";
                BOOST_CHECK(str1 >= str2);
                str2 = "str";
                BOOST_CHECK(!(str1 >= str2));
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(subscript_operator)
        BOOST_AUTO_TEST_CASE(returns_correct_char_element_by_its_index)
        {
            CMyString str("Hello, World!");
            BOOST_CHECK_EQUAL(str[0], 'H');
            BOOST_CHECK_EQUAL(str[str.GetLength() - 1], '!');
        }

        BOOST_AUTO_TEST_CASE(throws_an_exception_when_index_is_incorrect)
        {
            CMyString str("Some string");
            BOOST_REQUIRE_THROW(str[-1], std::out_of_range);
            BOOST_REQUIRE_THROW(str[str.GetLength()], std::out_of_range);
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_CASE(can_be_read_from_input_stream)
    {
        CMyString str;
        std::stringstream strm("some data in input string");
        strm >> str;
        VerifyString(str, "some", strlen("some"));

        // from empty input stream
        strm = std::stringstream("");
        strm >> str;
        VerifyString(str, "", 0);
    }

    BOOST_AUTO_TEST_CASE(can_be_printed_into_output_stream)
    {
        CMyString str("Hello, World");
        std::stringstream strm;
        strm << str << CMyString("!");
        BOOST_CHECK_EQUAL(strm.str(), "Hello, World!");

        // empty string
        strm = std::stringstream("");
        strm << CMyString();
        BOOST_CHECK_EQUAL(strm.str(), "");
    }
BOOST_AUTO_TEST_SUITE_END()
