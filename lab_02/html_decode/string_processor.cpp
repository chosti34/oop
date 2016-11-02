#include "stdafx.h"
#include "string_processor.h"

bool IsStrContains(const std::string &str, const std::string &substr, const size_t position)
{
    return (substr.compare(0, substr.length(), str, position, substr.length()) == 0);
}
