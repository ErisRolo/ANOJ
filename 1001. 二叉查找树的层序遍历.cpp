/**
* ·ÖÎö£ºbst
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n,x,root=-1;

struct Node {
	int data,lchild,rchild;
} node[maxn];

int idx=0;
void insert(int &root,int x) {
	if(root==-1) {
		node[idx].data=x;
		node[idx].lchild=node[idx].rchild=-1;
		root=idx++;
		return;
	}
	if(x<node[root].data)
		insert(node[root].lchild,x);
	else
		insert(node[root].rchild,x);
}

int cnt=0;
void BFS(int root) {
	queue<int> q;
	q.push(root);
	while(!q.empty()) {
		int front=q.front();
		q.pop();
		printf("%d",node[front].data);
		cnt++;
		if(cnt!=n)
			printf(" ");
		else
			printf("\n");
		if(node[front].lchild!=-1)
			q.push(node[front].lchild);
		if(node[front].rchild!=-1)
			q.push(node[front].rchild);
	}
}

int main() {
	scanf("%d",&n);
	for(int i=0; i<n; i++) {
		scanf("%d",&x);
		insert(root,x);
	}
	BFS(root);
	return 0;
}
