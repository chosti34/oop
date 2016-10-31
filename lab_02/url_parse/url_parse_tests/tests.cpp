#include "stdafx.h"
#include "../url_parse.h"

BOOST_AUTO_TEST_SUITE(ParseURL_function)
    BOOST_AUTO_TEST_CASE(trying_to_parse_empty_string)
    {
        std::string str;
        Url url;
        BOOST_CHECK(!ParseURL(str, url));
    }

    BOOST_AUTO_TEST_CASE(parsing_url_with_out_of_boundary_values_of_port)
    {
        std::string str = "http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title";
        Url url;
        BOOST_CHECK(!ParseURL(str, url));

        str = "http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title";
        BOOST_CHECK(!ParseURL(str, url));
    }

    BOOST_AUTO_TEST_CASE(parsing_url_with_invalid_protocol)
    {
        std::string str = "xhttp://www.mysite.com:80";
        Url url;
        BOOST_CHECK(!ParseURL(str, url));
    }

    BOOST_AUTO_TEST_CASE(parsing_correct_url_string)
    {
        std::string str = "https://ru.wikipedia.org:443/wiki/C%2B%2B";
        Url url;
        BOOST_CHECK(ParseURL(str, url));
    }
BOOST_AUTO_TEST_SUITE_END()
