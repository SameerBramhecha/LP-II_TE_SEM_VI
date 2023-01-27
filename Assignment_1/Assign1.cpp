/*
Assignment Number 1:
Implement DFS and BFS to search vertices in a graph in a recursive manner.
*/

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <list>
#include <numeric>
#include <utility>
#include <queue>
#include <set>
#define ll long long
#define lp while
#define rep(i, a, b) for (int i = a; i < b; i++)
#define sort(a) sort(a.begin(), a.end())
#define nl << endl
using namespace std;
class Graph
{
    int **gr;
    int n;
    int *visited1;
    int *visited2;
    queue<int> q;

public:
    Graph(int n)
    {
        this->n = n;
        gr = new int *[n];
        visited1 = new int[n];
        visited2 = new int[n];
        rep(i, 0, n)
        {
            gr[i] = new int[n];
            visited1[i] = 0;
            visited2[i] = 0;
            rep(j, 0, n)
            {
                gr[i][j] = 0;
            }
        }
    }
    void create(int edge);
    void display();
    void dfsr(int);
    void bfsr(int);
};
void Graph::create(int edge) // function to create a graph
{
    int s, d;
    rep(i, 0, edge)
    {
        cout << "Enter Source " << i + 1 nl;
        cin >> s;
        cout << "Enter Destination " << i + 1 nl;
        cin >> d;
        gr[s][d] = 1;
        gr[d][s] = 1;
    }
}
void Graph::display() // function to display a graph
{
    rep(i, 0, n)
    {
        rep(j, 0, n)
        {
            cout << gr[i][j] << " ";
        }
        cout nl;
    }
}
void Graph::dfsr(int v1) // function for Depth First Traversal
{
    cout << v1 << " ";
    visited1[v1] = 1;
    rep(v2, 0, n)
    {
        if (gr[v1][v2] == 1 && visited1[v2] == 0)
        {
            dfsr(v2);
        }
    }
}
void Graph::bfsr(int v1) // function for Breadth First Traversal
{
    cout << v1 << " ";
    visited2[v1] = 1;

    rep(v2, 0, n)
    {
        if (gr[v1][v2] == 1 && visited2[v2] == 0)
        {
            q.push(v2);
            visited2[v2] = 1;
        }
    }
    if (q.empty())
    {
        return;
    }
    int x = q.front();
    q.pop();
    bfsr(x);
}
int main()
{
    int v, e;
    cout << "Enter number of vertices: " nl;
    cin >> v;
    cout << "Enter number of edges: " nl;
    cin >> e;
    Graph g(v);
    g.create(e);
    while (true)
    {
        cout << "1. Display Graph" nl;
        cout << "2. DFS" nl;
        cout << "3. BFS" nl;
        cout << "4. Exit" nl;
        cout << "Enter Choice" nl;
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Entered Graph is: " nl;
            g.display();
            break;
        case 2:
            cout << "Enter node to start dfs from: " nl;
            int n1;
            cin >> n1;
            g.dfsr(n1);
            cout nl;
            break;
        case 3:
            cout << "Enter node to start bfs from: " nl;
            int n2;
            cin >> n2;
            g.bfsr(n2);
            cout nl;
            break;
        case 4:
            return 0;
        default:
            cout << "Enter correct choice!!" nl;
            break;
        }
    }
    return 0;
}
