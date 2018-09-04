#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 1010;
struct Edge {
    int v, w;
    Edge(){}
    Edge(int _v, int _w) {
        v = _v; w = _w;
    }
};
vector<Edge> G[MAXN];   // 邻接表
vector<int> activity[MAXN];     // 关键活动
// 顶点数、边数、入度、入度备份、最早时间、最晚时间
int n, m, inDegree[MAXN] = {0}, inDegreeOrigin[MAXN] = {0}, ve[MAXN], vl[MAXN];

// 拓扑序列
stack<int> topOrder;
// 拓扑排序，顺便求 ve 数组
bool topologicalSort() {
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(inDegree[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        topOrder.push(u); // 将 u 加入拓扑序列 
        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i].v; // u的i号后继结点编号为v
            inDegree[v]--;
            if(inDegree[v] == 0) {
                q.push(v);
            }
            // 用 ve[u]来更新 u 的所有后继结点 v
            if(ve[u] + G[u][i].w > ve[v]) {
                ve[v] = ve[u] + G[u][i].w;
            }
        }
   }
   if(topOrder.size() == n) return true;
   else return false;
}

// 关键路径，不是有向无环图返回-1，否则返回关键路径长度
int CriticalPath() {
    memset(ve, 0, sizeof(ve)); // ve数组初始化
    if(topologicalSort() == false) {
        return -1; // 不是有向无环图，返回-1
    }
    int maxLength = 0;
    for(int i = 0; i < n; i++) {
        if(ve[i] > maxLength) {
            maxLength = ve[i];  // 多汇点时取最长
        }
    }
    fill(vl, vl + n, maxLength); // vl数组初始化，初始值为汇点的ve值
    // 直接使用 topOrder 出栈即为逆拓扑序列，求解 vl 数组
    while(!topOrder.empty()) {
        int u = topOrder.top(); // 栈顶元素为 u
        topOrder.pop();
        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i].v; // u的后继结点v // 用 u 的所有后继结点 v 的 vl 值来更新 vl[u]
            if(vl[v] - G[u][i].w < vl[u]) {
                vl[u] = vl[v] - G[u][i].w;
            }
        }
    }
    // 遍历邻接表的所有边，计算活动的最早开始时间 e 和最迟开始时间 l
    for(int u = 0; u < n; u++) {
        for(int i = 0; i < G[u].size() ; i++) {
            int v = G[u][i].v, w = G[u][i].w;
            // 活动的最早开始时间 e 和最迟开始时间 l
            int e = ve[u], l = vl[v] - w;
            // 如果 e==l，说明活动 u->v 是关键活动
            if(e == l) {
                activity[u].push_back(v);   // 保存关键活动
            }
        }
    }
    return maxLength; // 返回关键路径长度
}

vector<int> criticalPath;   // 关键路径
void printCriticalPath(int u) {     // 输出关键路径
    if(activity[u].size() == 0) {   // 到关键路径末端
        criticalPath.push_back(u);
        for(int i = 0; i < criticalPath.size(); i++) {  // 输出关键路径
            printf("%d", criticalPath[i]);
            if(i < criticalPath.size() - 1) {
                printf("->");
            } else {
                printf("\n");
            }
        }
        criticalPath.pop_back();
        return;
    }
    criticalPath.push_back(u);
    sort(activity[u].begin(), activity[u].end());   // 把关键活动的v端排序
    for(int i = 0; i < activity[u].size(); i++) {
        printCriticalPath(activity[u][i]);  // 递归输出
    }
    criticalPath.pop_back();
}

int main() {
    // freopen("8.in", "r", stdin);
    // freopen("8.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(Edge(v, w));
        inDegree[v]++;  // 统计入度
        inDegreeOrigin[v]++;
    }
    int criticalTime = CriticalPath();  // 求关键路径
    if(criticalTime == -1) {
        printf("NO %d\n", n - (int)topOrder.size());    // 不在有向无环图中的结点数目
    } else {
        printf("YES %d\n", criticalTime);
        for(int i = 0; i < n; i++) {    // 从小到大遍历结点
            if(inDegreeOrigin[i] == 0 && activity[i].size() != 0) {     // 如果是关键路径起点
                printCriticalPath(i);   // 输出以i号结点开头的关键路径
            }
        }
    }
    return 0;
}

