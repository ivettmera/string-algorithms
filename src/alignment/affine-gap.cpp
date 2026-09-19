#include <bits/stdc++.h>
using namespace std;
/*Strings: x and y
 *A: without gaps
 *B: x ends in gap
 *C: Y ends in gap
 *GAP_OPEN(h), GAP_EXTEND(g): w(x) = h + g
*/
const int N = 1e3 + 5;
const int INF = 0x3f3f3f3f;
const int NEG_INF = -0x3f3f3f3f;
const int MATCH = 1, MISS = -1;
const int GAP_OPEN = -3, GAP_EXTEND = -2;
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

int a(int i, int j) {
    if (i == 0 and j == 0) return 0;
    if (i == 0 or j == 0) return NEG_INF;
    if (memoA[i][j] != INF) return memoA[i][j];
    return memoA[i][j] = p(i, j) + max({a(i - 1, j - 1),
                                        b(i - 1, j - 1),
                                        c(i - 1, j - 1)});
}

int b(int i, int j) {
    if (j == 0) return NEG_INF;
    if (i == 0) return GAP_OPEN + j * GAP_EXTEND;
    if (memoB[i][j] != INF) return memoB[i][j];
    return memoB[i][j] = max({a(i, j - 1) + GAP_OPEN + GAP_EXTEND,
                              c(i, j - 1) + GAP_OPEN + GAP_EXTEND,
                              b(i, j - 1) + GAP_EXTEND});
}

int c(int i, int j) {
    if (i == 0) return NEG_INF;
    if (j == 0) return GAP_OPEN + i * GAP_EXTEND;
    if (memoC[i][j] != INF) return memoC[i][j];
    return memoC[i][j] = max({a(i - 1, j) + GAP_OPEN + GAP_EXTEND,
                              b(i - 1, j) + GAP_OPEN + GAP_EXTEND,
                              c(i - 1, j) + GAP_EXTEND});
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
        val = b(i, j);
        nst = (val == a(i, j - 1) + GAP_OPEN + GAP_EXTEND) ? 'a' :
                  (val == c(i, j - 1) + GAP_OPEN + GAP_EXTEND) ? 'c' : 'b';
        align(i, j - 1, nst);
        ax += '-'; ay += y[j];
    } else {
        val = c(i, j);
        nst = (val == a(i - 1, j) + GAP_OPEN + GAP_EXTEND) ? 'a' :
                  (val == b(i - 1, j) + GAP_OPEN + GAP_EXTEND) ? 'b' : 'c';
        align(i - 1, j, nst);
        ax += x[i]; ay += '-';
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
