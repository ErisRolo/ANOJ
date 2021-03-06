/**
* 分析：关键路径 传统算法版
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int inf = 1000000000;

int n, m;
int g[maxn][maxn];
int ve[maxn], vl[maxn];
int e[maxn][maxn], l[maxn][maxn];
int indegree[maxn], inDegree[maxn];
vector<int> activity[maxn];

stack<int> topo;
void topoSort() {
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(indegree[i] == 0)
            q.push(i);
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push(u);
        for(int v = 0; v < n; v++) {
            if(g[u][v] != inf) {
                indegree[v]--;
                if(indegree[v] == 0)
                    q.push(v);
                ve[v] = max(ve[v], ve[u] + g[u][v]);
            }
        }
    }
}

int criticalPath() {
    int maxve = *max_element(ve, ve + n);
    fill(vl, vl + n, maxve);
    while(!topo.empty()) {
        int u = topo.top();
        topo.pop();
        for(int v = 0; v < n; v++) {
            if(g[u][v] != inf) {
                vl[u] = min(vl[u], vl[v] - g[u][v]);
            }
        }
    }
    for(int u = 0; u < n; u++) {
        for(int v = 0; v < n; v++) {
            if(g[u][v] != inf) {
                e[u][v] = ve[u];
                l[u][v] = vl[v] - g[u][v];
                if(e[u][v] == l[u][v])
                    activity[u].push_back(v);
            }
        }
    }
    return maxve;
}

vector<int> path;
void DFS(int v) {
    if(activity[v].size() == 0) {
        path.push_back(v);
        for(int i = 0; i < path.size(); i++) {
            printf("%d", path[i]);
            if(i != path.size() - 1)
                printf("->");
            else
                printf("\n");
        }
        path.pop_back();
        return;
    }
    path.push_back(v);
    for(int i = 0; i < activity[v].size(); i++)
        DFS(activity[v][i]);
    path.pop_back();

}

int main() {
    fill(g[0], g[0] + maxn * maxn, inf);
    int a, b, c;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = c;
        indegree[b]++;
        inDegree[b]++;
    }
    topoSort();
    if(topo.size() == n) {
        printf("YES ");
        int ans = criticalPath();
        printf("%d\n", ans);
        for(int i = 0; i < n; i++) {
            if(inDegree[i] == 0 && activity[i].size() != 0)
                DFS(i);
        }
    } else {
        printf("NO %d\n", n - topo.size());
    }
    return 0;
}




//**
//* 分析：万妖穴-拓扑排序+关键路径（DP版）
//**/
//
//#include <bits/stdc++.h>
//using namespace std;
//const int maxn = 1010;
//const int inf = 100000000;
//
//int n,m;
//int g[maxn][maxn];
//
//int indegree[maxn];
//vector<int> topo;
//int topoSort() {
//	int num=0;
//	queue<int> q;
//	for(int i=0; i<n; i++) {
//		if(indegree[i]==0)
//			q.push(i);
//	}
//	while(!q.empty()) {
//		int u=q.front();
//		q.pop();
//		topo.push_back(u);
//		num++;
//		for(int v=0; v<n; v++) {
//			if(g[u][v]!=inf) {
//				indegree[v]--;
//				if(indegree[v]==0)
//					q.push(v);
//			}
//		}
//	}
//	return num;
//}
//
//int dp[maxn];
//vector<int> choice[maxn];
//int DP(int i) {
//	if(dp[i]>0)
//		return dp[i];
//	for(int j=0; j<n; j++) {
//		if(g[i][j]!=inf) {
//			if(g[i][j]+dp[j]>dp[i]) {
//				dp[i]=g[i][j]+dp[j];
//				choice[i].clear();
//				choice[i].push_back(j);
//			} else if(g[i][j]+dp[j]==dp[i]) {
//				choice[i].push_back(j);
//			}
//		}
//	}
//	return dp[i];
//}
//
//vector<int> path;
//void DFS(int i) {
//	if(choice[i].size()==0) {
//		path.push_back(i);
//		for(int i=0; i<path.size(); i++) {
//			printf("%d",path[i]);
//			if(i!=path.size()-1)
//				printf("->");
//			else
//				printf("\n");
//		}
//		path.pop_back();
//		return;
//	}
//	path.push_back(i);
//	for(auto j:choice[i])
//		DFS(j);
//	path.pop_back();
//}
//
//int main() {
//	fill(g[0],g[0]+maxn*maxn,inf);
//	int a,b,c;
//	scanf("%d%d",&n,&m);
//	for(int i=0; i<m; i++) {
//		scanf("%d%d%d",&a,&b,&c);
//		g[a][b]=c;
//		indegree[b]++;
//	}
//	int num=topoSort();
//	if(num==n) {
//		printf("YES ");
//		int max=-1;
//		vector<int> st;
//		for(auto it=topo.rbegin(); it!=topo.rend(); it++) {
//			int i=*it;
//			if(DP(i)>max) {
//				max=DP(i);
//				st.clear();
//				st.push_back(i);
//			} else if(DP(i)==max) {
//				st.push_back(i);
//			}
//		}
//		printf("%d\n",max);
//		sort(st.begin(),st.end());
//		for(auto i:st)
//			DFS(i);
//	} else
//		printf("NO %d\n",n-num);
//	return 0;
//}
