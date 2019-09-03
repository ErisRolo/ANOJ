/**
* 分析：链表去重
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n,start,address;
bool vis[maxn];

struct Node {
	int address,data,next;
	int order;
} node[maxn];

bool cmp(Node a,Node b){
	return a.order<b.order;
}

int main() {
	for(int i=0; i<maxn; i++)
		node[i].order=maxn;
	scanf("%d%d",&n,&start);
	for(int i=0; i<n; i++) {
		scanf("%d",&address);
		node[address].address=address;
		scanf("%d%d",&node[address].data,&node[address].next);
	}
	int p=start,cnt=0;
	while(p!=-1) {
		if(vis[abs(node[p].data)]==false) {
			node[p].order=cnt++;
			vis[abs(node[p].data)]=true;
		}
		p=node[p].next;
	}
	sort(node,node+maxn,cmp);
	if(cnt!=0) {
		printf("%d %05d\n",cnt,node[0].address);
		for(int i=0; i<cnt; i++) {
			if(i!=cnt-1)
				printf("%05d %d %05d\n",node[i].address,node[i].data,node[i+1].address);
			else
				printf("%05d %d -1\n",node[i].address,node[i].data);
		}
	} else {
		printf("0 -1\n");
	}
	return 0;
}
