#include "stdafx.h"
#include "../MyStack.h"

struct EmptyStack
{
    CMyStack<std::string> stringStack;
    CMyStack<int> intStack;
};

BOOST_FIXTURE_TEST_SUITE(Stack, EmptyStack)
    BOOST_AUTO_TEST_SUITE(when_created)
        BOOST_AUTO_TEST_CASE(is_empty)
        {
            // string
            BOOST_CHECK_EQUAL(stringStack.GetSize(), 0);

            // int
            BOOST_CHECK_EQUAL(intStack.GetSize(), 0);
        }

        BOOST_AUTO_TEST_CASE(pop_method_throws_an_exception_because_stack_is_empty)
        {
            // string
            BOOST_REQUIRE_THROW(stringStack.Pop(), std::underflow_error);

            // int
            BOOST_REQUIRE_THROW(intStack.Pop(), std::underflow_error);
        }

        BOOST_AUTO_TEST_CASE(get_top_method_throws_an_exception_because_stack_is_empty)
        {
            // string
            BOOST_REQUIRE_THROW(stringStack.GetTopElement(), std::underflow_error);

            // int
            BOOST_REQUIRE_THROW(intStack.GetTopElement(), std::underflow_error);
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(after_element_push)
        BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
        {
            // int
            {
                size_t oldSize = intStack.GetSize();
                intStack.Push(1);
                BOOST_CHECK_EQUAL(intStack.GetSize(), oldSize + 1);
                intStack.Push(2);
                BOOST_CHECK_EQUAL(intStack.GetSize(), oldSize + 2);
            }

            // string
            {
                size_t oldSize = stringStack.GetSize();
                stringStack.Push("hello");
                BOOST_CHECK_EQUAL(stringStack.GetSize(), oldSize + 1);
                stringStack.Push("world");
                BOOST_CHECK_EQUAL(stringStack.GetSize(), oldSize + 2);
            }
        }

        BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetTopElement_method)
        {
            // int
            {
                intStack.Push(-5);
                BOOST_CHECK_EQUAL(intStack.GetTopElement(), -5);
                intStack.Push(10);
                BOOST_CHECK_EQUAL(intStack.GetTopElement(), 10);
            }

            // string
            {
                stringStack.Push("hello");
                BOOST_CHECK_EQUAL(stringStack.GetTopElement(), "hello");
                stringStack.Push("goodbye");
                BOOST_CHECK_EQUAL(stringStack.GetTopElement(), "goodbye");
            }
        }

        BOOST_AUTO_TEST_CASE(it_can_be_popped)
        {
            // int
            {
                size_t oldSize = intStack.GetSize();
                intStack.Push(11);
                BOOST_CHECK_EQUAL(intStack.GetSize(), oldSize + 1);
                intStack.Pop();
                BOOST_CHECK_EQUAL(intStack.GetSize(), oldSize);
            }

            // string
            {
                size_t oldSize = stringStack.GetSize();
                stringStack.Push("hello");
                BOOST_CHECK_EQUAL(stringStack.GetSize(), oldSize + 1);
                stringStack.Pop();
                BOOST_CHECK_EQUAL(stringStack.GetSize(), oldSize);
            }
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_CASE(can_be_cleared_correctly)
    {
        // int
        {
            for (int i = 0; i < 10; ++i)
            {
                intStack.Push(i);
            }
            BOOST_CHECK_EQUAL(intStack.GetSize(), 10);
            intStack.Clear();
            BOOST_CHECK_EQUAL(intStack.GetSize(), 0);
        }

        // string
        {
            for (int i = 0; i < 10; ++i)
            {
                stringStack.Push("string");
            }
            BOOST_CHECK_EQUAL(stringStack.GetSize(), 10);
            stringStack.Clear();
            BOOST_CHECK_EQUAL(stringStack.GetSize(), 0);
        }
    }

    BOOST_AUTO_TEST_CASE(can_be_copied_correctly)
    {
        // int
        {
            for (int i = 0; i < 10; ++i)
            {
                intStack.Push(i);
            }

            CMyStack<int> newIntStack = intStack;

            BOOST_CHECK_EQUAL(intStack.GetSize(), newIntStack.GetSize());

            for (size_t i = 0; i < intStack.GetSize(); ++i)
            {
                BOOST_CHECK_EQUAL(intStack.GetTopElement(), newIntStack.GetTopElement());
                intStack.Pop();
                newIntStack.Pop();
            }
        }
    }

    BOOST_AUTO_TEST_CASE(can_be_moved_correctly)
    {
        // int
        {
            for (int i = 0; i < 10; ++i)
            {
                intStack.Push(i);
            }
            size_t size = intStack.GetSize();

            CMyStack<int> copiedStack = intStack;
            CMyStack<int> movedStack = std::move(intStack);

            BOOST_CHECK_EQUAL(intStack.GetSize(), 0);
            BOOST_CHECK_EQUAL(copiedStack.GetSize(), size);
            BOOST_CHECK_EQUAL(movedStack.GetSize(), size);

            while (!copiedStack.IsEmpty())
            {
                BOOST_CHECK_EQUAL(copiedStack.GetTopElement(), movedStack.GetTopElement());
                copiedStack.Pop();
                movedStack.Pop();
            }
        }
    }
BOOST_AUTO_TEST_SUITE_END()
