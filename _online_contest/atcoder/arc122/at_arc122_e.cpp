/* at_arc122_e.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = (l), rep##i = (r); i <= rep##i; ++i)
#define per(i, r, l) for (int i = (r), per##i = (l); i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : (s))
#define all(s) (s).begin(), (s).end()
#define dbg(x) (cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>; using namespace std;

ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
ll lcm(ll x, ll y) { return x / gcd(x, y) * y; }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    vec<ll> a(n); each (x, a) cin >> x;
    auto chk = [&](const vec<ll> &t, ll x) {
        ll y = 1;
        each (s, t) if (s != x) {
            y = lcm(y, gcd(x, s));
            if (y == x) return false;
        }
        return true;
    };
    vec<ll> A;
    r0p (_, n) {
        each (x, a) if (chk(a, x)) {
            A.push_back(x);
            a.erase(find(all(a), x));
            break;
        }
    }
    if (int(A.size()) < n) return cout << "No\n", 0;
    reverse(all(A));
    cout << "Yes\n";
    each (x, A) cout << x << ' ';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
