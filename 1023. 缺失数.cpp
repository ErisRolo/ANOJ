/**
* 分析：最后一个点容易卡时间，输入LL会慢，改成字符数组，会快很多 
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
			h[atoi(s)]=true; //最终结果一定不大于10^7，所以只处理部分数字，不过其实PAT是禁用atoi的，然而PAT也不会考上界这么大的数
	}
	for(int i=1; i<=n+1; i++) { //最终结果为1到n+1之间 
		if(h[i]==false) {
			printf("%d",i);
			break;
		}
	}
	return 0;
}
