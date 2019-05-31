#include <cstdio>
#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int SIZE = 166;
const int N = 101;

struct BigInteger {
    int len, s[SIZE];
    BigInteger () {
        memset(s, 0, sizeof(s));
        len = 1;
    }
    BigInteger operator = (const char *num) { //`字符串赋值`
        memset(s, 0, sizeof(s));
        len = strlen(num);
        for(int i = 0; i < len; i++) s[i] = num[len - i - 1] - '0';
        return *this;
    }
    BigInteger operator = (const int num) { //int `赋值`
        memset(s, 0, sizeof(s));
        char ss[SIZE + 5];
        sprintf(ss, "%d", num);
        *this = ss;
        return *this;
    }
    BigInteger (int num) {
        *this = num;
    }
    BigInteger (char* num) {
        *this = num;
    }
    string str() const { //`转化成`string
        string res = "";
        for(int i = 0; i < len; i++) res = (char)(s[i] + '0') + res;
        if(res == "") res = "0";
        return res;
    }
    BigInteger clean() {
        while(len > 1 && !s[len - 1]) len--;
        return *this;
    }

    BigInteger operator + (const BigInteger& b) const {
        BigInteger c;
        c.len = 0;
        for(int i = 0, g = 0; g || i < max(len, b.len); i++) {
            int x = g;
            if(i < len) x += s[i];
            if(i < b.len) x += b.s[i];
            c.s[c.len++] = x % 10;
            g = x / 10;
        }
        return c.clean();
    }

    BigInteger operator - (const BigInteger& b) {
        BigInteger c;
        c.len = 0;
        for(int i = 0, g = 0; i < len; i++) {
            int x = s[i] - g;
            if(i < b.len) x -= b.s[i];
            if(x >= 0) g = 0;
            else {
                g = 1;
                x += 10;
            }
            c.s[c.len++] = x;
        }
        return c.clean();
    }

    BigInteger operator * (const int num) const {
        int c = 0, t;
        BigInteger pro;
        for(int i = 0; i < len; ++i) {
            t = s[i] * num + c;
            pro.s[i] = t % 10;
            c = t / 10;
        }
        pro.len = len;
        while(c != 0) {
            pro.s[pro.len++] = c % 10;
            c /= 10;
        }
        return pro.clean();
    }

    BigInteger operator * (const BigInteger& b) const {
        BigInteger c;
        for(int i = 0; i < len; i++) {
            for(int j = 0; j < b.len; j++) {
                c.s[i + j] += s[i] * b.s[j];
                c.s[i + j + 1] += c.s[i + j] / 10;
                c.s[i + j] %= 10;
            }
        }
        c.len = len + b.len + 1;
        return c.clean();
    }

    BigInteger operator / (const BigInteger &b) const {
        BigInteger c, f;
        for(int i = len - 1; i >= 0; --i) {
            f = f * 10;
            f.s[0] = s[i];
            while(f >= b) {
                f = f - b;
                ++c.s[i];
            }
        }
        c.len = len;
        return c.clean();
    }
    //`高精度取模`
    BigInteger operator % (const BigInteger &b) const{
        BigInteger r;
        for(int i = len - 1; i >= 0; --i) {
            r = r * 10;
            r.s[0] = s[i];
            while(r >= b) r = r - b;
        }
        r.len = len;
        return r.clean();
    }

    bool operator < (const BigInteger& b) const {
        if(len != b.len) return len < b.len;
        for(int i = len - 1; i >= 0; i--)
            if(s[i] != b.s[i]) return s[i] < b.s[i];
        return false;
    }
    bool operator > (const BigInteger& b) const {
        return b < *this;
    }
    bool operator <= (const BigInteger& b) const {
        return !(b < *this);
    }
    bool operator == (const BigInteger& b) const {
        return !(b < *this) && !(*this < b);
    }
    bool operator != (const BigInteger &b) const {
        return !(*this == b);
    }
    bool operator >= (const BigInteger &b) const {
        return *this > b || *this == b;
    }
    friend istream & operator >> (istream &in, BigInteger& x) {
        string s;
        in >> s;
        x = s.c_str();
        return in;
    }
    friend ostream & operator << (ostream &out, const BigInteger& x) {
        out << x.str();
        return out;
    }
}C[N][N];

void init() {
    C[0][0] = 1;
    for (int i = 1; i < N; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
}


int main() {
    init();int n, m;
    while(~scanf("%d%d", &n, &m) && !(n==0&&m==0)) {
        printf("%d things taken %d at a time is %s exactly.\n", n, m, C[n][m].str().c_str());
    }
}
