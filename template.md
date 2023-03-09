# 代码模板

## 模板

```cpp
/* FILENAME */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = (l), rep##i = (r); i <= rep##i; ++i)
#define per(i, r, l) for (int i = (r), per##i = (l); i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : (s))
#define all(s) (s).begin(), (s).end()
#define dbg(x) (std::cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << std::endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}

```

```cpp
const int P = 1e9 + 7;

int fix(int x) {
    assert(-P <= x && x < 2 * P);
    if (x < 0) x += P;
    if (x >= P) x -= P;
    return x;
}
template <class T> T power(T a, ll b) {
    T c = 1; for (; b; b /= 2, a *= a) if (b & 1) c *= a;
    return c;
}
struct Z {
    int x;
    Z(int x = 0) : x(fix(x)) {}
    Z(ll x) : x(fix(x % P)) {}
    int val() const { return x; }
    Z operator-() const { return Z(fix(P - x)); }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) { return x = 1ll * x * rhs.x % P, *this; }
    Z &operator+=(const Z &rhs) { return x = fix(x + rhs.x), *this; }
    Z &operator-=(const Z &rhs) { return x = fix(x - rhs.x), *this; }
    Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
    friend Z operator*(const Z &lhs, const Z &rhs) { Z res = lhs; return res *= rhs; }
    friend Z operator+(const Z &lhs, const Z &rhs) { Z res = lhs; return res += rhs; }
    friend Z operator-(const Z &lhs, const Z &rhs) { Z res = lhs; return res -= rhs; }
    friend Z operator/(const Z &lhs, const Z &rhs) { Z res = lhs; return res /= rhs; }
    friend std::istream &operator>>(std::istream &in, Z &a) {
        ll v; return in >> v, a = Z(v), in;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};
```

## 数据结构

### 并查集

```cpp
struct DSU {
    int n; vec<int> fa, sz;
    DSU(int n_) : n(n_), fa(n), sz(n, 1) { std::iota(all(fa), 0); }
    int fd(int x) { return x == fa[x] ? x : fa[x] = fd(fa[x]); }
    void mg(int u, int v) {
        if ((u = fd(u)) == (v = fd(v))) return;
        if (sz[u] < sz[v]) std::swap(u, v);
        fa[v] = u, sz[u] += sz[v];
    }
};
```

### 树状数组

```cpp
template <typename T> struct BIT {
    int n; vec<T> t;
    BIT(int n_) : n(n_), t(n + 1) {}
    void add(int p, const T &x) { for (; p <= n; p += p & -p) t[p] += x; }
    T qry(int p) { T x = T(); for (; p; p -= p & -p) { x += t[p]; } return x; }
    T range(int l, int r) { return qry(r) - qry(l - 1); }
};
```

## 图论

### 网络流

```cpp
template <typename T> class NetFlow {
public:
    struct Edge { int u, v; T w, f; };
    NetFlow(int n_) : n(n_), G(n), d(n), h(n) {}
    void adde(int u, int v, T w) {
        auto add = [&](int u, int v, T w, T f) {
            G[u].push_back(int(E.size())), E.push_back({u, v, w, f});
        };
        add(u, v, w, 0), add(v, u, w, w);
    }
    T max_flow(int s_, int t_, T mf) {
        T f = T(); s = s_, t = t_;
        r0p (i, int(E.size())) E[i].f = (i & 1 ? E[i].w : T());
        while (bfs()) fill(all(h), 0), f += dfs(s, mf);
        return f;
    }
    vec<Edge> &edges() { return E; }
    const vec<Edge> &edges() const { return E; }
private:
    bool bfs() {
        static queue<int> Q;
        fill(all(d), -1), d[s] = 0, Q.push(s);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            each (i, G[u]) {
                int v = E[i].v; T w = E[i].w - E[i].f;
                if (w && !~d[v]) d[v] = d[u] + 1, Q.push(v);
            }
        }
        return ~d[t];
    }
    T dfs(int u, T mf) {
        T f = T(); if (u == t) return mf;
        for (int &_ = h[u]; f < mf && _ < int(G[u].size()); ++_) {
            int i = G[u][_], v = E[i].v; T w = E[i].w - E[i].f;
            if (w && d[v] == d[u] + 1) {
                T t = dfs(v, min(w, mf - f));
                E[i].f += t, E[i ^ 1].f -= t, f += t;
            }
        }
        return f;
    }
    int n, s, t; vec<Edge> E; vec<vec<int>> G;
    vec<int> d, h;
};
```

### 费用流

```cpp
template <typename T, typename U> class CostNetFlow {
public:
    struct Edge { int u, v; T w, f; U c; };
    struct Flow {
        T f; U c;
        Flow operator+(const Flow &y) const { return {f + y.f, c + y.c}; }
        Flow &operator+=(const Flow &y) { return f += y.f, c += y.c, *this; }
    };
    CostNetFlow(int n_) : n(n_), G(n), d(n), h(n), vs(n) {}
    void adde(int u, int v, T w, U c) {
        auto add = [&](int u, int v, T w, T f, U c) {
            G[u].push_back(int(E.size())), E.push_back({u, v, w, f, c});
        };
        add(u, v, w, T(), c), add(v, u, w, w, -c);
    }
    Flow max_flow(int s_, int t_, T mf) {
        Flow f = {T(), U()}; s = s_, t = t_;
        r0p (i, int(E.size())) E[i].f = (i & 1 ? E[i].w : T());
        while (spfa()) fill(all(h), 0), f += dfs(s, mf);
        return f;
    }
    vec<Edge> &edges() { return E; }
    const vec<Edge> &edges() const { return E; }
private:
    bool spfa() {
        static queue<int> Q; static vec<bool> V;
        V.clear(), V.resize(n);
        V[s] = true, fill(all(vs), false), d[s] = U(), Q.push(s);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop(), vs[u] = false;
            each (i, G[u]) {
                int v = E[i].v; T w = E[i].w - E[i].f; U c = E[i].c;
                if (w && (!V[v] || d[v] > d[u] + c)) {
                    V[v] = true, d[v] = d[u] + c;
                    if (!vs[v]) Q.push(v), vs[v] = true;
                }
            }
        }
        return V[t];
    }
    Flow dfs(int u, T mf) {
        Flow f = {T(), U()}; if (u == t) return {mf, U()};
        vs[u] = true;
        for (int &_ = h[u]; f.f < mf && _ < int(G[u].size()); ++_) {
            int i = G[u][_], v = E[i].v; T w = E[i].w - E[i].f; U c = E[i].c;
            if (!vs[v] && w && d[v] == d[u] + c) {
                Flow t = dfs(v, min(w, mf - f.f));
                E[i].f += t.f, E[i ^ 1].f -= t.f, f += t, f.c += t.f * c;
            }
        }
        return vs[u] = false, f;
    }
    int n, s, t; vec<Edge> E; vec<vec<int>> G;
    vec<U> d; vec<int> h; vec<bool> vs;
};
```

## 优化

### Perf

```cpp
using namespace std::chrono;
struct Perf {
    std::string msg; steady_clock::time_point st;
    Perf(const std::string &msg_) : msg(msg_), st(steady_clock::now()) {}
    ~Perf() {
        static std::map<std::string, nanoseconds> *M = nullptr;
        if (M == nullptr) M = new std::map<std::string, nanoseconds>();
        steady_clock::time_point ed = steady_clock::now();
        auto t = duration_cast<nanoseconds>(ed - st);
        (*M)[msg] += t;
        if (msg == "ALL") {
            for (const auto &p : *M) {
                auto t = duration_cast<milliseconds>(p.second);
                std::cerr << p.first << ": " << t.count() << "ms\n";
            }
            delete M;
        }
    }
} _perf_print("ALL");
#define PERF() Perf _perf(__FUNCTION__)
```
