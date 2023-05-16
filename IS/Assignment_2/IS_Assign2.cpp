#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;

class Transposition
{
public:
    string encrypt(string, string);
    string decrypt(string, string);
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

string Transposition::decrypt(string key, string ct)
{
    int n = key.length();
    int lct = ct.length();
    int row = lct / n;
    int col = n;
    char a[row][col];
    int k = 0;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            a[j][i] = ct[k];
            k++;
        }
    }
    // printing matrix
    cout << "Preparing the plaintext: " << endl;
    for (int j = 0; j < row; j++)
    {
        for (int k = 0; k < col; k++)
        {
            cout << a[j][k] << " ";
        }
        cout << endl;
    }
    // rearranging the matrix
    char pt[row][col];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < row; j++)
        {
            pt[j][i] = a[j][(key[i] - '1')];
        }
    }

    //
    for (int j = 0; j < row; j++)
    {
        for (int k = 0; k < col; k++)
        {
            cout << pt[j][k] << " ";
        }
        cout << endl;
    }
    string plntxt = "";
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            plntxt += pt[i][j];
        }
    }
    return plntxt;
}

int main()
{
    Transposition t;
    string pt, key;
    cout << "Enter plain text: " << endl;
    getline(cin, pt);
    cout << "Enter Key: " << endl;
    cin >> key;
    string ct = t.encrypt(key, pt);
    cout << "Cipher Text:--> " << ct << endl;
    cout << "Starting Decryption:--> " << endl;
    cout << "Plain Text :-->" << endl;
    cout << t.decrypt(key, ct) << endl;
    return 0;
}

/*
TEST CASE 1 ->
PT -> attack postponed until two am
Key -> 4312567
CT -> TTNAAPTMTSUOAODWCOIAKNLBPETC

TEST CASE 2 -->
PT -> we are the best
KEY -> 421635
CT -> abeeeswhttre

*/
