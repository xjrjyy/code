# 编程竞赛代码仓库

## 命名规则

`trans.py` 是 URL 转文件名工具。需要先 `pip install -r requirements.txt`。

文件名仅使用小写字母、数字与下划线。

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
    - 不使用赛时链接。
  - 例：[cf_gym_100001_a](https://codeforces.com/gym/100001/problem/A)。
    - 对于无在线题面的比赛，手动添加 `/problem/PID`。
- [AtCoder](https://atcoder.jp/)：`at_CONTEST_ID`（仅限 ABC、ARC 与 AGC）。 <!--TODO：其他类型比赛。-->
  - 例：[at_arc001_a](https://atcoder.jp/contests/arc001/tasks/arc001_1)。
  - 例：[at_arc058_a](https://atcoder.jp/contests/arc058/tasks/arc058_a)。
    - 实际显示与 URL 内容不符时，**以 URL 为准**。
- 赛题：`CONTEST_(DAY)(PID_)NAME`。
  - 除非找不到原题面，否则需要加上 `PID`。
  - 若题目年代久远，找不到英文名称，则直接根据中文名称翻译，在代码内注明。
  - 例：`ioi2022_1a_digital_circuit`。
  - 例：`ceoi2016_kangaroo`。

<!--TODO: 省选题。-->

<!--TODO：校内模拟赛。-->

- 本质相同的代码仅存放一份，同一题的不同实现**加后缀区分**（仅**模板题**与**相差很大的解法**）。
  - 例：[loj_p104_fhq_treap](https://loj.ac/p/104) 与 [loj_p104_wblt](https://loj.ac/p/104)。

如果存在重题，需要放置多份代码。 <!--TODO：校内模拟赛。-->

## 文件存放

- 测试代码存放在 `test` 文件夹。
- 通过的代码存放在 `_ac` 文件夹。
  - 例：`_ac/loj_p1.cpp`。
- 未通过的代码存放在 `_unac` 文件夹。
  - 例：`_unac/loj_p1.cpp`。
- 比赛代码存放在 `_contest/CONTEST/YEAR` 文件夹。
  - 例：`_contest/ioi/2022/ioi2022_1a_digital_circuit.cpp`。
  - 省选（Provincial Team Selection）题目存放在 `_contest/pts/CONTEST/YEAR` 文件夹。
    - 例：`_contest/pts/fjoi/2022/fjoi2022_1a_range.cpp`。
- 线上非官方比赛代码存放在 `_online_contest` 文件夹。
  - [Uoj](https://uoj.ac/) 题目存放在 `_online_contest/uoj/CONTEST` 中。
    - 例：`_online_contest/uoj/unr1/uoj_p218.cpp`。
  - [Codeforces](https://codeforces.com/) 题目存放在 `_online_contest/codeforces/CONTEST` 中。
    - 例：`_online_contest/codeforces/1/cf_1_a.cpp`。
    - 例：`_online_contest/codeforces/gym_100001/cf_gym_100001_a.cpp`。
  - [AtCoder](https://atcoder.jp/) 题目存放在 `_online_contest/atcoder/CONTEST` 中。
    - 例：`_online_contest/atcoder/arc001/at_arc001_a.cpp`。

[OI 赛事与赛制](https://oi-wiki.org/contest/oi/)。

常见比赛见 [Category](http://qoj.ac/category/)。

## 代码头

所有代码均不保留文件输入输出。

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
