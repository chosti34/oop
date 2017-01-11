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
            BOOST_CHECK_EQUAL(intStack.GetSize(), 0); // int
            BOOST_CHECK_EQUAL(stringStack.GetSize(), 0); // string
        }

        BOOST_AUTO_TEST_CASE(pop_method_throws_an_exception_because_stack_is_empty)
        {
            BOOST_REQUIRE_THROW(intStack.Pop(), std::underflow_error); // int
            BOOST_REQUIRE_THROW(stringStack.Pop(), std::underflow_error); // string
        }

        BOOST_AUTO_TEST_CASE(get_top_method_throws_an_exception_because_stack_is_empty)
        {
            BOOST_REQUIRE_THROW(intStack.GetTopElement(), std::underflow_error); // int
            BOOST_REQUIRE_THROW(stringStack.GetTopElement(), std::underflow_error); // string
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(after_element_push)
        BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
        {
            // int
            {
                std::size_t oldSize = intStack.GetSize();
                intStack.Push(1);
                BOOST_CHECK_EQUAL(intStack.GetSize(), oldSize + 1);
                intStack.Push(2);
                BOOST_CHECK_EQUAL(intStack.GetSize(), oldSize + 2);
            }

            // string
            {
                std::size_t oldSize = stringStack.GetSize();
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
                std::size_t oldSize = intStack.GetSize();
                intStack.Push(11);
                BOOST_CHECK_EQUAL(intStack.GetSize(), oldSize + 1);
                intStack.Pop();
                BOOST_CHECK_EQUAL(intStack.GetSize(), oldSize);
            }

            // string
            {
                std::size_t oldSize = stringStack.GetSize();
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
        // by constructor
        {
            for (int i = 0; i < 10; ++i)
            {
                intStack.Push(i);
            }
            CMyStack<int> newIntStack = intStack;

            BOOST_CHECK_EQUAL(intStack.GetSize(), newIntStack.GetSize());
            for (std::size_t i = 0; i < intStack.GetSize(); ++i)
            {
                BOOST_CHECK_EQUAL(intStack.GetSize(), newIntStack.GetSize());
                intStack.Pop();
                newIntStack.Pop();
            }
        }

        // by assignment operator
        {
            for (int i = 0; i < 10; ++i)
            {
                intStack.Push(i);
            }
            CMyStack<int> newIntStack;
            newIntStack = intStack;

            BOOST_CHECK_EQUAL(intStack.GetSize(), newIntStack.GetSize());
            while (!intStack.IsEmpty())
            {
                BOOST_CHECK_EQUAL(intStack.GetTopElement(), newIntStack.GetTopElement());
                intStack.Pop();
                newIntStack.Pop();
            }
        }
    }

    BOOST_AUTO_TEST_CASE(can_be_moved_correctly)
    {
        // by constructor
        {
            for (int i = 0; i < 10; ++i)
            {
                intStack.Push(i);
            }
            std::size_t oldSize = intStack.GetSize();

            CMyStack<int> copy = intStack;
            CMyStack<int> acceptor = std::move(intStack);

            BOOST_CHECK_EQUAL(intStack.GetSize(), 0);
            BOOST_CHECK_EQUAL(copy.GetSize(), oldSize);
            BOOST_CHECK_EQUAL(acceptor.GetSize(), oldSize);

            while (!copy.IsEmpty())
            {
                BOOST_CHECK_EQUAL(copy.GetTopElement(), acceptor.GetTopElement());
                copy.Pop();
                acceptor.Pop();
            }
        }

        // by assignment operator
        {
            for (int i = 0; i < 10; ++i)
            {
                intStack.Push(i);
            }
            std::size_t oldSize = intStack.GetSize();

            CMyStack<int> copy = intStack;
            CMyStack<int> acceptor;
            acceptor = std::move(intStack);

            BOOST_CHECK_EQUAL(intStack.GetSize(), 0);
            BOOST_CHECK_EQUAL(copy.GetSize(), oldSize);
            BOOST_CHECK_EQUAL(acceptor.GetSize(), oldSize);

            while (!copy.IsEmpty())
            {
                BOOST_CHECK_EQUAL(copy.GetTopElement(), acceptor.GetTopElement());
                copy.Pop();
                acceptor.Pop();
            }
        }
    }

    BOOST_AUTO_TEST_CASE(can_be_assigned_to_itself_correctly)
    {
        // copy
        {
            CMyStack<int> stack1;
            CMyStack<int> stack2;

            for (int i = 0; i < 10; ++i)
            {
                stack1.Push(i);
            }

            stack2 = stack1;
            stack1 = stack2;

            BOOST_CHECK_EQUAL(stack1.GetSize(), stack2.GetSize());

            while (!stack1.IsEmpty())
            {
                BOOST_CHECK_EQUAL(stack1.GetTopElement(), stack2.GetTopElement());
                stack1.Pop();
                stack2.Pop();
            }
        }

        // move
        {
            CMyStack<int> stack1;
            CMyStack<int> stack2;

            int amount = 10;

            for (int i = 0; i < amount; ++i)
            {
                stack1.Push(i);
            }

            stack2 = std::move(stack1);
            stack1 = std::move(stack2);

            BOOST_CHECK_EQUAL(stack1.GetSize(), amount);
            BOOST_CHECK(stack2.IsEmpty());

            while (!stack1.IsEmpty())
            {
                BOOST_CHECK_EQUAL(stack1.GetTopElement(), amount - 1);
                stack1.Pop();
                --amount;
            }
        }
    }

    BOOST_AUTO_TEST_CASE(can_contain_large_number_of_elements)
    {
        int amount = 20000;

        for (int i = 0; i < amount; ++i)
        {
            intStack.Push(i);
        }

        BOOST_CHECK_EQUAL(intStack.GetSize(), amount);

        while (!intStack.IsEmpty())
        {
            BOOST_CHECK_EQUAL(intStack.GetTopElement(), amount - 1);
            intStack.Pop();
            --amount;
        }
    }
BOOST_AUTO_TEST_SUITE_END()
