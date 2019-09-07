/**
* 分析：判断AVL与CBT，综合训练了DFS BFS 和 downAdjust
*       坑点在于heap不能在输入时直接存储，而应该在BFS时存储，因为结点1不一定是根结点，需要对建成的树重新编号  
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 21;

int n,root;
int heap[maxn];
bool isRoot[maxn];

struct Node {
	int data,lchild,rchild;
	int height,level;
} node[maxn];

int getHeight(int root) {
	if(root==-1)
		return 0;
	else
		return node[root].height;
}

void updateHeight(int root) {
	node[root].height=max(getHeight(node[root].lchild),getHeight(node[root].rchild))+1;
}

int getBalanceFactor(int root) {
	return getHeight(node[root].lchild)-getHeight(node[root].rchild);
}

int notbalance=0;
void DFS(int root) {
	if(root==-1)
		return;
	if(node[root].lchild==-1&&node[root].rchild==-1) {
		updateHeight(root);
		return;
	}
	DFS(node[root].lchild);
	DFS(node[root].rchild);
	updateHeight(root);
	if(abs(getBalanceFactor(root))>1)
		notbalance++;
}

bool iscbt=true;
int maxlevel=1,level[maxn];
void BFS(int root) {
	bool flag=false;
	queue<int> q;
	q.push(root);
	node[root].level=1;
	level[1]=1;
	int cnt=1;
	while(!q.empty()) {
		int front=q.front();
		q.pop();
		heap[cnt++]=node[front].data;
		int l=node[front].lchild,r=node[front].rchild;
		maxlevel=max(maxlevel,node[front].level);
		if(flag==false) {
			if((l!=-1&&r==-1)||(l==-1&&r==-1))
				flag=true;
		} else {
			if(l!=-1||r!=-1)
				iscbt=false;
		}
		if(l==-1&&r!=-1)
			iscbt=false;
		if(l!=-1) {
			q.push(l);
			node[l].level=node[front].level+1;
			level[node[l].level]++;
		}
		if(r!=-1) {
			q.push(r);
			node[r].level=node[front].level+1;
			level[node[r].level]++;
		}
	}
}

int num=0;
void downAdjust(int low,int high) {
	int i=low,j=i*2;
	while(j<=high) {
		if(j+1<=high&&heap[j+1]>heap[j])
			j=j+1;
		if(heap[j]>heap[i]) {
			swap(heap[i],heap[j]);
			num++;
			i=j;
			j=i*2;
		} else {
			break;
		}
	}
}
;
void createHeap() {
	for(int i=n/2; i>=1; i--)
		downAdjust(i,n);
}

int main() {
	fill(isRoot,isRoot+maxn,true);
	string a,b;
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		scanf("%d",&node[i].data);
		heap[i]=node[i].data;
	}
	for(int i=1; i<=n; i++) {
		cin>>a>>b;
		if(a!="-") {
			node[i].lchild=stoi(a);
			isRoot[stoi(a)]=false;
		} else
			node[i].lchild=-1;
		if(b!="-") {
			node[i].rchild=stoi(b);
			isRoot[stoi(b)]=false;
		} else
			node[i].rchild=-1;
	}
	for(int i=1; i<=n; i++) {
		if(isRoot[i]) {
			root=i;
			break;
		}
	}
	DFS(root);
	if(notbalance!=0) {
		printf("NOT AVL TREE!!!\n%d\n",notbalance);
	} else {
		BFS(root);
		if(!iscbt) {
			printf("NOT COMPLETE TREE!!!\n");
			for(int i=maxlevel; i>=1; i--) {
				if(level[i]==pow(2,i-1)) {
					printf("%d\n",i);
					break;
				}
			}
		} else {
			printf("OHHHHH HEAP!!!\n");
			createHeap();
			printf("%d\n",num);
		}
	}
	return 0;
}
