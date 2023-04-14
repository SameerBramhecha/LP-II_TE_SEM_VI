#include <bits/stdc++.h>
using namespace std;
class SDES
{
    string k1, k2;
    // All sequences of operation are 0-indexed
    string p10 = "2416390875";
    string kp8 = "52637498";
    string p8 = "15203746";
    string p4 = "1320";
    string ipr = "30246175";
    string ep = "30121230";
    int n = 2;
    vector<string> key;
    map<string, map<string, string>> sbx0;
    map<string, map<string, string>> sbx1;

public:
    string xorop(string a, string b);      // function to XOR two strings
    void keygenerate(string);              // function to generate round keys k1 and k2
    string roundfunc(string, string, int); // function to simulate rounds of encryption and decryptiion
    string encrypt(string pt);             // Encryption function
    string decrypt(string);                // Decryption function
    string lcs(string, int);               // function to perform left circular shift
    string sbox0(string a);                // function to return s0 box value
    string sbox1(string a);                // function to return s1 box value
};
string SDES::sbox0(string a)
{
    sbx0["00"]["00"] = "01";
    sbx0["00"]["01"] = "00";
    sbx0["00"]["10"] = "11";
    sbx0["00"]["11"] = "10";
    sbx0["01"]["00"] = "11";
    sbx0["01"]["01"] = "10";
    sbx0["01"]["10"] = "01";
    sbx0["01"]["11"] = "00";
    sbx0["10"]["00"] = "00";
    sbx0["10"]["01"] = "10";
    sbx0["10"]["10"] = "01";
    sbx0["10"]["11"] = "11";
    sbx0["11"]["00"] = "11";
    sbx0["11"]["01"] = "01";
    sbx0["11"]["10"] = "11";
    sbx0["11"]["11"] = "10";
    string r = a.substr(0, 1) + a.substr(3);
    string c = a.substr(1, 2);
    string ret = sbx0[r][c];
    return ret;
}
string SDES::sbox1(string a)
{
    sbx1["00"]["00"] = "00";
    sbx1["00"]["01"] = "01";
    sbx1["00"]["10"] = "10";
    sbx1["00"]["11"] = "11";
    sbx1["01"]["00"] = "10";
    sbx1["01"]["01"] = "00";
    sbx1["01"]["10"] = "01";
    sbx1["01"]["11"] = "11";
    sbx1["10"]["00"] = "11";
    sbx1["10"]["01"] = "00";
    sbx1["10"]["10"] = "01";
    sbx1["10"]["11"] = "00";
    sbx1["11"]["00"] = "10";
    sbx1["11"]["01"] = "01";
    sbx1["11"]["10"] = "00";
    sbx1["11"]["11"] = "11";
    string r = a.substr(0, 1) + a.substr(3);
    string c = a.substr(1, 2);
    string ret = sbx1[r][c];
    return ret;
}
string SDES::xorop(string a, string b)
{
    string res = "";
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] == b[i])
        {
            res += '0';
        }
        else
        {
            res += '1';
        }
    }
    return res;
}
string SDES::lcs(string kc, int nb)
{
    string a = kc;
    for (int i = 0; i < nb; i++)
    {
        char c = a[0];
        a = a.substr(1);
        a += c;
    }
    return a;
}
void SDES::keygenerate(string k)
{
    k1 = "";
    k2 = "";
    string temp = k;
    // Applying p-10 on k
    for (int i = 0; i < temp.length(); i++)
    {
        k[i] = temp[(p10[i] - '0')];
    }
    cout << "P-10 : " << k << endl;
    string kl, kr;
    // splitting in kl and kr
    kl = k.substr(0, 5);
    kr = k.substr(5);
    cout << "KL : " << kl << endl;
    cout << "KR : " << kr << endl;
    // left circular shift by one bit;
    kl = lcs(kl, 1);
    kr = lcs(kr, 1);
    cout << "After lcs of Kl and Kr by 1-bit: " << endl;
    cout << "KL : " << kl << endl;
    cout << "KR : " << kr << endl;
    // applying p-8 on kl+kr
    temp = kl + kr;
    for (int i = 0; i < 8; i++)
    {
        k1 += temp[(kp8[i] - '0')];
    }
    cout << "Key 1 : " << k1 << endl;
    // generating k2
    // lcs on kl & kr by two bits;
    kl = lcs(kl, 2);
    kr = lcs(kr, 2);
    cout << "After lcs of Kl and Kr by 2-bit: " << endl;
    cout << "KL : " << kl << endl;
    cout << "KR : " << kr << endl;
    temp = kl + kr;
    // performing p-8
    for (int i = 0; i < 8; i++)
    {
        k2 += temp[(kp8[i] - '0')];
    }
    cout << "Key 2 : " << k2 << endl;
    // saving the keys in vector to use during encryption and decryption
    key.push_back(k1);
    key.push_back(k2);
}

string SDES::roundfunc(string pt, string key, int round)
{
    //  split pt in l and r
    string l = "";
    for (int i = 0; i < 4; i++)
    {
        l += pt[i];
    }
    string r = "";
    for (int i = 4; i < 8; i++)
    {
        r += pt[i];
    }
    cout << "B : " << l << " " << r << endl;
    // Expansion permutation of r i.e. EP(r)
    string epr = "";
    for (int i = 0; i < r.length() * 2; i++)
    {
        epr += r[ep[i] - '0'];
    }
    cout << "C : " << epr << endl;
    // xor ep(r) with k1
    epr = xorop(epr, key);
    cout << "D : " << epr << endl;
    // splitting in l1 and r1
    string l1 = "";
    for (int i = 0; i < 4; i++)
    {
        l1 += epr[i];
    }
    string r1 = "";
    for (int i = 4; i < 8; i++)
    {
        r1 += epr[i];
    }
    cout << "E : " << l1 << " " << r1 << endl;
    // Finding s box values of l1 and r1
    string s0 = sbox0(l1);
    string s1 = sbox1(r1);
    cout << "F : " << s0 << " " << s1 << endl;
    // performing P-4
    string temp = s0 + s1;
    string temp2 = temp;
    for (int i = 0; i < temp2.length(); i++)
    {
        temp[i] = temp2[p4[i] - '0'];
    }
    cout << "G : " << temp << endl;
    // Xor o/p of P-4 with l
    temp = xorop(temp, l);
    cout << "H : " << temp << endl;
    // Combine with r
    temp += r;
    cout << "I : " << temp << endl;
    // Split into l2 and r2
    string l2 = "";
    for (int i = 0; i < 4; i++)
    {
        l2 += temp[i];
    }
    string r2 = "";
    for (int i = 4; i < 8; i++)
    {
        r2 += temp[i];
    }
    cout << "J : " << l2 << " " << r2 << endl;
    // If it is the last round, do not swap
    // Else it is not the last round, swap l2 and r2
    if (round != n - 1)
    {
        temp = r2 + l2;
    }
    else
    {
        temp = l2 + r2;
    }
    return temp;
}
string SDES::encrypt(string pt)
{
    string temp = pt;
    for (int i = 0; i < temp.length(); i++)
    {
        pt[i] = temp[(p8[i] - '0')];
    }
    cout << "A : " << pt << endl;
    string rop = pt;
    for (int i = 0; i < n; i++)
    {
        rop = roundfunc(rop, key[i], i);
        cout << "Round Output : " << rop << endl;
    }

    temp = rop;
    for (int i = 0; i < rop.length(); i++)
    {
        rop[i] = temp[ipr[i] - '0'];
    }
    cout << "Encrpytion: " << rop << endl;
    return rop;
}
string SDES::decrypt(string ct)
{
    string temp = ct;
    for (int i = 0; i < temp.length(); i++)
    {
        ct[i] = temp[(p8[i] - '0')];
    }
    cout << "A : " << ct << endl;
    string rop = ct;
    for (int i = 0; i < n; i++)
    {
        rop = roundfunc(rop, key[n - i - 1], i);
        cout << "Round Output : " << rop << endl;
    }

    temp = rop;
    for (int i = 0; i < rop.length(); i++)
    {
        rop[i] = temp[ipr[i] - '0'];
    }
    cout << "Decrpytion: " << rop << endl;
    return rop;
}
int main()
{
    SDES s;
    string key = "1010000010";
    s.keygenerate(key);
    string pt = "01101101";
    string ct = s.encrypt(pt);
    cout << endl;
    cout << "Starting Decrpytion" << endl;
    cout << endl;
    string pta = s.decrypt(ct);
    if (pt == pta)
    {
        cout << "Algorithm Worked Successfully!! \nChill Life!!!!.. Mouj Karo" << endl;
    }
    return 0;
}