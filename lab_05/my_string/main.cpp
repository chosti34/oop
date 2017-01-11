#include "stdafx.h"
#include "MyString.h"
#include <cmath>

#include <string>

char* Merge(char *x, char* y, unsigned len = 0)
{
    char* z = new char[len];
    memcpy(z, x, strlen(x));
    memcpy(z + strlen(x), y, strlen(y));
    z[len] = '\0';
    return z;
}

char* Foo()
{
    char *a = "asdads";
    return a;
}

int main()
{
    /*char *x = "timur";
    char *y = "xyz";

    char *z = Merge(x, y, strlen(x) + strlen(y));

    std::cout << z << std::endl;*/

    CMyString str1("timur");
    CMyString str2("xyz");


    //CMyString str("abcd", 2);

    //std::cout << str << std::endl;

    std::cout << str1 + str2 + "asd" << std::endl;

    std::cout << Foo() << std::endl;

    return 0;
}
