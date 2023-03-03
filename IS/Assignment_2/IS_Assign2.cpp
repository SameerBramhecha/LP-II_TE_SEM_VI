#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;

class Transposition
{
public:
    string encrypt(string, string);
};

string Transposition::encrypt(string key, string pt)
{
    int n = key.length();
    int lpt;
    pt.erase(remove(pt.begin(), pt.end(), ' '), pt.end());
    lpt = pt.length();
    int x = lpt;
    if (x % n == 0)
    {
        x /= n;
    }
    else
    {
        int c = x % n;
        x = x / n;
        x += 1;
        for (int i = 0; i < c; i++)
        {
            pt.push_back('a' + i);
        }
    }
    char a[x][n];
    int i = 0;
    for (int j = 0; j < x; j++)
    {
        for (int k = 0; k < n; k++)
        {
            a[j][k] = pt[i];
            i++;
        }
    }
    vector<string> ed(n, "");
    string s = "";
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < x; k++)
        {
            s += a[k][j];
        }
        ed[(key[j] - '0') - 1] = s;
        s = "";
    }
    // printing matrix
    cout << "Preparing the plaintext: " << endl;
    for (int j = 0; j < x; j++)
    {
        for (int k = 0; k < n; k++)
        {
            cout << a[j][k] << " ";
        }
        cout << endl;
    }
    // preparing cipher text
    string q = "";
    for (int i = 0; i < ed.size(); i++)
    {
        q += ed[i];
    }
    cout << "Cipher Text: " << endl;
    return q;
}

int main()
{
    Transposition t;
    string pt, key;
    cout << "Enter plain text: " << endl;
    getline(cin, pt);
    cout << "Enter Key: " << endl;
    cin >> key;
    cout << t.encrypt(key, pt) << endl;
    return 0;
}
