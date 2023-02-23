
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <list>
#include <set>
#define lp while
#define rep(i, a, b) for (int i = a; i < b; i++)
#define sort(a) sort(a.begin(), a.end())
#define nl << endl
using namespace std;
class Node
{
public:
    string name;
    int weight;
    Node(string name, int weight)
    {
        this->name = name;
        this->weight = weight;
    }
};
class Graph
{
public:
    map<string, vector<Node>> adj;
    map<string, int> H;
    Graph(map<string, vector<Node>> adjac_lis)
    {
        adj = adjac_lis;
    }
    vector<Node> get_neighbors(string name)
    {
        return adj.at(name);
    }
    int h(string v)
    {
        return H[v];
    }
    void a_star(string source, string destination)
    {
        /*
        open_list is a list of nodes which have been visited, but who's neighbors
        haven't all been inspected, starts off with the start node
        closed_list is a list of nodes which have been visited
        and who's neighbors have been inspected
        */
        set<string> open_list, closed_list;
        open_list.insert(source);
        // g contains current distances from start_node to all other nodes
        // the default value (if it's not found in the map) is +infinity
        map<string, int> g;
        g[source] = 0;
        // parents contains an adjacency map of all nodes
        map<string, string> parent;
        parent[source] = source;
        while (open_list.size() > 0)
        {
            string n = "";
            // find a node with lowest f(n)
            for (string v : open_list)
            {
                if (n == "" || (g[v] + h(v)) < (g[n] + h(n)))
                {
                    n = v;
                }
            }
            if (n == "")
            {
                cout << "NO PATH EXISTS!!" << endl;
                return;
            }
            // if the current node is the stop_node
            // then we begin reconstructin the path from it to the start_node
            if (n == destination)
            {
                vector<string> recons_path;
                while (parent[n] != n)
                {
                    recons_path.push_back(n);
                    n = parent[n];
                }
                recons_path.push_back(n);
                reverse(recons_path.begin(), recons_path.end());
                cout << "Path found: " nl;
                for (string x : recons_path)
                {
                    cout << x << " ";
                }
                return;
            }
            // for all neighbors of the current node do
            for (Node v : get_neighbors(n))
            {
                // if the current node isn't in both open_list and closed_list
                // add it to open_list and note n as it's parent
                if (!(closed_list.count(v.name)) && !(open_list.count(v.name)))
                {
                    open_list.insert(v.name);
                    parent[v.name] = n;
                    g[v.name] = g.at(n) + v.weight;
                }
                else
                {
                    if (g[v.name] > g[n] + v.weight)
                    {
                        g[v.name] = g.at(n) + v.weight;
                        parent[v.name] = n;
                    }
                    if (closed_list.count(v.name))
                    {
                        closed_list.erase(v.name);
                        open_list.insert(v.name);
                    }
                }
            }
            // remove n from the open_list, and add it to closed_list
            // # because all of his neighbors were inspected
            open_list.erase(n);
            closed_list.insert(n);
        }
    }
};
int main()
{
    map<string, vector<Node>> adjac_lis;
    int n;
    cout << "Enter number of nodes: " nl;
    cin >> n;
    cout << "Enter The Graph: " nl;
    for (int i = 0; i < 22; i++)
    {
        string a, b;
        int w;
        cin >> a >> b >> w;
        Node obj(b, w);
        adjac_lis[a].push_back(obj);
    }
    Graph g(adjac_lis);
    cout << "Enter Heuristic distances: " nl;
    rep(i, 0, n)
    {
        string name;
        int heuristic;
        cin >> name >> heuristic;
        g.H[name] = heuristic;
    }
    g.a_star("A", "B");
    return 0;
}

/*
Graph: -
A Z 75
A T 118
A S 140
Z O 71
O S 151
T L 111
L M 70
M D 75
D C 120
C R 146
R S 80
S F 77
F B 211
R P 97
P B 101
B G 90
B U 85
U V 142
U H 98
H E 86
V I 92
I N 87


Heuristic: -
A 366
B 0
C 160
D 242
E 161
F 176
G 77
H 151
I 226
L 244
M 241
N 234
O 380
P 100
R 193
S 253
T 329
U 80
V 199
Z 374
*/