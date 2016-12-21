#include "stdafx.h"
#include "MyStack.h"

int main()
{
    CMyStack<int> stack1;

    for (size_t i = 0; i < 100; ++i)
    {
        stack1.Push(i);
    }

    CMyStack<int> stack2(stack1);

    std::cout << stack2.GetTopElement() << std::endl;

    return 0;
}
