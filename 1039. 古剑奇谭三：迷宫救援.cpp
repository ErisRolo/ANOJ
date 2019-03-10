/**
* ������˼·������ͬ������һ�����Ե�TLE����������
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;
const int inf = 100000000;

int n, m;
int t, worst = -1;
int g[maxn][maxn];
int d[maxn];
bool vis[maxn] = {false};
vector<int> pre[maxn];
vector<int> temppath, path;

void Dijkstra(int s) {
    fill(d, d + maxn, inf);
    d[s] = 0;
    for(int i = 1; i <= n; i++) {
        int u = -1, min = inf;
        //ע���±�
        for(int j = 1; j <= n; j++) {
            if(vis[j] == false && d[j] < min) {
                u = j;
                min = d[j];
            }
        }
        if(u == -1)
            return;
        vis[u] = true;
        for(int v = 1; v <= n; v++) {
            if(vis[v] == false && g[u][v] != inf) {
                if(d[u] + g[u][v] < d[v]) {
                    d[v] = d[u] + g[u][v];
                    pre[v].clear();
                    pre[v].push_back(u);
                }
            } else if(d[u] + g[u][v] == d[v]) {
                pre[v].push_back(u);
            }
        }
    }
}

void DFS(int v) {
    if(v == 1) {
        temppath.push_back(v);
        int value = 0;
        for(int i = temppath.size() - 1; i > 0; i--) {
            int id = temppath[i];
            int nextid = temppath[i - 1];
            value += g[id][nextid];
        }
        if(value < t) {
            t = value;
            path = temppath;
        }
        temppath.pop_back();
        return;
    }
    temppath.push_back(v);
    for(int i = 0; i < pre[v].size(); i++)
        DFS(pre[v][i]); //�ݹ����ǰ���������
    temppath.pop_back();
}

int main() {

#ifdef ONLINE_JUDGE
#else
    freopen("4.in", "r", stdin);
#endif

    fill(g[0], g[0] + maxn * maxn, inf);
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u][v] = g[v][u] = w;
    }
    bool flag = true;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(g[i][j] != inf) {
                int temp = g[i][j];
                g[i][j] = g[j][i] = inf;
                t = inf;
                fill(vis, vis + maxn, false);
                Dijkstra(1);
                DFS(n);
                if(t == inf)
                    flag = false; //����������ﲻ��
                if(t > worst && t != inf)
                    worst = t;
                g[i][j] = g[j][i] = temp;
            }
        }
    }
    if(flag && worst != -1)
        printf("%d", worst);
    else
        printf("It's a bug!!!");
    return 0;
}

/******���Ƿָ��ߣ�����Ϊ������******/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0x3FFFFFFF;
const int MAXV = 510;   // �����������
int G[MAXV][MAXV];      // �ڽӾ���
bool vis[MAXV];         // �����Ƿ��ѷ���
int n, m, d[MAXV], pre[MAXV];      // ����, ����, ��㵽�������̾���, ��������·��ǰ�����
// ���·�㷨,updatePre��ʾ�Ƿ�Ҫ����pre����
void Dijkstra(bool updatePre) {
    memset(vis, false, sizeof(vis));    // ��ʼ�����ж���δ����
    fill(d, d + MAXV, INF);             // ��ʼ����̾�������
    d[1] = 0;   // ��㵽������̾����ʼ��Ϊ0
    for(int i = 0; i < n; i++) {    // ִ��n��
        int u = -1, MIN = INF;      // Ѱ��uʹ��d[u]��С
        for(int j = 1; j <= n; j++) {
            if(vis[j] == false && d[j] < MIN) {     // �ҵ�d��С��δ���ʶ���
                u = j;
                MIN = d[j];
            }
        }
        if(u == -1)
            return;     // ʣ�ඥ���޷���ͨ,�˳�dij�㷨
        vis[u] = true;          // ��Ƕ���u�ѷ���
        for(int v = 1; v <= n; v++) {   // ��������δ���ʽ��
            if(vis[v] == false && G[u][v] != -1 && d[u] + G[u][v] < d[v]) {     // �����uΪ�н����ʹd[v]��С
                d[v] = d[u] + G[u][v];      // ��ô����d[v]
                if(updatePre) {     // �����Ҫ����pre����
                    pre[v] = u;     // ��v��ǰ��Ϊu
                }
            }
        }
    }
}

int main() {
    memset(G, -1, sizeof(G));       // ��ʼ��ͼG
    memset(pre, -1, sizeof(pre));   // ��ʼ��pre����
    scanf("%d%d", &n, &m);          // ������, ����
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);    // ����ߵ����,�յ�,��Ȩ
        G[u][v] = G[v][u] = w;      // ˫���
    }
    Dijkstra(true);     // ��һ�����·,������pre����
    int maxDistance = d[n], v = n;  // maxDistanceΪ��������㵽�յ����̾���, v��ǰ��Ϊ�յ�
    while(pre[v] != -1) {           // �����û�е����
        int backup = G[pre[v]][v];  // ���ݱ�pre[v]->v�ı�Ȩ
        G[pre[v]][v] = -1;          // ɾ����pre[v]->v
        Dijkstra(false);            // ��һ�����·,����Ҫ����pre����
        maxDistance = max(maxDistance, d[n]);   // ���������µ���̾���
        G[pre[v]][v] = backup;      // �ָ�ɾ���ı�
        v = pre[v];                 // ��v����ǰ�����
    }
    if(maxDistance == INF) {            // ����������޷������յ�
        printf("It's a bug!!!\n");      // ���������Ϣ
    } else {
        printf("%d\n", maxDistance);    // ���������������㵽�յ����̾���
    }
    return 0;
}
