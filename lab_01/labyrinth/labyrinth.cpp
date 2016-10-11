#include "labyrinth.h"

bool InitializeLabyrinthFromFile(ifstream &file, Labyrinth &labyrinth)
{
    InitializeField(labyrinth.field);

    labyrinth.haveStart = false;
    labyrinth.haveFinish = false;

    string str;

    for (int row = 0; row < MAX_HEIGHT; ++row)
    {
        if (!getline(file, str))
        {
            break;
        }

        for (int col = 0; col < str.length(); ++col)
        {
            switch (str[col])
            {
            case 'A':
                if (labyrinth.haveStart)
                {
                    return false;
                }
                labyrinth.start.x = col;
                labyrinth.start.y = row;
                labyrinth.field[row][col] = START;
                labyrinth.haveStart = true;
                break;
            case 'B':
                if (labyrinth.haveFinish)
                {
                    return false;
                }
                labyrinth.finish.x = col;
                labyrinth.finish.y = row;
                labyrinth.field[row][col] = END;
                labyrinth.haveFinish = true;
                break;
            case '#':
                labyrinth.field[row][col] = WALL;
                break;
            case ' ':
                labyrinth.field[row][col] = BLANK;
                break;
            default:
                return false;
            }
        }
    }

    if ((!labyrinth.haveStart) || (!labyrinth.haveFinish))
    {
        return false;
    }

    return true;
}

bool SetWaves(Labyrinth &labyrinth)
{
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    int startWavePoint = 0;
    labyrinth.field[labyrinth.start.y][labyrinth.start.x] = startWavePoint;

    bool stop = false;

    while (!stop)
    {
        stop = true;

        for (int row = 0; row < MAX_HEIGHT; ++row)
        {
            for (int col = 0; col < MAX_WIDTH; ++col)
            {
                if (labyrinth.field[row][col] == startWavePoint)
                {
                    // проход по соседям
                    for (int inner = 0; inner < 4; ++inner)
                    {
                        int nextRow = row + dy[inner], nextCol = col + dx[inner];
                        if (nextRow >= 0 && nextRow < MAX_HEIGHT && nextCol >= 0 && nextCol < MAX_WIDTH
                            && (labyrinth.field[nextRow][nextCol] == BLANK || labyrinth.field[nextRow][nextCol] == END))
                        {
                            stop = false;
                            labyrinth.field[nextRow][nextCol] = startWavePoint + 1;
                        }
                    }
                }
            }
        }
        startWavePoint++;
    }

    return true;
}

bool SetPath(Labyrinth &labyrinth)
{
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    int length = labyrinth.field[labyrinth.finish.y][labyrinth.finish.x];

    int row = labyrinth.finish.y;
    int col = labyrinth.finish.x;

    int endWavePoint = length;

    labyrinth.field[labyrinth.finish.y][labyrinth.finish.x] = END;
    labyrinth.field[labyrinth.start.y][labyrinth.start.x] = START;

    while (endWavePoint > 0)
    {
        endWavePoint--;

        if ((labyrinth.field[row][col] != END) && (labyrinth.field[row][col] != START))
        {
            labyrinth.field[row][col] = PATH;
        }

        for (int inner = 0; inner < 4; ++inner)
        {
            int nextRow = row + dy[inner], nextCol = col + dx[inner];
            if (nextRow >= 0 && nextRow < MAX_HEIGHT && nextCol >= 0 && nextCol < MAX_WIDTH
                && labyrinth.field[nextRow][nextCol] == endWavePoint)
            {
                    row = row + dy[inner];
                    col = col + dx[inner];
                    break;
            }
        }
    }

    return true;
}

void DrawLabyrinth(ofstream &file, Labyrinth &labyrinth)
{
    bool isLabyrinthElement = false;
    int cell;
    char cellToPrint;

    for (int row = 0; row < MAX_HEIGHT; ++row)
    {
        for (int col = 0; col < MAX_WIDTH; ++col)
        {
            cell = labyrinth.field[row][col];
            switch (cell)
            {
                case WALL:
                    cellToPrint = '#';
                    file << cellToPrint;
                    break;
                case BLANK:
                    cellToPrint = ' ';
                    file << cellToPrint;
                    break;
                case START:
                    cellToPrint = 'A';
                    file << cellToPrint;
                    break;
                case END:
                    cellToPrint = 'B';
                    file << cellToPrint;
                    break;
                case PATH:
                    cellToPrint = '.';
                    file << cellToPrint;
                    break;
                default:
                    cellToPrint = ' ';
                    file << cellToPrint;
                    break;
            }
        }
        file << std::endl;
    }
}
