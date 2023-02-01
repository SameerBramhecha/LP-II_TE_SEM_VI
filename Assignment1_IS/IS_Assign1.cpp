#include <bits/stdc++.h>
#include <iostream>
#include <string>
#define ll long long
#define lp while
#define rep(i, a, b) for (int i = a; i < b; i++)
#define sort(a) sort(a.begin(), a.end())
#define nl << endl
using namespace std;
class Assign1IS
{
    string s = "\\HelloWorld";
    public:
    int andop(char x);
    int orop(char x);
    int xorop(char x);
    void display();
};
void Assign1IS::display(){
    int len = s.length();
    rep(i,0,len){
        cout<<s[i]<<"(" << (int) s[i]<<")" nl;
        cout<<"AND: "<<andop(s[i]) nl;
        cout<<"OR: "<<orop(s[i]) nl;
        cout<<"XOR: "<<xorop(s[i]) nl;
    }
}
int Assign1IS::andop(char x){
    int a = (int) x;
    return (a&127);
}
int Assign1IS::orop(char x){
    int a = (int) x;
    return (a|127);
}
int Assign1IS::xorop(char x){
    int a = (int) x;
    return (a^127);
}

int main(){
    Assign1IS is;
    is.display();
    return 0;
}
