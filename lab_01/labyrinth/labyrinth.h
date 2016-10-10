#pragma once

#include <fstream>
#include <string>

#include "field.h"

using namespace std;

enum CellCategory
{
    WALL = -4,
    BLANK = -3,
    START = -2,
    END = -1,
    PATH = -5
};

struct Point
{
    int x;
    int y;
};

struct Labyrinth
{
    Point start, finish;
    Field field;

    bool haveStart;
    bool haveFinish;
};

bool InitializeLabyrinthFromFile(ifstream &file, Labyrinth &labyrinth);
bool SetWaves(Labyrinth &labyrinth);
bool SetPath(Labyrinth &labyrinth);

void DrawLabyrinth(ofstream &file, Labyrinth &labyrinth);
