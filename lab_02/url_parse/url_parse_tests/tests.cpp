#include "stdafx.h"
#include "../url_parse.h"

BOOST_AUTO_TEST_SUITE(ParseURL_function)
    BOOST_AUTO_TEST_CASE(returns_false_when_string_is_empty)
    {
        std::string str;
        Url url;
        BOOST_CHECK(!ParseURL(str, url));
    }

    BOOST_AUTO_TEST_CASE(returns_false_when_port_less_than_1_or_bigger_than_65535)
    {
        std::string str = "http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title";
        Url url;
        BOOST_CHECK(!ParseURL(str, url));

        str = "http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title";
        BOOST_CHECK(!ParseURL(str, url));
    }

    BOOST_AUTO_TEST_CASE(returns_false_when_url_has_invalid_protocol)
    {
        std::string str = "xhttp://www.mysite.com:80";
        Url url;
        BOOST_CHECK(!ParseURL(str, url));
    }

    BOOST_AUTO_TEST_CASE(returns_true_when_url_string_is_correct)
    {
        std::string str = "https://ru.wikipedia.org:443/wiki/C%2B%2B";
        Url url;
        BOOST_CHECK(ParseURL(str, url));
    }

    BOOST_AUTO_TEST_CASE(returns_true_when_url_is_correct_and_document_is_empty)
    {
        std::string str = "ftp://mail.ru:431/";
        Url url;
        BOOST_CHECK(ParseURL(str, url));
    }
BOOST_AUTO_TEST_SUITE_END()
