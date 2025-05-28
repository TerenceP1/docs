#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

typedef vector<vector<bool>> cBoard; // Chess board

// Stores one iteration for BFS

struct iteration
{
    cBoard board;
    bool f_found; // True if forward BFS found this board
    bool b_found; // True if backward BFS found this board
    int fDst;     // Moves to get to this board from starting postion
    int bDst;     // Moves to get to this board from ending postion
    bool operator<(iteration bd)
    {
        if (board < bd.board)
        {
            return true;
        }
        else if (board > bd.board)
        {
            return false;
        }
        else if (f_found < bd.f_found)
        {
            return true;
        }
        else if (f_found > bd.f_found)
        {
            return false;
        }
        else if (b_found < bd.b_found)
        {
            return true;
        }
        else if (b_found > bd.b_found)
        {
            return false;
        }
        else if (fDst < bd.fDst)
        {
            return true;
        }
        else if (fDst > bd.fDst)
        {
            return false;
        }
        else if (bDst < bd.bDst)
        {
            return true;
        }
        else if (bDst > bd.bDst)
        {
            return false;
        }
        else
        {
            return false;
        }
    }
};

// Store iteration state for use in map

struct cbDst
{
    bool f_found; // True if forward BFS found this board
    bool b_found; // True if backward BFS found this board
    int fDst;     // Moves to get to this board from starting postion
    int bDst;     // Moves to get to this board from ending postion
    bool operator<(iteration bd)
    {
        if (f_found < bd.f_found)
        {
            return true;
        }
        else if (f_found > bd.f_found)
        {
            return false;
        }
        else if (b_found < bd.b_found)
        {
            return true;
        }
        else if (b_found > bd.b_found)
        {
            return false;
        }
        else if (fDst < bd.fDst)
        {
            return true;
        }
        else if (fDst > bd.fDst)
        {
            return false;
        }
        else if (bDst < bd.bDst)
        {
            return true;
        }
        else if (bDst > bd.bDst)
        {
            return false;
        }
        else
        {
            return false;
        }
    }
};

bool isValid(int x, int y)
{
    return (x > -1) && (x < 4) && (y > -1) && (y < 4);
}

int main()
{

    // User input

    cBoard start(4);
    cBoard end(4);
    for (int i = 0; i < 4; i++)
    {
        start[i].resize(4);
        string tmp;
        cin >> tmp;
        for (int j = 0; j < 4; j++)
        {
            start[i][j] = tmp[j] - '0';
        }
    }

    for (int i = 0; i < 4; i++)
    {
        end[i].resize(4);
        string tmp;
        cin >> tmp;
        for (int j = 0; j < 4; j++)
        {
            end[i][j] = tmp[j] - '0';
        }
    }

    // Forward + backward BFS

    map<cBoard, cbDst> mvs;
    queue<iteration> q;
    q.push({start, 1, 0, 0, 0});
    q.push({end, 0, 1, 0, 0});
    while (!q.empty())
    {
        iteration tst = q.front();
        q.pop();
        // Find all possible iterations
        vector<iteration> itrs;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int dsX1 = i + 1; // Possible swap
                int dsY1 = j;     // Possible swap
                int dsX2 = i;     // Possible swap
                int dsY2 = j + 1; // Possible swap
                if (isValid(dsX1, dsY1))
                {
                    cBoard cBd = tst.board; // Board to test
                    cBd[i][j] = tst.board[dsX1][dsY1];
                    cBd[dsX1][dsY1] = tst.board[i][j];
                    if (mvs.find(cBd) == mvs.end())
                    {
                        if (tst.f_found)
                        {
                            q.push({cBd, 1, 0, tst.fDst + 1, 0});
                            mvs.insert({cBd, {1, 0, tst.fDst + 1, 0}});
                        }
                        else
                        {
                            q.push({cBd, 0, 1, 0, tst.bDst + 1});
                            mvs.insert({cBd, {0, 1, 0, tst.bDst + 1}});
                        }
                    }
                    else
                    {
                        pair<cBoard, cbDst> pstres = *mvs.find(cBd); // Last time cBd was found
                        if (tst.f_found != pstres.second.f_found)
                        {
                            if (tst.f_found)
                            {
                                cout << tst.fDst + pstres.second.bDst + 1;
                                return 0;
                            }
                            else
                            {
                                cout << tst.bDst + pstres.second.fDst + 1;
                                return 0;
                            }
                        }
                    }
                }
                if (isValid(dsX2, dsY2))
                {
                    cBoard cBd = tst.board; // Board to test
                    cBd[i][j] = tst.board[dsX2][dsY2];
                    cBd[dsX2][dsY2] = tst.board[i][j];
                    if (mvs.find(cBd) == mvs.end())
                    {
                        if (tst.f_found)
                        {
                            q.push({cBd, 1, 0, tst.fDst + 1, 0});
                            mvs.insert({cBd, {1, 0, tst.fDst + 1, 0}});
                        }
                        else
                        {
                            q.push({cBd, 0, 1, 0, tst.bDst + 1});
                            mvs.insert({cBd, {0, 1, 0, tst.bDst + 1}});
                        }
                    }
                    else
                    {
                        pair<cBoard, cbDst> pstres = *mvs.find(cBd); // Last time cBd was found
                        if (tst.f_found != pstres.second.f_found)
                        {
                            if (tst.f_found)
                            {
                                cout << tst.fDst + pstres.second.bDst + 1;
                                return 0;
                            }
                            else
                            {
                                cout << tst.bDst + pstres.second.fDst + 1;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
}