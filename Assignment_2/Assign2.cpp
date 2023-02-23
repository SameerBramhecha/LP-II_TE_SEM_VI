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
    map<string, vector<Node>> adj;
    map<string, int> H;

public:
    Graph(map<string, vector<Node>> adjac_lis)
    {
        adj = adjac_lis;
        H["A"] = 11;
        H["B"] = 6;
        H["C"] = 99;
        H["D"] = 1;
        H["E"] = 7;
        H["G"] = 0;
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
    cout << "Enter The Graph: " nl;
    for (int i = 0; i < 6; i++)
    {
        string a, b;
        cin >> a >> b;
        int w;
        cin >> w;
        Node obj(b, w);
        adjac_lis[a].push_back(obj);
    }
    Graph g(adjac_lis);
    g.a_star("A", "G");
    return 0;
}

/*
A B 2
A E 3
B C 1
B G 9
D G 1
E D 6
*/