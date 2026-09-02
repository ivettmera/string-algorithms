#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
const int INF = 0x3f3f3f3f;
const int MATCH = 1, MISS = -1, GAP = -2;

bool free_s_start = true;
bool free_s_end   = true;
bool free_t_start = true;
bool free_t_end   = true;

int memo[N][N];
int m, n;
string x, y;
string ax, ay;

void env_override(const char *name, bool &flag) {
    const char *v = getenv(name);
    if (v && string(v) == "true")  flag = true;
    if (v && string(v) == "false") flag = false;
}

void config() {
    env_override("FREE_S_START", free_s_start);
    env_override("FREE_S_END",   free_s_end);
    env_override("FREE_T_START", free_t_start);
    env_override("FREE_T_END",   free_t_end);
}

int p(int i, int j) { return x[i] == y[j] ? MATCH : MISS; }

int sim(int i, int j) {
    if (i == 0 && j == 0) return 0;
    if (i == 0) return free_s_start ? 0 : j * GAP;
    if (j == 0) return free_t_start ? 0 : i * GAP;
    if (memo[i][j] != INF) return memo[i][j];
    return memo[i][j] = max({sim(i - 1, j) + GAP,
                             sim(i - 1, j - 1) + p(i, j),
                             sim(i, j - 1) + GAP});
}

void align(int i, int j) {
    if (i == 0 && j == 0) return;
    if (i == 0) { align(0, j - 1); ax += '-';  ay += y[j]; return; }
    if (j == 0) { align(i - 1, 0); ax += x[i]; ay += '-';  return; }

    if (sim(i, j) == sim(i - 1, j) + GAP) {
        align(i - 1, j);     ax += x[i]; ay += '-';
    } else if (sim(i, j) == sim(i - 1, j - 1) + p(i, j)) {
        align(i - 1, j - 1); ax += x[i]; ay += y[j];
    } else {
        align(i, j - 1);     ax += '-';  ay += y[j];
    }
}

void solve() {
    cin >> x >> y;
    x = "$" + x;
    y = "$" + y;
    m = (int)x.size() - 1;
    n = (int)y.size() - 1;
    memset(memo, 0x3f, sizeof memo);

    int score = sim(m, n), bi = m, bj = n;
    if (free_s_end)
        for (int j = 1; j <= n; j++)
            if (sim(m, j) > score) { score = sim(m, j); bi = m; bj = j; }
    if (free_t_end)
        for (int i = 1; i <= m; i++)
            if (sim(i, n) > score) { score = sim(i, n); bi = i; bj = n; }

    align(bi, bj);
    for (int i = bi + 1; i <= m; i++) { ax += x[i]; ay += '-'; }
    for (int j = bj + 1; j <= n; j++) { ax += '-';  ay += y[j]; }

    cout << "score: " << score << '\n' << ax << '\n' << ay << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    config();
    solve();
    return 0;
}
