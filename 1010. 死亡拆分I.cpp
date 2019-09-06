/**
* 分析：简单数学问题，坑点在于1000个数的和可能超过int，所以要用long long 
**/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1010;

int d[maxn];

int main() {
	int n,n1,n2;
	LL s1=0,s2=0;
	scanf("%d",&n);
	for(int i=0; i<n; i++)
		scanf("%d",&d[i]);
	sort(d,d+n);
	if(n%2==0) {
		n1=n2=n/2;
		for(int i=0; i<n1; i++)
			s1+=d[i];
		for(int i=n1; i<n; i++)
			s2+=d[i];
		printf("%d %lld\n",n1-n2,abs(s1-s2));
	} else {
		int t=n/2;
		if(d[t]<0)
			n1=n/2+1;
		else
			n1=n/2;
		n2=n-n1;
		for(int i=0; i<n1; i++)
			s1+=d[i];
		for(int i=n1; i<n; i++)
			s2+=d[i];
		printf("%d %lld\n",abs(n1-n2),abs(s1-s2));
	}
	return 0;
}
