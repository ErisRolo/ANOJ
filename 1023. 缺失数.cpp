/**
* ���������һ�������׿�ʱ�䣬����LL�������ĳ��ַ����飬���ܶ� 
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000010;

bool h[maxn];

int main() {
	int n;
	char s[20];
	scanf("%d",&n);
	for(int i=0; i<n; i++) {
		scanf("%s",s);
		if(s[0]!='-'&&strlen(s)<=7)
			h[atoi(s)]=true; //���ս��һ��������10^7������ֻ���������֣�������ʵPAT�ǽ���atoi�ģ�Ȼ��PATҲ���ῼ�Ͻ���ô�����
	}
	for(int i=1; i<=n+1; i++) { //���ս��Ϊ1��n+1֮�� 
		if(h[i]==false) {
			printf("%d",i);
			break;
		}
	}
	return 0;
}
