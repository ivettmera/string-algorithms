#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
const int INF = 0x3f3f3f3f;
const int MATCH = 1, MISS = -1, GAP = -2;

int memo[N][N];
int m, n;
string x, y;
string ax, ay;

int p(int i, int j) { return x[i] == y[j] ? MATCH : MISS; }

int sim(int i, int j) {
    if (i == 0 || j == 0) return 0;
    if (memo[i][j] != INF) return memo[i][j];
    return memo[i][j] = max({0,
                             sim(i - 1, j - 1) + p(i, j),
                             sim(i - 1, j) + GAP,
                             sim(i, j - 1) + GAP});
}

void align(int i, int j) {
    if (i == 0 || j == 0 || sim(i, j) == 0) return;

    if (sim(i, j) == sim(i - 1, j - 1) + p(i, j)) {
        align(i - 1, j - 1); ax += x[i]; ay += y[j];
    } else if (sim(i, j) == sim(i - 1, j) + GAP) {
        align(i - 1, j);     ax += x[i]; ay += '-';
    } else {
        align(i, j - 1);     ax += '-';  ay += y[j];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    cin >> x >> y;
    x = "$" + x;
    y = "$" + y;
    m = (int)x.size() - 1;
    n = (int)y.size() - 1;
    memset(memo, 0x3f, sizeof memo);

    int score = 0, bi = 0, bj = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (sim(i, j) > score) {
                score = sim(i, j);
                bi = i;
                bj = j;
            }

    align(bi, bj);

    cout << "score: " << score << '\n' << ax << '\n' << ay << '\n';
    return 0;
}
