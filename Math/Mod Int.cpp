#include <bits/stdc++.h>
using namespace std;

template <int M>
struct Mint {
    int x;

    Mint(int x = 0) : x(x) {}
    // Mint(long long v = 0) : x((v % M + M) % M) {}

    Mint operator+(const Mint &u) const { return x + u.x >= M ? x + u.x - M : x + u.x; }
    Mint operator-(const Mint &u) const { return x - u.x < 0 ? x - u.x + M : x - u.x; }
    Mint operator*(const Mint &u) const { return (int)(1ll * x * u.x % M); }
    Mint operator-() const { return Mint(M - x); }
    Mint &operator+=(const Mint &u) { return *this = *this + u; }
    Mint &operator-=(const Mint &u) { return *this = *this - u; }
    Mint &operator*=(const Mint &u) { return *this = *this * u; }
    bool operator==(const Mint &u) const { return x == u.x; }
    bool operator!=(const Mint &u) const { return x != u.x; }
    explicit operator int() const { return x; }

    Mint pow(long long k) const
    {
        Mint res = 1, a = *this;
        while (k > 0) {
            if (k & 1) res *= a;
            a *= a;
            k >>= 1;
        }
        return res;
    }

    Mint inv() const { return pow(M - 2); }  // Note: M must be prime
    Mint operator/(const Mint &u) const { return *this * u.inv(); }
    Mint &operator/=(const Mint &u) { return *this = *this / u; }
};

// https://www.luogu.com.cn/problem/P2613
constexpr int M = 19260817;
using T = Mint<M>;

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    auto str2val = [](const string &s) -> T {
    	T res = 0;
    	for (char c : s) {
    		res = res * 10 + (c - '0');
    	}
    	return res;
    };
    
    string sa, sb;
    cin >> sa >> sb;
    auto a = str2val(sa);
    auto b = str2val(sb);
    cout << (int)(a / b) << '\n';
}
