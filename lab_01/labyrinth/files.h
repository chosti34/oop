#pragma once

#include <fstream>
#include <string>

using namespace std;

bool OpenFileForReading(ifstream &file, const string &fileName);
bool OpenFileForWriting(ofstream &file, const string &fileName);