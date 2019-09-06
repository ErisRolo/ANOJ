/**
* 分析：层序中序建树，然后BFS和DFS，码量多一点但思路还算简单，就是从上往下看有点麻烦
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 31;

int n,x,root=-1;
int in[maxn];
vector<int> layer;

struct Node {
	int data,lchild,rchild;
	int level;
} node[maxn];

int idx=0;
int create(vector<int> layer,int inl,int inr) {
	if(layer.size()==0)
		return -1;
	int root=idx++;
	node[root].data=layer[0];
	int k;
	for(k=inl; k<=inr; k++) {
		if(in[k]==layer[0])
			break;
	}
	vector<int> left,right;
	for(int i=1; i<layer.size(); i++) {
		bool isleft=false;
		for(int j=inl; j<k; j++) {
			if(layer[i]==in[j]) {
				isleft=true;
				break;
			}
		}
		if(isleft)
			left.push_back(layer[i]);
		else
			right.push_back(layer[i]);
	}
	node[root].lchild=create(left,inl,k-1);
	node[root].rchild=create(right,k+1,inr);
	return root;
}

int c1=0;
void preorder(int root) {
	if(root==-1)
		return;
	printf("%d",node[root].data);
	c1++;
	if(c1!=n)
		printf(" ");
	else
		printf("\n");
	preorder(node[root].lchild);
	preorder(node[root].rchild);
}

int c2=0;
void postorder(int root) {
	if(root==-1)
		return;
	postorder(node[root].lchild);
	postorder(node[root].rchild);
	printf("%d",node[root].data);
	c2++;
	if(c2!=n)
		printf(" ");
	else
		printf("\n");
}

int n1=0;
void BFS(int root) {
	queue<int> q;
	q.push(root);
	node[root].level=1;
	while(!q.empty()) {
		int front=q.front();
		q.pop();
		n1=max(n1,node[front].level);
		if(node[front].lchild!=-1) {
			q.push(node[front].lchild);
			node[node[front].lchild].level=node[front].level+1;
		}
		if(node[front].rchild!=-1) {
			q.push(node[front].rchild);
			node[node[front].rchild].level=node[front].level+1;
		}
	}
}

int n2=0;
void DFSR(int root,int r) {
	if(root==-1)
		return;
	n2=max(n2,r);
	DFSR(node[root].lchild,r);
	DFSR(node[root].rchild,r+1);
}

//int n3=0,l=0,r=0;
//void DFS(int root,int left,int right) {
//	if(root==-1)
//		return;
//	l=max(l,left);
//	r=max(r,right);
//	DFS(node[root].lchild,left+1,right);
//	DFS(node[root].rchild,left,right+1);
//}

int n3=0,l=0,r=0;
void DFS(int root,int cnt) {
	if(root==-1)
		return;
	l=min(l,cnt);
	r=max(r,cnt);
	DFS(node[root].lchild,cnt-1);
	DFS(node[root].rchild,cnt+1);
}

int main() {
	scanf("%d",&n);
	for(int i=0; i<n; i++) {
		scanf("%d",&x);
		layer.push_back(x);
	}
	for(int i=0; i<n; i++)
		scanf("%d",&in[i]);
	root=create(layer,0,n-1);
	preorder(root);
	postorder(root);
	BFS(root);
	printf("%d\n",n1);
	DFSR(root,1);
	printf("%d\n",n2);
//	DFS(root,0,0);
//	n3=l+r+1;
	DFS(root,0);
	n3=abs(l)+r+1;
	printf("%d\n",n3);
	return 0;
}
