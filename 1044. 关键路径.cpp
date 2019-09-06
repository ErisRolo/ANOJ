/**
* ��������ͳ�㷨���ؼ�·����˼·����
*       �����������ж��Ƿ�ΪDAG�����������ͬʱ����������У���ջ�洢���������ve���飬��ve[v]=max(ve[v],ve[u]+g[u][v])
*       Ȼ�����ؼ�·�����Ȼ�ȡ���ve��Ҳ�ǹؼ�·���ܳ��ȣ�����vl�����ʼ��Ϊvl��Ȼ�����vl���飬��vl[u]=min(vl[u],vl[v]-g[u][v])
*       ֮�����e�����l���飬��e[u][v]=ve[u]��l[u][v]=vl[v]-g[u][v]��e��l�൱�ļ�Ϊ�ؼ������vector<int> activity[maxn]�洢
*       ���Ҫ���������ӡ·���Ļ�����DFS����ͼһ���������ݹ�߽�Ϊactivity[u].size()==0�������Ĳ���Ϊ���Ϊ0��activity[i].size()!=0�Ķ���
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

struct Node {
    int v, w;
};

int n, m, u, v, w, k;
vector<Node> adj[maxn];
int indegree[maxn], inDegree[maxn]; //��� ��ȱ���
int ve[maxn], vl[maxn]; //�������ʱ�� �������ʱ��
int e[maxn][maxn], l[maxn][maxn]; //�ߵ�����ʱ�� �ߵ�����ʱ��
vector<int> activity[maxn]; //�ؼ�� �൱��dp�汾���choice

stack<int> topo; //��ջ�洢�������� �������������������
bool topoSort() { //�������� �����ve����
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
//			//���ve
//			if(ve[u]+adj[u][i].w>ve[v])
//				ve[v]=ve[u]+adj[u][i].w;
            ve[v] = max(ve[v], ve[u] + adj[u][i].w); //��ٵ� ��������
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
//			maxve=ve[i]; //����ʱȡ�
//	}
    int maxve = *max_element(ve + 1, ve + n + 1); //�������ve
    fill(vl + 1, vl + n + 1, maxve); //vl�����ʼ�� ��ʼֵΪ����veֵ
    while(!topo.empty()) { //topo��ջ��Ϊ���������У����vl����
        int u = topo.top();
        topo.pop();
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].v;
//			//���vl
//			if(vl[v]-adj[u][i].w<vl[u])
//				vl[u]=vl[v]-adj[u][i].w;
            vl[u] = min(vl[u], vl[v] - adj[u][i].w); //����� ������С��
        }
    }
    for(int u = 1; u <= n; u++) {
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].v, w = adj[u][i].w;
            e[u][v] = ve[u]; //��������翪ʼʱ��e ����������¼������翪ʼʱ��
            l[u][v] = vl[v] - w; //�������ٿ�ʼʱ��l ���������¼�����ٿ�ʼʱ���ȥ�ʹ��ʱ��
            if(e[u][v] == l[u][v])
                activity[u].push_back(v); //��������Ϊ�ؼ��
        }
    }
    return maxve;
}

vector<int> path; //�ؼ�·��
void DFS(int u) {
    if(activity[u].size() == 0) {
        path.push_back(u);
        for(int i = 0; i < path.size(); i++) {  //����ؼ�·��
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
    sort(activity[u].begin(), activity[u].end()); //������Ҫ
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
