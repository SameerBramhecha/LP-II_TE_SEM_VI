#include <bits/stdc++.h>
using namespace std;
class NQueens_BNB
{
    int n;

public:
    NQueens_BNB(int n)
    {
        this->n = n;
    }
    bool isSafe(int, int, vector<bool> rows, vector<bool> ld, vector<bool> rd);
    bool solve(vector<vector<char>> &board, int col, vector<bool> &rows, vector<bool> &ld, vector<bool> &rd);
    void print(vector<vector<char>> &board);
};

bool NQueens_BNB::isSafe(int row, int col, vector<bool> rows, vector<bool> ld, vector<bool> rd)
{
    if (rows[row] == true || ld[row + col] == true || rd[col - row + n - 1] == true)
    {
        return false;
    }
    return true;
}
bool NQueens_BNB::solve(vector<vector<char>> &board, int col, vector<bool> &rows, vector<bool> &ld, vector<bool> &rd)
{
    if (col >= n)
    {
        return true;
    }
    for (int i = 0; i < n; i++)
    {
        if (isSafe(i, col, rows, ld, rd))
        {
            rows[i] = true;
            ld[i + col] = true;
            rd[col - i + n - 1] = true;
            board[i][col] = 'Q';
            if (solve(board, col + 1, rows, ld, rd))
            {
                return true;
            }
            // backtracking now
            rows[i] = false;
            ld[i + col] = false;
            rd[col - i + n - 1] = false;
            board[i][col] = '-';
        }
    }
    return false;
}
void NQueens_BNB::print(vector<vector<char>> &board)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
int main()
{
    cout << "Enter N: " << endl;
    int n;
    cin >> n;
    NQueens_BNB nq(n);
    vector<vector<char>> board(n, vector<char>(n, '-'));
    vector<bool> rows(n, false);
    vector<bool> ld(2 * n - 1, false);
    vector<bool> rd(2 * n - 1, false);
    bool ans = nq.solve(board, 0, rows, ld, rd);
    if (ans)
    {
        nq.print(board);
    }
    else
    {
        cout << "Solution Does Not Exist" << endl;
    }
}