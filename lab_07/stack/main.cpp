#include "stdafx.h"
#include "MyStack.h"

int main()
{
    CMyStack<int> a;
    a.Push(1);

    CMyStack<int> b(a);

    return 0;
}
