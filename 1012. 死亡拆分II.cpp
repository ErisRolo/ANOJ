/**
* ������ʹ��nth_element�������ѡ���㷨��nth_element(d,d+k,d+n)�����ҵ���k��������������Ϊd[0] -d[k-1],d[k]-d[n-1]
**/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 10000010;

LL d[maxn];

int main() {
	int n;
	LL sum=0,s1=0;
	scanf("%d",&n);
	for(int i=0; i<n; i++) {
		scanf("%lld",&d[i]);
		sum+=d[i];
	}
	nth_element(d,d+n/2,d+n); //Ѱ�ҵ�n/2������������з�
	for(int i=0; i<n/2; i++)
		s1+=d[i];
	printf("%d %lld\n",n%2,abs(sum-s1-s1));
	return 0;
}
