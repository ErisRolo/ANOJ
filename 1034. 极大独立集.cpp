#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;

int g[maxn][maxn];
int h[maxn];
set<int> s1, s2, s3;

int main() {
    int n, m, u, v, k, l, t;
    bool isIndependentSet, isMaximal;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        g[u][v] = g[v][u] = 1;
        s1.insert(u);
        s1.insert(v);
    }
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        fill(h, h + maxn, 0);
        isIndependentSet = true, isMaximal = true;
        s2.clear();
        s3.clear(); //�м�
        scanf("%d", &l);
        for(int j = 0; j < l; j++) {
            scanf("%d", &t);
            s2.insert(t);
            h[t] = 1;
        }
        for(set<int>::iterator it1 = s1.begin(); it1 != s1.end(); it1++) {
            if(h[*it1] != 1)
                s3.insert(*it1);
        }
        for(set<int>::iterator it1 = s2.begin(); it1 != s2.end(); it1++) {
            for(set<int>::iterator it2 = s2.begin(); it2 != s2.end(); it2++) {
                if(g[*it1][*it2] == 1) {
                    isIndependentSet = false;
                }
            }
        }
        if(isIndependentSet == true) {
            for(set<int>::iterator it1 = s3.begin(); it1 != s3.end(); it1++) {
                bool flag = true; //�����Ƕ�����
                s2.insert(*it1);
                for(set<int>::iterator it2 = s2.begin(); it2 != s2.end(); it2++) {
                    for(set<int>::iterator it3 = s2.begin(); it3 != s2.end(); it3++) {
                        if(g[*it2][*it3] == 1) {
                            flag = false; //���ڵ�ʹ�䲻Ϊ����������Ϊ����
                        }
                    }
                }
                s2.erase(*it1);
                if(flag)
                    isMaximal = false; //����������Ƕ����������Ǽ���
            }
        }
        if(!isIndependentSet)
            printf("Not an Independent Set\n");
        else {
            if(isMaximal)
                printf("Yes\n");
            if(!isMaximal)
                printf("Not Maximal\n");
        }
    }
    return 0;
}
