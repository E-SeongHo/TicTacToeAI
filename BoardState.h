#pragma once

#include <vector>

using namespace std;

class BoardState
{
public:
	vector<vector<bool>> maxPlayer;
	vector<vector<bool>> minPlayer;
    bool visited = false;
	int evaluation = -10;
	int turn;

public:
	BoardState()
		:maxPlayer(3, vector<bool>(3)), minPlayer(3, vector<bool>(3)), turn(0)
	{
	}
	BoardState(vector<vector<bool>>& max, vector<vector<bool>>& min, int turn)
		:maxPlayer(max), minPlayer(min), turn(turn)
	{
	}
	bool IsOpen(int y, int x)
	{
		if (!maxPlayer[y][x] && !minPlayer[y][x]) return true;
		else return false;
	}
    bool IsEnd()
    {
        if (IsMaxWin())
        {
            evaluation = 1;
            visited = true;
            return true;
        }
        if (IsMinWin())
        {
            evaluation = -1;
            visited = true;
            return true;
        }
        if (turn == 9)
        {
            evaluation = 0;
            visited = true;
            return true;
        }
        return false;
    }
    bool IsMaxWin()
    {
        // horizontal
        for (int i = 0; i < 3; i++)
        {
            int count = 0;
            for (int j = 0; j < 3; j++)
            {
                if (maxPlayer[i][j]) count++;
                else break;
            }
            if (count == 3) return true;
        }
        // vertical
        for (int i = 0; i < 3; i++)
        {
            int count = 0;
            for (int j = 0; j < 3; j++)
            {
                if (maxPlayer[j][i]) count++;
                else break;
            }
            if (count == 3) return true;
        }
        // diagonal
        for (int i = 0; i < 3; i++)
        {
            if (maxPlayer[0][0] && maxPlayer[1][1] && maxPlayer[2][2]) return true;
            if (maxPlayer[0][2] && maxPlayer[1][1] && maxPlayer[2][0]) return true;
        }
        return false;
    }
    bool IsMinWin()
    {
        // horizontal
        for (int i = 0; i < 3; i++)
        {
            int count = 0;
            for (int j = 0; j < 3; j++)
            {
                if (minPlayer[i][j]) count++;
                else break;
            }
            if (count == 3) return true;
        }
        // vertical
        for (int i = 0; i < 3; i++)
        {
            int count = 0;
            for (int j = 0; j < 3; j++)
            {
                if (minPlayer[j][i]) count++;
                else break;
            }
            if (count == 3) return true;
        }
        // diagonal
        for (int i = 0; i < 3; i++)
        {
            if (minPlayer[0][0] && minPlayer[1][1] && minPlayer[2][2]) return true;
            if (minPlayer[0][2] && minPlayer[1][1] && minPlayer[2][0]) return true;
        }
        return false;
    }
};


