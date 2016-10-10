#pragma once

static const int MAX_HEIGHT = 100;
static const int MAX_WIDTH = 100;

typedef int Field[MAX_HEIGHT][MAX_WIDTH];

void InitializeField(Field &field);
void DrawField(Field &field);
