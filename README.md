# 编程竞赛代码仓库

## 命名规则

仅使用小写字母、数字与下划线。

一些记号：

- `ID`：OJ 中的题号；
- `CONTEST`：比赛名称；
- `PID`：题目（在题库或比赛中的）编号（如 `1`、`a`）。

- [LOJ](https://loj.ac/)：`loj_pID`。
  - 例：[loj_p1](https://loj.ac/p/1)。
- [UOJ](https://uoj.ac/)：`uoj_pID`。
  - 例：[uoj_p1](https://uoj.ac/problem/1)。
- [洛谷](https://www.luogu.com.cn/)：`luogu_ID`（仅限主题库）。
  - 例：[luogu_p1001](https://www.luogu.com.cn/problem/P1001)。
- [Codeforces](https://codeforces.com/)：`cf_CONTEST_ID`（仅限主题库）、`cf_gymCONTEST_ID`（gym）。
  - 例：[cf_1_a](https://codeforces.com/problemset/problem/1/A)。
    - 不使用比赛链接。
  - 例：[cf_gym_100001_a](https://codeforces.com/gym/100001/problem/A)。
    - 对于无在线题面的比赛，手动添加 `/problem/PID`。
- [AtCoder](https://atcoder.jp/)：`at_CONTEST_ID`（仅限 ABC、ARC 与 AGC）。 <!--TODO：其他类型比赛。-->
  - 例：[at_arc001_a](https://atcoder.jp/contests/arc001/tasks/arc001_1)。
  - 例：[at_arc058_a](https://atcoder.jp/contests/arc058/tasks/arc058_a)。
    - 实际显示与 URL 内容不符时，**以 URL 为准**。

- 本质相同的代码仅存放一份，同一题的不同实现**加后缀区分**。
  - 例：[loj_p104_fhq_treap](https://loj.ac/p/104) 与 [loj_p104_wblt](https://loj.ac/p/104)。

## 文件存放

- 测试代码存放在 `test` 文件夹。
- 通过的代码存放在 `_ac` 文件夹。
  - 例：`_ac/loj_p1.cpp`。
- 未通过的代码存放在 `_unac` 文件夹。
  - 例：`_unac/loj_p1.cpp`。
- 比赛代码存放在 `_contest` 文件夹。
  - 例：`_contest/ioi2022/day1/a.cpp`。 <!--TODO：是否加上题目名称。-->
- 线上非官方比赛代码存放在 `_online_contest` 文件夹。
  - [Codeforces](https://codeforces.com/) 题目存放在 `_online_contest/codeforces` 中。
    - 例：`_online_contest/codeforces/1/cf_1_a.cpp`。
    - 例：`_online_contest/codeforces/gym_100001/cf_gym_100001_a.cpp`。
  - [AtCoder](https://atcoder.jp/) 题目存放在 `_online_contest/atcoder` 中。
    - 例：`_online_contest/atcoder/arc001/at_arc001_a.cpp`。

## 代码头

```cpp
/* FILENAME */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = l, rep##i = r; i <= rep##i; ++i)
#define per(i, r, l) for (int i = r, per##i = l; i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : s)
#define all(s) (s).begin(), (s).end()
#define dbg(x) (cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>; using namespace std;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
```
