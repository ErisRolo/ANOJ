/**
* ·ÖÎö£º¼òµ¥ÅÅĞò 
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 310; 

int a,b,c,d,l,n,cnt=0;

struct student {
	string id;
	int a,b,c,d,sum;
} stu[maxn];

bool cmp(student x,student y) {
	if(x.sum!=y.sum)
		return x.sum>y.sum;
	else
		return x.id<y.id;
}

int main() {
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&l);
	scanf("%d",&n);
	for(int i=0; i<n; i++) {
		cin>>stu[i].id;
		scanf("%d%d%d%d",&stu[i].a,&stu[i].b,&stu[i].c,&stu[i].d);
		stu[i].sum=stu[i].a+stu[i].b+stu[i].c+stu[i].d;
		if(stu[i].a>=a&&stu[i].b>=b&&stu[i].c>=c&&stu[i].d>=d&&stu[i].sum>=l)
			cnt++;
	}
	sort(stu,stu+n,cmp);
	printf("%d\n",cnt);
	for(int i=0; i<n; i++) {
		if(stu[i].a>=a&&stu[i].b>=b&&stu[i].c>=c&&stu[i].d>=d&&stu[i].sum>=l) {
			printf("%s %d\n",stu[i].id.c_str(),stu[i].sum);
		}
	}
	return 0;
}
