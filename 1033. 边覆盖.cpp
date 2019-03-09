#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;

int g[maxn][maxn];
set<int> cnt;

int main() {
    int n, m, u, v, k, l;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        g[u][v] = g[v][u] = 1;
    }
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        cnt.clear();
        scanf("%d", &l);
        for(int j = 0; j < l; j++) {
            scanf("%d%d", &u, &v);
            if(g[u][v] == 1) {
                cnt.insert(u);
                cnt.insert(v);
            }
        }
        if(cnt.size() == n)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
