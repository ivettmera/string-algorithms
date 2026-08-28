#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

int memo[N][N];
string x, y ;

int eDist(int n, int m){
    if(n == - 1 and m == -1) return 0;
    if(n == -1) return m + 1;
    if(m == -1) return n + 1;

    if(memo[n][m] != -1) return memo[n][m];

    if(x[n] == y[m]) memo[n][m] = eDist(n - 1, m - 1);
    else memo[n][m] = 1 + min({eDist(n - 1, m), eDist(n, m - 1),
                                eDist(n - 1, m - 1)});

    return memo[n][m];
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    cin >> x >> y;
    memset(memo, -1, sizeof(memo));
    cout << eDist(x.size() - 1 , y.size() - 1) << '\n';

    return 0;
}