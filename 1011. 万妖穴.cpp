/**
* 分析：万妖穴-拓扑排序
*       注意先消灭编号最小的穴，所以使用优先队列
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n, m;
vector<int> adj[maxn];

int indegree[maxn];
vector<int> topo;
int topoSort() {
    int num = 0;
    priority_queue<int, vector<int>, greater<int> > q; //小顶堆的优先队列
    for(int i = 0; i < n; i++) {
        if(indegree[i] == 0)
            q.push(i);
    }
    while(!q.empty()) {
        int u = q.top();
        q.pop();
        num++;
        topo.push_back(u);
        for(auto v : adj[u]) {
            indegree[v]--;
            if(indegree[v] == 0)
                q.push(v);
        }
        adj[u].clear();
    }
    if(num == n)
        return num;
    else
        return n - num;
}

int main() {
    int a, b;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        indegree[b]++;
    }
    int num = topoSort();
    if(num == n) {
        printf("YES\n");
        for(int i = 0; i < topo.size(); i++) {
            printf("%d", topo[i]);
            if(i != topo.size() - 1)
                printf(" ");
        }
    } else {
        printf("NO\n%d", num);
    }
    return 0;
}
