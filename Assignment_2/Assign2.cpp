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

class Node{
    
    public:
    string name;
    int weight;
        Node(string name,int weight){
            this->name = name;
            this->weight = weight;
        }
};
class Graph{
    public: 
    map<string,vector<Node>> adj;
    map<string,int> H;
    Graph(map<string,vector<Node>> adj_list){
        adj = adj_list;
    }
    vector<Node> get_neighbors(string v){
        return adj[v];
    }
    int h(string v){
        return H[v];
    }
    void a_star(string source,string destination){
        set<string> open_list,closed_list;
        open_list.insert(source);
        map<string,int> g;
        g[source] = 0;
        map<string,string> parent;
        parent[source] = source;
        while(open_list.size()>0){
            string n = "";
            int f = 0;
            for(string v:open_list){ 
                if(n=="" || (g[v]+h(v)) < (g[n]+h(n))){
                    n = v;
                    f = g[v] + h(v);
                }
            }
            if(n==""){
                cout<<"NO PATH EXISTS" nl;
                return;
            }
            if(n==destination){
                vector<string> recons_path;
                while(parent[n]!=n){
                    recons_path.push_back(n);
                    n = parent[n];
                }
                recons_path.push_back(n);
                reverse(recons_path.begin(),recons_path.end());
                cout << "Path Exists: " nl;
                for(auto v:recons_path){
                    cout << v <<" ";
                }
                cout nl;
                cout<<"Path Cost: " nl;
                cout << f nl;
                return;

            }
            for(Node v: get_neighbors(n)){
                if(!closed_list.count(v.name) && !open_list.count(v.name)){
                    open_list.insert(v.name);
                    parent[v.name] = n;
                    g[v.name] = g[n] + v.weight;
                }
                else{
                    if(g[v.name] > (g[n] + v.weight)){
                        g[v.name] = g[n] + v.weight;
                        parent[v.name] = n;
                    }
                    if(closed_list.count(v.name)){
                        closed_list.erase(v.name);
                        closed_list.insert(v.name);
                    }
                }
            }
            open_list.erase(n);
            closed_list.insert(n);
        }
    }
};
int main(){
    map<string, vector<Node>> adj_list;
    int n,e;
    cout<<"Enter Number of Nodes: " nl;
    cin>>n;
    cout<<"Enter number of edges: " nl;
    cin>>e;
    cout<<"Enter the Graph: " nl;
    for(int i=0;i<e;i++){
        string a,b;
        int w;
        cin>>a>>b>>w;
        Node obj(b,w);
        adj_list[a].push_back(obj);
    }
    Graph g(adj_list);
    cout<<"Enter Heuristic Distances: " nl;
    rep(i,0,n){
        string name;
        int heuristic;
        cin>>name>>heuristic;
        g.H[name] = heuristic;
    }
    string source,destination;
    cout<<"Enter source Node: " nl;
    cin>>source;
    cout<<"Enter Destination Node: " nl;
    cin>>destination;
    g.a_star(source,destination);
    return 0;
}

/*
Input 1 -->
n = 20
e = 22
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
C P 138
R S 80
S F 99
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

Input 2 -->
Graph: -
n = 7
e = 9
A B 4
A C 3
B E 12
B F 5
C E 10
C D 7
D E 2
F Z 16
E Z 5
Heuristic: -
A 14
B 12
C 11
D 6
E 4
F 11
Z 0
*/
