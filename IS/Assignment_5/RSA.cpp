#include <bits/stdc++.h>
using namespace std;
class RSA
{
    double p, q;
    double n, phin, e, d, m, c;

public:
    int gcd(int, int);
    bool isPrime(int);
    void acceptprimes();
    void generatekey();
    void encdec();
};
int RSA::gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}
bool RSA::isPrime(int a)
{
    if (a <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= a; i++)
    {
        if (a % i == 0)
        {
            return false;
        }
    }
    return true;
}
void RSA::acceptprimes()
{
l1:
    cout << "Enter 1st prime number p: " << endl;
    cin >> p;
    if (!isPrime(p))
    {
        cout << "p is not prime!!" << endl;
        goto l1;
    }
l2:

    cout << "Enter second prime number q: " << endl;
    cin >> q;
    if (!isPrime(q))
    {
        cout << "q is not prime!!" << endl;
        goto l2;
    }
    cout << p << " " << q << endl;
}

void RSA::generatekey()
{
    n = p * q;
    cout << "n = " << n << endl;
    phin = (p - 1) * (q - 1);
    cout << "phi(n) = " << phin << endl;
    e = 5;
    for (; e < phin; e++)
    {
        if (gcd(e, phin) == 1)
        {
            break;
        }
    }
    cout << "e: " << e << endl;
    double d1 = 1 / e;
    d = fmod(d1, phin);
    cout << "d: " << d << endl;

    cout << "Public Key : PU = {" << e << "," << n << "}" << endl;
    cout << "Private Key : PK = {" << d << "," << n << "}" << endl;
}
void RSA::encdec()
{
    cout << "Enter message to encrypt: " << endl;
    cin >> m;
    c = pow(m, e);
    double pt = pow(c, d);
    c = fmod(c, n);
    pt = fmod(pt, n);
    cout << "Encrypted Message: " << c << endl;
    cout << "Decrypted Message: " << pt << endl;
}
int main()
{
    RSA rsa;
    rsa.acceptprimes();
    rsa.generatekey();
    rsa.encdec();
    return 0;
}
