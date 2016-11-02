#include "stdafx.h"
#include "../html_processor.h"

bool StringsAreEqual(const std::string &x, const std::string &y)
{
    return (x == y);
}

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)
    BOOST_AUTO_TEST_CASE(makes_empty_str_by_decoding_empty_str)
    {
        std::string emptyStr;
        std::string decodedStr = HtmlDecode(emptyStr);
        BOOST_CHECK(StringsAreEqual(decodedStr, emptyStr));
    }

    BOOST_AUTO_TEST_CASE(makes_same_string_without_html_special_chars)
    {
        std::string someStr = "hypertext markup language";
        std::string decodedStr = HtmlDecode(someStr);
        BOOST_CHECK(StringsAreEqual(decodedStr, someStr));
    }

    BOOST_AUTO_TEST_CASE(makes_decoded_string_with_all_five_special_chars)
    {
        std::string someStr = "&lt;username&gt; say&apos;s: &quot;head&amp;shoulders&quot;";
        std::string decodedStr = HtmlDecode(someStr);
        BOOST_CHECK(StringsAreEqual(decodedStr, "<username> say's: \"head&shoulders\""));
    }

    BOOST_AUTO_TEST_CASE(makes_decoded_string_with_repeating_special_chars)
    {
        std::string someStr = "std::cout &lt;&lt; &quot;Hello, World!&quot;";
        std::string decodedStr = HtmlDecode(someStr);
        BOOST_CHECK(StringsAreEqual(decodedStr, "std::cout << \"Hello, World!\""));
    }

    BOOST_AUTO_TEST_CASE(makes_correct_decoded_string_without_repeating_decode)
    {
        std::string someStr = "&amp;gt;";
        std::string decodedStr = HtmlDecode(someStr);
        BOOST_CHECK(StringsAreEqual(decodedStr, "&gt;"));
    }
BOOST_AUTO_TEST_SUITE_END()
