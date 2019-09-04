/**
* 分析：极大匹配，先判断是否为匹配，即边是原图的边且每个顶点只出现一次
*       再判断是不是极大，即这些点之外的点，是否还有边相连，有的话则非极大
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n, m, k, u, v, l;
int g[maxn][maxn];
int h[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        g[u][v] = g[v][u] = 1;
    }
    scanf("%d", &k);
    while(k--) {
        bool ismatch = true, ismax = true;
        fill(h, h + maxn, 0);
        scanf("%d", &l);
        while(l--) {
            scanf("%d%d", &u, &v);
            h[u]++, h[v]++;
            if(g[u][v] != 1)
                ismatch = false;
        }
        for(int i = 1; i <= n; i++) {
            if(h[i] != 0) {
                if(h[i] != 1) {
                    ismatch = false;
                    break;
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(h[i] == 0 && h[j] == 0 && g[i][j] == 1) {
                    ismax = false;
                    break;
                }
            }
        }
        if(ismatch) {
            if(ismax)
                printf("Yes\n");
            else
                printf("Not Maximal\n");
        } else
            printf("Not a Matching\n");
    }
    return 0;
}
