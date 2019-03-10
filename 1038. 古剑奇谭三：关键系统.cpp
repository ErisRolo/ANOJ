#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int inf = 1000000000;

int g[maxn][maxn];
bool vis[maxn];
vector<int> vec;

void DFS(int v) {
    vis[v] = true;
    for(int i = 1; i <= maxn; i++) {
        if(g[v][i] != inf && vis[i] == false)
            DFS(i);
    }
}

int main() {
    fill(g[0], g[0] + maxn * maxn, inf);
    int n, m, k, b1 = 0;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a][b] = g[b][a] = 1;
    }
    fill(vis, vis + maxn, false);
    for(int i = 1; i <= n; i++) {
        if(vis[i] == false) {
            DFS(i);
            b1++;
        }
    }
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        int b2 = 0;
        fill(vis, vis + maxn, false);
        vec.clear();
        int v;
        bool flag = false; //特判那种完全独立的点
        scanf("%d", &v);
        for(int j = 1; j <= n; j++) {
            if(g[v][j] == 1) {
                flag = true; //只要存在一条边则不会完全独立
                g[v][j] = g[j][v] = inf;
                vec.push_back(j);
            }
        }
        for(int j = 1; j <= n; j++) {
            if(vis[j] == false) {
                DFS(j);
                b2++;
            }
        }
        b2--; //拿出去的那点要减掉
        if(flag && b2 != b1)
            printf("YES\n");
        else
            printf("NO\n");
        for(int j = 0; j < vec.size(); j++)
            g[v][vec[j]] = g[vec[j]][v] = 1;
    }
    return 0;
}
