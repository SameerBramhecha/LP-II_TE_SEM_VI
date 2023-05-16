#include <bits/stdc++.h>
using namespace std;
class RSA
{
    long long p, q, n, phin, e, d, c, m;

public:
    long long gcd(long long, long long);
    bool isPrime(long long);
    void acceptPrimes();
    void generateKey();
    void encdec();
};
long long RSA::gcd(long long a, long long b)
{
    return (b == 0) ? a : gcd(b, a % b);
}
bool RSA::isPrime(long long a)
{
    if (a <= 1)
    {
        return false;
    }
    else
    {
        for (int i = 2; i * i <= a; i++)
        {
            if (a % i == 0)
            {
                return false;
            }
        }
        return true;
    }
}
void RSA::acceptPrimes()
{
l1:
    cout << "Enter Prime p" << endl;
    cin >> p;
    if (!isPrime(p))
    {
        cout << "p is not prime\n please enter a prime number" << endl;
        goto l1;
    }
l2:
    cout << "Enter Prime q" << endl;
    cin >> q;
    if (!isPrime(q))
    {
        cout << "q is not prime\n please enter a prime number" << endl;
        goto l2;
    }
}
void RSA::generateKey()
{
    n = p * q;
    cout << "n: " << n << endl;
    phin = (p - 1) * (q - 1);
    cout << "phin: " << phin << endl;
    e = 2;
    for (; e < phin; e++)
    {
        if (gcd(e, phin) == 1)
        {
            break;
        }
    }
    cout << "e: " << e << endl;
    long long k = 0;
    for (;; k++)
    {
        if ((1 + (k * phin)) % e == 0)
        {
            break;
        }
    }
    d = (1 + (k * phin)) / e;
    d = fmod(d, n);
    cout << "d: " << d << endl;
    cout << "Public key: { " << e << "," << n << "}" << endl;
    cout << "Private key: { " << d << "," << n << "}" << endl;
}

void RSA::encdec()
{
    cout << "Enter message to be encrypted: " << endl;
    cin >> m;
    c = pow(m, e);
    c = fmod(c, n);
    long long pt = pow(c, d);
    pt = fmod(pt, n);
    cout << "Encrypted Message: " << c << endl;
    cout << "Decrypted Message: " << pt << endl;
}
int main()
{
    RSA r;
    r.acceptPrimes();
    r.generateKey();
    r.encdec();
    return 0;
}