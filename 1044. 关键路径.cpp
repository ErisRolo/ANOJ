/**
* 分析：传统算法求解关键路径，思路如下
*       先拓扑排序判断是否为DAG，拓扑排序的同时获得拓扑序列（用栈存储），并求解ve数组，即ve[v]=max(ve[v],ve[u]+g[u][v])
*       然后求解关键路径，先获取最大ve（也是关键路径总长度），将vl数组初始化为vl，然后求解vl数组，即vl[u]=min(vl[u],vl[v]-g[u][v])
*       之后求解e数组和l数组，即e[u][v]=ve[u]，l[u][v]=vl[v]-g[u][v]，e和l相当的即为关键活动，用vector<int> activity[maxn]存储
*       最后按要求输出，打印路径的话就用DFS，和图一样，不过递归边界为activity[u].size()==0，传进的参数为入度为0且activity[i].size()!=0的顶点
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

struct Node {
    int v, w;
};

int n, m, u, v, w, k;
vector<Node> adj[maxn];
int indegree[maxn], inDegree[maxn]; //入度 入度备份
int ve[maxn], vl[maxn]; //点的最早时间 点的最晚时间
int e[maxn][maxn], l[maxn][maxn]; //边的最早时间 边的最晚时间
vector<int> activity[maxn]; //关键活动 相当于dp版本里的choice

stack<int> topo; //用栈存储拓扑序列 方便后序获得逆拓扑序列
bool topoSort() { //拓扑排序 并求解ve数组
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(indegree[i] == 0)
            q.push(i);
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push(u);
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].v;
            indegree[v]--;
            if(indegree[v] == 0)
                q.push(v);
//			//求解ve
//			if(ve[u]+adj[u][i].w>ve[v])
//				ve[v]=ve[u]+adj[u][i].w;
            ve[v] = max(ve[v], ve[u] + adj[u][i].w); //最迟的 就是最大的
        }
    }
    if(topo.size() == n)
        return true;
    else
        return false;
}

int criticalPath() {
//	int maxve=0;
//	for(int i=1; i<=n; i++) {
//		if(ve[i]>maxve)
//			maxve=ve[i]; //多汇点时取最长
//	}
    int maxve = *max_element(ve + 1, ve + n + 1); //求解最大的ve
    fill(vl + 1, vl + n + 1, maxve); //vl数组初始化 初始值为汇点的ve值
    while(!topo.empty()) { //topo出栈即为逆拓扑序列，求解vl数组
        int u = topo.top();
        topo.pop();
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].v;
//			//求解vl
//			if(vl[v]-adj[u][i].w<vl[u])
//				vl[u]=vl[v]-adj[u][i].w;
            vl[u] = min(vl[u], vl[v] - adj[u][i].w); //最早的 就是最小的
        }
    }
    for(int u = 1; u <= n; u++) {
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].v, w = adj[u][i].w;
            e[u][v] = ve[u]; //求解活动的最早开始时间e 即引出活动的事件的最早开始时间
            l[u][v] = vl[v] - w; //求解活动的最迟开始时间l 即活动到达的事件的最迟开始时间减去活动使用时间
            if(e[u][v] == l[u][v])
                activity[u].push_back(v); //如果相等则为关键活动
        }
    }
    return maxve;
}

vector<int> path; //关键路径
void DFS(int u) {
    if(activity[u].size() == 0) {
        path.push_back(u);
        for(int i = 0; i < path.size(); i++) {  //输出关键路径
            printf("%d", path[i]);
            if(i != path.size() - 1)
                printf("->");
            else
                printf("\n");
        }
        path.pop_back();
        return;
    }
    path.push_back(u);
    sort(activity[u].begin(), activity[u].end()); //如有需要
    for(int i = 0; i < activity[u].size(); i++)
        DFS(activity[u][i]);
    path.pop_back();
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back({v, w});
        indegree[v]++;
        inDegree[v]++;
    }
    if(topoSort()) {
        printf("YES\n");
        int maxlen = criticalPath();
        scanf("%d", &k);
        while(k--) {
            scanf("%d%d", &u, &v);
            printf("%d %d\n", e[u][v], l[u][v]);
        }
        printf("%d\n", maxlen);
        for(int i = 1; i <= n; i++) {
            if(inDegree[i] == 0 && activity[i].size() != 0)
                DFS(i);
        }
    } else
        printf("NO\n");
    return 0;
}
