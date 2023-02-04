/**
 * TODO: Linux
 */
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

const int kNumThreads = 5;
const int kBufferSize = 1024 * 1024;

string input_path(int id) { return "data" + to_string(id) + ".in"; }
string output_path(int id) { return "data" + to_string(id) + ".out"; }
string answer_path(int id) { return "data" + to_string(id) + ".ans"; }
string error_path(int) { return ""; }

void compile(const string &s) {
    if (system(("g++ " + s + ".cpp -o " + s + ".exe -O2").c_str())) {
        cout << s << ".cpp Compile Error!\n";
        exit(1);
    }
}
void run_cmd(const string &cmd, int &res) {
    res = system(cmd.c_str());
}
string get_exe_cmd(const string &s, const string &args = "", const string &in = "", const string &out = "", const string &err = "") {
    string cmd = s + ".exe " + args;
    if (!in.empty()) cmd += " < " + in;
    if (!out.empty()) cmd += " > " + out;
    if (!err.empty()) cmd += " 2> " + err;
    return cmd;
}
bool cmp(const string &out, const string &ans) {
    char buffer1[kBufferSize], buffer2[kBufferSize];
    ifstream file1(out, ios::binary), file2(ans, ios::binary);
    if (!file1 || !file2) {
        cout << "Error opening file." << endl;
        return false;
    }

    while (true) {
        file1.getline(buffer1, kBufferSize);
        file2.getline(buffer2, kBufferSize);
        // 忽略行末空格
        string str1(buffer1), str2(buffer2);
        str1.erase(find_if(str1.rbegin(), str1.rend(),
                                [](int ch) { return !isspace(ch); }).base(), str1.end());
        str2.erase(find_if(str2.rbegin(), str2.rend(),
                                [](int ch) { return !isspace(ch); }).base(), str2.end());
        if (str1 != str2) return false;
        if (file1.eof() && file2.eof()) break;
    }

    return true;
    // return !system(("fc.exe " + out + " " + ans + " > nul 2> nul").c_str());
}

void gen_testcase(int id, unsigned sd, int &res) {
    const string in = input_path(id);
    const string err = error_path(id);
    bool success = true;
    {
        int res_gen;
        thread t1(run_cmd, get_exe_cmd("gen", to_string(sd), "", in, err), ref(res_gen));
        t1.join();
        success &= (res_gen == 0);
    }
    res = success;
}
void run_testcase(int id, int &res) {
    const string in = input_path(id);
    const string out = output_path(id);
    const string ans = answer_path(id);
    const string err = error_path(id);
    bool success = true;
    if (success) {
        int res_std, res_usr;
        thread t2(run_cmd, get_exe_cmd("std", "", in, ans, err), ref(res_std));
        thread t3(run_cmd, get_exe_cmd("usr", "", in, out, err), ref(res_usr));
        t2.join();
        t3.join();
        success &= (res_std == 0);
        success &= (res_usr == 0);
    }
    res = success && cmp(out, ans);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    system("taskkill /im gen.exe /f");
    system("taskkill /im usr.exe /f");
    system("taskkill /im std.exe /f");
    if (true) {
        cout << "Compiling..." << endl;
        compile("gen");
        compile("std");
        compile("usr");
        cout << "Compiled!" << endl;
    }
    const string in = "data.in", out = "data.out", ans = "data.ans", err = "";
    mt19937 rnd(42); int cnt = 0;
    clock_t start = clock();
    cout << "Start!" << endl;
    vector<int> gen_res(kNumThreads);
    vector<int> res(kNumThreads);
    vector<unsigned> sd(kNumThreads);
    vector<thread> t(kNumThreads);
    while (true) {
        cout << "#" << cnt << endl;
        r0p (i, kNumThreads) {
            sd[i] = rnd();
            t[i] = thread(gen_testcase, i, sd[i], ref(gen_res[i]));
        }
        r0p (i, kNumThreads) t[i].join();
        r0p (i, kNumThreads) {
            t[i] = thread(run_testcase, i, ref(res[i]));
        }
        r0p (i, kNumThreads) t[i].join();
        r0p (i, kNumThreads) if (!gen_res[i] || !res[i]) {
            cout << "#" << cnt + i << "(data" << i << ")"
                << " Wrong Answer!" << endl;
            cout << "seed = " << sd[i] << endl;
            cout << "Total time: " << double(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
            exit(0);
        }
        cnt += kNumThreads;
    }
    cout << "Error!" << endl;
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
