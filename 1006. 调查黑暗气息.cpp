/**
* 分析：最短路径+BFS，注意round是四舍五入，ceil才是向上取整 
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;
const int inf = 1000000000;

int n,m,l,k,s,t;
int g[maxn][maxn];
int level[maxn],eng[maxn];

int d[maxn];
bool vis[maxn];
vector<int> pre[maxn];
void Dijkstra(int s) {
	fill(d,d+maxn,inf);
	d[s]=0;
	for(int i=0; i<n; i++) {
		int u=-1,min=inf;
		for(int j=0; j<n; j++) {
			if(vis[j]==false&&d[j]<min) {
				u=j;
				min=d[j];
			}
		}
		if(u==-1)
			return;
		vis[u]=true;
		for(int v=0; v<n; v++) {
			if(vis[v]==false&&g[u][v]!=inf) {
				if(d[u]+g[u][v]<d[v]) {
					d[v]=d[u]+g[u][v];
					pre[v].clear();
					pre[v].push_back(u);
				} else if(d[u]+g[u][v]==d[v]) {
					pre[v].push_back(u);
				}
			}
		}
	}
}

int num=0,maxeng=-1,mineng=inf;
vector<int> path,temppath;
void DFS(int v) {
	if(v==s) {
		temppath.push_back(v);
		num++;
		int teng=0,seng=0;
		int city=temppath.size()/2;
		for(int i=temppath.size()-1; i>=0; i--) {
			int id=temppath[i];
			teng+=eng[id];
		}
		teng%=k; //直接用总辐射取模 
		for(int i=0; i<city; i++) {
			int id=temppath[i];
			seng+=eng[id];
		}
		if(teng>maxeng) {
			path=temppath;
			maxeng=teng;
			mineng=seng;
		} else if(teng==maxeng&&seng<mineng) {
			path=temppath;
			mineng=seng;
		}
		temppath.pop_back();
		return;
	}
	temppath.push_back(v);
	for(int i=0; i<pre[v].size(); i++)
		DFS(pre[v][i]);
	temppath.pop_back();
}

bool inq[maxn];
void BFS(int s) {
	queue<int> q;
	q.push(s);
	inq[s]=true;
	level[s]=0;
	while(!q.empty()) {
		int front=q.front();
		q.pop();
		if(level[front]<=l) {
			double p=(100-100.0/l*level[front])*0.01;
			eng[front]+=(int)(ceil(eng[front]*p));
		}
		for(int i=0; i<n; i++) {
			if(g[front][i]!=inf) {
				if(inq[i]==false) {
					q.push(i);
					inq[i]=true;
					level[i]=level[front]+1;
				}
			}
		}
	}
}

int main() {
	fill(g[0],g[0]+maxn*maxn,inf);
	int u,v,w;
	scanf("%d%d%d%d%d%d",&n,&m,&l,&k,&s,&t);
	for(int i=0; i<n; i++)
		scanf("%d",&eng[i]);
	for(int i=0; i<m; i++) {
		scanf("%d%d%d",&u,&v,&w);
		g[u][v]=g[v][u]=w;
	}
	Dijkstra(s);
	BFS(s);
	DFS(t);
	if(path.size()!=0) {
		printf("%d %d %d %d\n",num,d[t],maxeng,mineng);
		for(int i=path.size()-1; i>=0; i--) {
			printf("%d",path[i]);
			if(i!=0)
				printf("->");
			else
				printf("\n");
		}
	} else {
		printf("-1\n");
	}
	return 0;
}
