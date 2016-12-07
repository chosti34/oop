#include "stdafx.h"
#include "../equation.h"

template <typename Ex, typename Fn>
void ExpectException(Fn &&function, const std::string &expectedDescription)
{
    // Проверяем, что вызов function() выбросит исключение типа Ex 
	// с описанием, равным expectedDescription
	BOOST_CHECK_EXCEPTION(function(), Ex, [&](const Ex &error) {
		return error.what() == expectedDescription; 
    });

    try
    {
        function(); // Выполняем действие, от которого ожидаем выброс исключения
              // Если не выбросило, то тест провалился
        BOOST_ERROR("No exception thrown");
    }
    catch (const Ex &error) // Ловим исключение типа Ex (или его подкласс)
    {
        // Проверяем, что исключение будет иметь ожидаемое сообщение
        BOOST_CHECK_EQUAL(expectedDescription, error.what());
    }
    catch (...)
    {
        // Если выбросили иное исключение, то это также ошибка
        BOOST_ERROR("Unexpected exception");
    }
}

BOOST_AUTO_TEST_SUITE(MySqrt_function)
    BOOST_AUTO_TEST_CASE(throws_an_exception_when_input_parametr_is_negative)
    {
        ExpectException<std::invalid_argument>([] {
            MySqrt(-5);
        }, "Can't calculate square root of negative value...");
        BOOST_REQUIRE_NO_THROW(0);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Solve2_function)
    BOOST_AUTO_TEST_CASE(throws_an_exception_when_first_coefficient_of_quadratic_equation_equal_to_zero)
    {
        ExpectException<std::invalid_argument>([]{
            EquationRoots roots = Solve2(0, 1, -1);
        }, "\"a\" coefficient can't be zero...");
    }

    BOOST_AUTO_TEST_CASE(throws_an_exception_when_quadratic_equation_have_no_real_roots)
    {
        ExpectException<std::domain_error>([] {
            EquationRoots roots = Solve2(1, 0, 1);
        }, "Equation does not have any real roots...");
    }

    BOOST_AUTO_TEST_CASE(returns_one_correct_real_root_when_equation_have_only_one_real_solution)
    {
        EquationRoots roots;
        BOOST_REQUIRE_NO_THROW(roots = Solve2(1, -6, 9));
        BOOST_CHECK_EQUAL(roots.numRoots, 1);
        BOOST_CHECK_EQUAL(roots.root[0], 3);
    }

    BOOST_AUTO_TEST_CASE(return_two_correct_real_roots_when_equation_have_two_real_solutions)
    {
        EquationRoots roots;
        BOOST_REQUIRE_NO_THROW(roots = Solve2(1, -1, -1));
        BOOST_CHECK_EQUAL(roots.numRoots, 2);
        BOOST_CHECK_EQUAL(roots.root[0], (1 + MySqrt(5)) / (2 * 1));
        BOOST_CHECK_EQUAL(roots.root[1], (1 - MySqrt(5)) / (2 * 1));
    }
BOOST_AUTO_TEST_SUITE_END()
