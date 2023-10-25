#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

#include "BoardState.h"

using namespace std;

#define MAX_X 25
#define MAX_Y 7
#define START_Y 2

void GotoXY(int x, int y);
void PrintBoard();
void InputProcess();
bool IsWin();
int MappingValue(int val, char factor);

int MiniMax(int mapY, int mapX, int turn);
void SearchGameTree(BoardState* current, int depth);

int board[MAX_Y][MAX_X];
vector<vector<bool>> player1(3, vector<bool>(3));
vector<vector<bool>> player2(3, vector<bool>(3));

int turn;
int winner;

int main()
{
    // set border
    for (int i = 0; i < MAX_X; i++)
    {
        board[0][i] = 1;
        board[2][i] = 1;
        board[4][i] = 1;
        board[6][i] = 1;
    }
    for (int i = 1; i < MAX_Y; i += 2)
    {
        board[i][0] = 1;
        board[i][8] = 1;
        board[i][16] = 1;
        board[i][24] = 1;
    }

    turn = 0;
    winner = 0;

    while (1)
    {
        if (winner != 0 || turn >= 9)
        {
            PrintBoard();
            GotoXY(0, MAX_Y + 6);
            if (winner == 1) cout << "Player 1 Win";
            else if (winner == 2) cout << "Player 2 Win";
            else if (turn >= 9) cout << "Draw!!";
            break;
        }
        else
        {
            system("cls");

            GotoXY(0, 0);
            if (turn % 2 == 0) cout << "Player 1 turn";
            else cout << "Player 2 turn";

            PrintBoard();
            InputProcess();

            Sleep(100);
        }
    }

    Sleep(1000);
    return 0;
}

int MappingValue(int val, char factor)
{
    if (factor == 'x')
    {
        if (val > 0 && val < 8) return 0;
        else if (val >= 8 && val < 16) return 1;
        else if (val >= 16 && val < 24) return 2;
    }
    else if (factor == 'y')
    {
        val -= START_Y;
        if (val > 0 && val < 2) return 0;
        else if (val >= 2 && val < 4) return 1;
        else if (val >= 4 && val < 6) return 2;
    }
}
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void PrintBoard()
{
    GotoXY(0, 2);
    for (int i = 0; i < MAX_Y; i++)
    {
        for (int j = 0; j < MAX_X; j++)
        {
            if (board[i][j] == 1) cout << '#';
            else if (board[i][j] == 2) cout << 'X';
            else if (board[i][j] == 3) cout << 'O';
            else cout << " ";
        }
        cout << endl;
    }
}
bool IsWin()
{
    // Search
    // player1
    if (turn % 2 == 0)
    {
        // horizontal
        for (int i = 0; i < 3; i++)
        {
            int count = 0;
            for (int j = 0; j < 3; j++)
            {
                if (player1[i][j]) count++;
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
                if (player1[j][i]) count++;
                else break;
            }
            if (count == 3) return true;
        }
        // diagonal
        for (int i = 0; i < 3; i++)
        {
            if (player1[0][0] && player1[1][1] && player1[2][2]) return true;
            if (player1[0][2] && player1[1][1] && player1[2][0]) return true;
        }
        return false;
    }
    else
    {
        // horizontal
        for (int i = 0; i < 3; i++)
        {
            int count = 0;
            for (int j = 0; j < 3; j++)
            {
                if (player2[i][j]) count++;
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
                if (player2[j][i]) count++;
                else break;
            }
            if (count == 3) return true;
        }
        // diagonal
        for (int i = 0; i < 3; i++)
        {
            if (player2[0][0] && player2[1][1] && player2[2][2]) return true;
            if (player2[0][2] && player2[1][1] && player2[2][0]) return true;
        }
        return false;
    }

}

void InputProcess()
{
    int X = (MAX_X / 2);
    int Y = (MAX_Y / 2) + START_Y;

    int eval = 0;

    bool enter = false;
    char icon = '+';
    int keyin = 0;
    while (!enter)
    {
        // print info
        GotoXY(0, MAX_Y + 3);
        cout << "X: " << X << " \n";
        cout << "Y: " << Y << " \n";
        cout << "Last keyin value: " << keyin << " \n";
        cout << "Expect: " << eval << "  \n";

        GotoXY(X, Y);
        cout << icon;
        keyin = _getch();
        cout << "\b ";
        if (player1[MappingValue(Y, 'y')][MappingValue(X, 'x')]) cout << "\bX";
        else if (player2[MappingValue(Y, 'y')][MappingValue(X, 'x')]) cout << "\bO";

        switch (keyin)
        {
        case 224: // arrow keys
        {
            keyin = _getch();
            switch (keyin)
            {
            case 72: // up
                if (Y - 2 > 2) Y -= 2;
                break;
            case 75: // left
                if (X - 8 > 0) X -= 8;
                break;
            case 77: // right
                if (X + 8 < MAX_X) X += 8;
                break;
            case 80: // down
                if (Y + 2 < MAX_Y + 2) Y += 2;
                break;
            }
            int mapY = MappingValue(Y, 'y');
            int mapX = MappingValue(X, 'x');
            eval = MiniMax(mapY, mapX, turn);

            break;
        }
        case 13: // enter
        {
            int mapY = MappingValue(Y, 'y');
            int mapX = MappingValue(X, 'x');

            if (turn % 2 == 0) // player 1's input
            {
                if (!player1[mapY][mapX] && !player2[mapY][mapX])
                {
                    player1[mapY][mapX] = true;
                    if (IsWin()) winner = 1;
                    enter = true;
                }
                else continue;
            }
            else // player 2's input
            {
                if (!player1[mapY][mapX] && !player2[mapY][mapX])
                {
                    player2[mapY][mapX] = true;
                    if (IsWin()) winner = 2;
                    enter = true;
                }
                else continue;
            }
            board[Y - START_Y][X] = (turn % 2) + 2; // player1 = 2, player2 = 3
            break;
        }
        }
    }
    turn++;
}

int MiniMax(int mapY, int mapX, int turn)
{
    BoardState* current;
    if (turn % 2 == 0) // was player 1, Search tree from player2's turn
    {
        current = new BoardState(player2, player1, turn + 1);
    }
    else
    {
        current = new BoardState(player1, player2, turn + 1);
    }

    current->minPlayer[mapY][mapX] = true;
    SearchGameTree(current, 0);

    int eval = current->evaluation;
    eval = -eval;

    delete current;

    return eval;
}

void SearchGameTree(BoardState* current, int depth)
{
    if (current->IsEnd())
        return;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (current->IsOpen(i, j))
            {
                BoardState* child = new BoardState(current->maxPlayer, current->minPlayer, current->turn+1);
                if (depth % 2 == 0) // max turn
                    child->maxPlayer[i][j] = true;
                else // min turn
                    child->minPlayer[i][j] = true;

                SearchGameTree(child, depth + 1);

                if (!current->visited)
                {
                    current->evaluation = child->evaluation;
                    current->visited = true;
                }
                else
                {
                    if (depth % 2 == 0)
                        current->evaluation = max(current->evaluation, child->evaluation);
                    else
                        current->evaluation = min(current->evaluation, child->evaluation);
                }
                    
                delete child;
            }
        }
    }

}