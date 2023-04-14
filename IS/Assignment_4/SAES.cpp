// SIMPLIFIED AES ALGORITHM
#include <bits/stdc++.h>
using namespace std;

class SAES
{
    map<string, map<string, string>> sencrypt;
    map<string, map<string, string>> sdecrypt;
    vector<string> keys;
    vector<vector<int>> enc;
    vector<vector<int>> dec;

public:
    SAES()
    {
        sencrypt["00"]["00"] = "1001";
        sencrypt["00"]["01"] = "0100";
        sencrypt["00"]["10"] = "1010";
        sencrypt["00"]["11"] = "1011";

        sencrypt["01"]["00"] = "1101";
        sencrypt["01"]["01"] = "0001";
        sencrypt["01"]["10"] = "1000";
        sencrypt["01"]["11"] = "0101";

        sencrypt["10"]["00"] = "0110";
        sencrypt["10"]["01"] = "0010";
        sencrypt["10"]["10"] = "0000";
        sencrypt["10"]["11"] = "0011";

        sencrypt["11"]["00"] = "1100";
        sencrypt["11"]["01"] = "1110";
        sencrypt["11"]["10"] = "1111";
        sencrypt["11"]["11"] = "0111";

        sdecrypt["00"]["00"] = "1010";
        sdecrypt["00"]["01"] = "0101";
        sdecrypt["00"]["10"] = "1001";
        sdecrypt["00"]["11"] = "1011";

        sdecrypt["01"]["00"] = "0001";
        sdecrypt["01"]["01"] = "0111";
        sdecrypt["01"]["10"] = "1000";
        sdecrypt["01"]["11"] = "1111";

        sdecrypt["10"]["00"] = "0110";
        sdecrypt["10"]["01"] = "0000";
        sdecrypt["10"]["10"] = "0010";
        sdecrypt["10"]["11"] = "0011";

        sdecrypt["11"]["00"] = "1100";
        sdecrypt["11"]["01"] = "0100";
        sdecrypt["11"]["10"] = "1101";
        sdecrypt["11"]["11"] = "1110";

        enc = {{1, 4},
               {4, 1}};

        dec = {{9, 2},
               {2, 9}};
    }
    void keygeneration(string key);
    int gf24(int, int);
    string xorop(string a, string b);
    string rotnibble(string a);
    string subnibble(string a, bool flag);
    string encrypt(string pt);
    string decrypt(string ct);
    string matmulpt(vector<vector<int>>, int[2][2]);
    int binarytodecimal(string a);
    string decToBinary(int);
};

string SAES::decToBinary(int n)
{
    string ans = "";
    // Size of an integer is assumed to be 3 bits
    for (int i = 3; i >= 0; i--)
    {
        int k = n >> i;
        if (k & 1)
            ans += "1";
        else
            ans += "0";
    }
    return ans;
}

int SAES::binarytodecimal(string a)
{
    int value = 0;
    int indexCounter = 0;
    for (int i = a.length() - 1; i >= 0; i--)
    {
        if (a[i] == '1')
        {
            value += pow(2, indexCounter);
        }
        indexCounter++;
    }
    return value;
}
string SAES::rotnibble(string a)
{
    string ans = "";
    for (int i = 4; i < 8; i++)
    {
        ans += a[i];
    }
    for (int i = 0; i < 4; i++)
    {
        ans += a[i];
    }
    return ans;
}
string SAES::subnibble(string a, bool flag)
{
    string ans, n1, n2;
    for (int i = 0; i < 4; i++)
    {
        n1 += a[i];
    }
    for (int i = 4; i < 8; i++)
    {
        n2 += a[i];
    }
    if (flag)
    {
        // encrpytion
        string r = n1.substr(0, 2);
        string c = n1.substr(2);
        ans += sencrypt[r][c];
        r = n2.substr(0, 2);
        c = n2.substr(2);
        ans += sencrypt[r][c];
        return ans;
    }
    else
    {
        // decryption
        string r = n1.substr(0, 2);
        string c = n1.substr(2);
        ans += sdecrypt[r][c];
        r = n2.substr(0, 2);
        c = n2.substr(2);
        ans += sdecrypt[r][c];
        return ans;
    }
}
string SAES::xorop(string a, string b)
{
    string ans = "";
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == b[i])
        {
            ans += "0";
        }
        else
        {
            ans += "1";
        }
    }
    return ans;
}
void SAES::keygeneration(string key)
{
    string w0, w1, w2, w3, w4, w5;
    w0 = key.substr(0, 8);
    w1 = key.substr(8);
    // cout<<w0<<" "<<w1<<endl;
    w2 = xorop(w0, "10000000");
    w2 = xorop(w2, subnibble(rotnibble(w1), true));
    w3 = xorop(w1, w2);
    w4 = xorop(w2, "00110000");
    w4 = xorop(w4, subnibble(rotnibble(w3), true));
    w5 = xorop(w3, w4);
    string k1, k2, k3;
    k1 = w0 + w1;
    k2 = w2 + w3;
    k3 = w4 + w5;
    keys.push_back(k1);
    keys.push_back(k2);
    keys.push_back(k3);
    for (int i = 0; i < 3; i++)
    {
        cout << "Key " << i + 1 << ": " << keys[i] << endl;
    }
}

string SAES::matmulpt(vector<vector<int>> a, int b[2][2])
{
    vector<string> res;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            //
            vector<int> x;
            for (int k = 0; k < 2; k++)
            {
                //
                x.push_back(gf24(a[i][k], b[k][j]));
            }
            res.push_back(xorop(decToBinary(x[0]), decToBinary(x[1])));
        }
    }
    string ans = res[0] + res[2] + res[1] + res[3];
    return ans;
}

int SAES::gf24(int a, int b)
{
    int product = 0; // the product of the multiplication
    while (b > 0)
    {
        if ((b & 1) != 0)
        { // if b is odd then add the first num i.e a into product result
            product = product ^ a;
            // cout<<product<<endl;
        }
        a = a << 1; // double first num
        // cout<<a<<endl;

        // if a overflows beyond 4th bit
        if ((a & (1 << 4)) != 0)
        {
            a = a ^ 0b10011; // XOR with irreducible polynomial with high term eliminated
            // POLYNOMIAL = x^4 + x + 1
            // cout<<"XOR "<<a<<endl;
        }
        b = b >> 1; // reduce second num
        // cout<<b<<endl;
    }
    return product;
}

string SAES::encrypt(string pt)
{
    cout << "ENCRYPTION --> " << endl;

    // Step 1 --> Add Round key
    string ct = xorop(pt, keys[0]);
    cout << "Step 1 : " << ct << endl;
    // Step 2 --> Substitute Nibbles
    ct = subnibble(ct.substr(0, 8), true) + subnibble(ct.substr(8), true);
    cout << "Step 2 : " << ct << endl;
    // Step 3 --> Shift Rows
    // string ct1 = "";
    ct = ct.substr(0, 4) + ct.substr(12, 4) + ct.substr(8, 4) + ct.substr(4, 4);
    cout << "Step 3 : " << ct << endl;
    // Step 4 --> Mix Columns
    int mat[2][2];
    mat[0][0] = binarytodecimal(ct.substr(0, 4));
    mat[1][0] = binarytodecimal(ct.substr(4, 4));
    mat[0][1] = binarytodecimal(ct.substr(8, 4));
    mat[1][1] = binarytodecimal(ct.substr(12, 4));
    // cout<<"0 0 "<<mat[0][0]<<endl;
    // cout<<"0 1 "<<mat[0][1]<<endl;
    // cout<<"1 0 "<<mat[1][0]<<endl;
    // cout<<"1 1 "<<mat[1][1]<<endl;
    ct = matmulpt(enc, mat);
    cout << "Step 4 : " << ct << endl;
    // Step 5 --> Add Round key
    ct = xorop(ct, keys[1]);
    cout << "Step 5 : " << ct << endl;
    // Step 6 --> Substitute Nibbles
    ct = subnibble(ct.substr(0, 8), true) + subnibble(ct.substr(8), true);
    cout << "Step 6 : " << ct << endl;
    // Step 7 --> Shift Rows
    ct = ct.substr(0, 4) + ct.substr(12, 4) + ct.substr(8, 4) + ct.substr(4, 4);
    cout << "Step 7 : " << ct << endl;
    // Step 8 --> Add Round key
    ct = xorop(ct, keys[2]);
    cout << "Step 8 : " << ct << endl;

    cout << "Cipher Text :: " << ct << endl;
    return ct;
}

string SAES::decrypt(string ct)
{
    cout << "DECRYPTION -->" << endl;
    // Step 1 --> Add Round Key 3
    string pt = xorop(ct, keys[2]);
    cout << "Step 1 : " << pt << endl;
    // Step 2 --> Inverse Shifts Rows
    pt = pt.substr(0, 4) + pt.substr(12, 4) + pt.substr(8, 4) + pt.substr(4, 4);
    cout << "Step 2 : " << pt << endl;
    // Step 3 --> Inverse Nibble Substitution
    pt = subnibble(pt.substr(0, 8), false) + subnibble(pt.substr(8), false);
    cout << "Step 3 : " << pt << endl;
    // Step 4 --> Add Round Key 2
    pt = xorop(pt, keys[1]);
    cout << "Step 4 : " << pt << endl;
    // Step 5 --> Inverse Mix Columns
    int mat[2][2];
    mat[0][0] = binarytodecimal(pt.substr(0, 4));
    mat[1][0] = binarytodecimal(pt.substr(4, 4));
    mat[0][1] = binarytodecimal(pt.substr(8, 4));
    mat[1][1] = binarytodecimal(pt.substr(12, 4));
    pt = matmulpt(dec, mat);
    cout << "Step 5 : " << pt << endl;
    // Step 6 --> Inverse Shift Rows
    pt = pt.substr(0, 4) + pt.substr(12, 4) + pt.substr(8, 4) + pt.substr(4, 4);
    cout << "Step 6 : " << pt << endl;
    // Step 7 --> Inverse Nibble Substitution
    pt = subnibble(pt.substr(0, 8), false) + subnibble(pt.substr(8), false);
    cout << "Step 7 : " << pt << endl;
    // Step 8 --> Add Round Key 1
    pt = xorop(pt, keys[0]);
    cout << "Step 8 : " << pt << endl;

    cout << "Plain Text :: " << pt << endl;
    return pt;
}

int main()
{
    SAES s;
    string key = "0100101011110101";
    s.keygeneration(key);
    string pt = "1101011100101000";
    string ct = s.encrypt(pt);
    string rpt = s.decrypt(ct);
    if (pt == rpt)
    {
        cout << "Decryption Successfull !! \nAbhi Maje Karo.. Jyada Load Mat Lo" << endl;
    }
    return 0;
}
