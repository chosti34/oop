#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <windows.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702) // To disable 4702 warning in boost
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/replace.hpp>
