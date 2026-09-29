#include <bits/stdc++.h>
using namespace std;
/*Strings: x and y
 *A: without gaps
 *B: x ends in gap
 *C: Y ends in gap
 *w(k): penalty of a gap of length k (any function)
*/
const int N = 1e3 + 5;
const int INF = 0x3f3f3f3f;
const int NEG_INF = -0x3f3f3f3f;
const int MATCH = 1, MISS = -1, GAP = -2;

int memoA[N][N], memoB[N][N], memoC[N][N];
int m, n;
string x, y;
string ax, ay;

int a(int i, int j);
int b(int i, int j);
int c(int i, int j);

int p(int i, int j) {
    return x[i] == y[j] ? MATCH : MISS;
}
int w(int k) {
    return k * GAP;
}

int a(int i, int j) {
    if (i == 0 and j == 0) return 0;
    if (i == 0 or j == 0) return NEG_INF;
    if (memoA[i][j] != INF) return memoA[i][j];
    return memoA[i][j] = p(i, j) + max({a(i - 1, j - 1), b(i - 1, j - 1), c(i - 1, j - 1)});
}

int b(int i, int j) {
    if (j == 0) return NEG_INF;
    if (i == 0) return w(j);
    if (memoB[i][j] != INF) return memoB[i][j];
    int best = NEG_INF;
    for (int k = 1; k <= j; k++)
        best = max({best, a(i, j - k) + w(k), c(i, j - k) + w(k)});
    return memoB[i][j] = best;
}

int c(int i, int j) {
    if (i == 0) return NEG_INF;
    if (j == 0) return w(i);
    if (memoC[i][j] != INF) return memoC[i][j];
    int best = NEG_INF;
    for (int k = 1; k <= i; k++)
        best = max({best, a(i - k, j) + w(k), b(i - k, j) + w(k)});
    return memoC[i][j] = best;
}

void align(int i, int j, char st) {
    if (i == 0 and j == 0) return;

    int val; char nst;
    if (st == 'a') {
        val = a(i, j) - p(i, j);
        nst = (val == a(i - 1, j - 1)) ? 'a' : (val == b(i - 1, j - 1)) ? 'b' : 'c';
        align(i - 1, j - 1, nst);
        ax += x[i]; ay += y[j];
    } else if (st == 'b') {
        int k = 1;

        while (b(i, j) != a(i, j - k) + w(k) and
                b(i, j) != c(i, j - k) + w(k)) k++;

        nst = (b(i, j) == a(i, j - k) + w(k)) ? 'a' : 'c';
        align(i, j - k, nst);
        for (int t = j - k + 1; t <= j; t++) { ax += '-'; ay += y[t]; }
    } else {
        int k = 1;

        while (c(i, j) != a(i - k, j) + w(k) and
                c(i, j) != b(i - k, j) + w(k)) k++;

        nst = (c(i, j) == a(i - k, j) + w(k)) ? 'a' : 'b';for (int t = j - k + 1; t <= j; t++) { ax += '-'; ay += y[t]; }
        align(i - k, j, nst);
        for (int t = i - k + 1; t <= i; t++) { ax += x[t]; ay += '-'; }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    cin >> x >> y;
    x = "$" + x;
    y = "$" + y;
    m = (int)x.size() - 1;
    n = (int)y.size() - 1;
    memset(memoA, 0x3f, sizeof memoA);
    memset(memoB, 0x3f, sizeof memoB);
    memset(memoC, 0x3f, sizeof memoC);

    int score = max({a(m, n), b(m, n), c(m, n)});
    char st = (score == a(m, n)) ? 'a' : (score == b(m, n)) ? 'b' : 'c';
    align(m, n, st);

    cout << "score: " << score << '\n' << ax << '\n' << ay << '\n';
    return 0;
}
