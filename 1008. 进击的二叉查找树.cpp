/**
* 分析：判断两棵BST是否一致，直接建树解决
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 62;

int n,x,ra=-1,rb=-1;
int posta[maxn],postb[maxn],layera[maxn],layerb[maxn];

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

void postorder(int root,int post[]) {
	if(root==-1)
		return;
	postorder(node[root].lchild,post);
	postorder(node[root].rchild,post);
	post[idx++]=node[root].data;
}

void BFS(int root,int layer[]) {
	queue<int> q;
	q.push(root);
	while(!q.empty()) {
		int front=q.front();
		q.pop();
		layer[idx++]=node[front].data;
		if(node[front].lchild!=-1)
			q.push(node[front].lchild);
		if(node[front].rchild!=-1)
			q.push(node[front].rchild);
	}
}

bool isEqual(int a[],int b[]) {
	for(int i=1; i<=n; i++) {
		if(a[i]!=b[i])
			return false;
	}
	return true;
}

int main() {
	scanf("%d",&n);
	for(int i=0; i<n; i++) {
		scanf("%d",&x);
		insert(ra,x);
	}
	for(int i=0; i<n; i++) {
		scanf("%d",&x);
		insert(rb,x);
	}
	idx=0;
	postorder(ra,posta);
	idx=0;
	postorder(rb,postb);
	idx=0;
	BFS(ra,layera);
	idx=0;
	BFS(rb,layerb);
	if(isEqual(posta,postb)&&isEqual(layera,layera))
		printf("YES\n");
	else
		printf("NO\n");
	for(int i=0; i<n; i++) {
		printf("%d",posta[i]);
		if(i!=n-1)
			printf(" ");
		else
			printf("\n");
	}
	for(int i=0; i<n; i++) {
		printf("%d",layera[i]);
		if(i!=n-1)
			printf(" ");
		else
			printf("\n");
	}
	return 0;
}
