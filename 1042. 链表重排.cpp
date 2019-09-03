/**
* 分析：因为order数组的规律很容易发现，所以不需要temp数组先写新链表，再用order[temp[i]]=i确定顺序
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n,start,address;
int order[maxn];

struct Node {
	int address,data,next;
	int order;
} node[maxn];

bool cmp(Node a,Node b) {
	return a.order<b.order;
}

void getorder(int cnt) {
	int i=1,ord=1;
	while(ord<=cnt) {
		order[i]=ord;
		i++;
		ord+=2;
	}
	ord-=2;
	if(cnt%2==0)
		ord+=1;
	else
		ord-=1;
	while(i<=cnt) {
		order[i]=ord;
		i++;
		ord-=2;
	}
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
		p=node[p].next;
		cnt++;
	}
	getorder(cnt);
	p=start,cnt=0;
	while(p!=-1) {
		node[p].order=order[cnt+1];
		p=node[p].next;
		cnt++;
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
		printf("0 -1");
	}
	return 0;
}
