#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;

int v1[maxn][maxn];
int v2[maxn][maxn];
int l1[maxn];
int l2[maxn];

int main() {
    int n, k, v, a, b;
    bool flag;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        for(int j = n; j >= 1; j--) {
            scanf("%d", &v);
            v1[i][v] = j;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = n; j >= 1; j--) {
            scanf("%d", &v);
            v2[i][v] = j;
        }
    }
    scanf("%d", &k);
    while(k--) {
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &a, &b);
            l1[a] = b;
            l2[b] = a;
        }
        flag = true;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(v1[i][j] > v1[i][l1[i]] && v2[j][i] > v2[j][l2[j]])
                    flag = false;
            }
        }
        if(flag)
            printf("Stable\n");
        else
            printf("Not Stable\n");
    }
    return 0;
}
