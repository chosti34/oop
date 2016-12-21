#include "stdafx.h"
#include "../vector_processor.h"

struct Athlete
{
    std::string name;
    double height;
    double weight;
};

bool IsHeightLess(const Athlete &left, const Athlete &right)
{
    return (left.height < right.height);
}

bool IsWeightLess(const Athlete &left, const Athlete &right)
{
    return (left.weight < right.weight);
}

bool AthletesAreEqual(const Athlete &left, const Athlete &right)
{
    return (left.name == right.name) && (left.height == right.height) && (left.weight == right.weight);
}

const Athlete KuaiLiang = { "Kuai Liang", 188.3, 105 };
const Athlete Hanzo = { "Hanzo Hasashi", 188, 93 };
const Athlete BiHan = { "Bi-Han", 180, 95 };
const Athlete KungLao = { "Kung Lao", 178, 80 };
const Athlete LiuKang = { "Liu Kang", 188.4, 90 };

const std::vector<Athlete> athletes = { KuaiLiang, Hanzo, BiHan, KungLao, LiuKang };

BOOST_AUTO_TEST_SUITE(FindMax_function)

    BOOST_AUTO_TEST_CASE(returns_false_when_vector_is_empty)
    {
        // int
        {
            std::vector<int> vect;
            int max = 0;
            BOOST_CHECK(!FindMax(vect, max));
            BOOST_CHECK(max == 0);
        }

        // string
        {
            std::vector<std::string> vect;
            std::string max;
            BOOST_CHECK(!FindMax(vect, max));
            BOOST_CHECK_EQUAL(max, "");
        }

        // custom type
        {
            std::vector<Athlete> vect;
            Athlete athlete = KungLao;
            BOOST_CHECK(!FindMax(vect, athlete, IsHeightLess));
            BOOST_CHECK(!FindMax(vect, athlete, IsWeightLess));
            BOOST_CHECK(AthletesAreEqual(athlete, KungLao));
        }
    }

    BOOST_AUTO_TEST_CASE(returns_true_when_correct_max_element_of_non_empty_vector_has_been_found)
    {
        // int
        {
            std::vector<int> vect = { -27, 0, 0, 27, 28, 27, 28 };
            int max = 0;
            BOOST_CHECK(FindMax(vect, max, [](int a, int b) {return a < b;}));
            BOOST_CHECK_EQUAL(max, 28);
        }

        // string
        {
            std::vector<std::string> vect = { "123", "space", "digit", "z", "xcx", "zxc" };
            std::string max;
            BOOST_CHECK(FindMax(vect, max));
            BOOST_CHECK_EQUAL(max, "zxc");
        }

        // const char
        {
            std::vector<const char*> vect = { "123", "space", "digit", "z", "xcx", "zxc" };
            const char *str = "";

            auto IsConstCharLess = [](const char *a, const char *b)
            {
                return (strcmp(a, b) < 0);
            };

            BOOST_CHECK(FindMax(vect, str, IsConstCharLess));
            BOOST_CHECK_EQUAL(str, "zxc");
        }

        // custom type
        {
            Athlete athlete = KungLao;

            // with max height (Liu Kang)
            BOOST_CHECK(FindMax(athletes, athlete, IsHeightLess));
            BOOST_CHECK(AthletesAreEqual(athlete, LiuKang));

            // with max weight (KuaiLiang)
            BOOST_CHECK(FindMax(athletes, athlete, IsWeightLess));
            BOOST_CHECK(AthletesAreEqual(athlete, KuaiLiang));
        }
    }

BOOST_AUTO_TEST_SUITE_END()
