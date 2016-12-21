#include "stdafx.h"
#include "MyStack.h"

int main()
{
    for (size_t i = 0; i < 10000; ++i)
    {
        while (true)
        {
            CMyStack<int> stack1;

            for (size_t i = 0; i < 100; ++i)
            {
                stack1.Push(i);
            }

            CMyStack<int> stackn(stack1);
            CMyStack<int> stack2 = stack1;
        }
    }

    CMyStack<int> stack1;

    for (size_t i = 0; i < 100; ++i)
    {
        stack1.Push(i);
    }

    CMyStack<int> stack2 = stack1;

    for (int i = 0; i < 100; ++i)
    {
        std::cout << stack2.GetTopElement() << std::endl;
        stack2.Pop();
    }

    return 0;
}
