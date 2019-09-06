/**
* 分析：丸十哥哥的水题。。。 
**/

#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	int n1=0,n2=0;
	cin>>s;
	for(int i=0; i<s.size(); i++) {
		n1+=s[i]-'0';
		n2+=(s[i]-'0')*(s[i]-'0');
	}
	if(s=="120"||n1==120||n2==120)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
