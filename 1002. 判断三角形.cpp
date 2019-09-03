/**
* ·ÖÎö£ºÅÐ¶ÏÈý½ÇÐÎ
**/

#include <bits/stdc++.h>
using namespace std;

map<string,int> mp;


int main() {
	mp["zero"]=0,mp["one"]=1,mp["two"]=2,mp["three"]=3,mp["four"]=4,mp["five"]=5,mp["six"]=6,mp["seven"]=7,mp["eight"]=8,mp["nine"]=9;
	int n,temp,a,b,c;
	string s;
	for(int i=0; i<3; i++) {
		scanf("%d",&n);
		temp=0;
		while(n--) {
			cin>>s;
			temp=temp*10+mp[s];
		}
		if(i==0)
			a=temp;
		else if(i==1)
			b=temp;
		else if(i==2)
			c=temp;
	}
	if((a+b<=c)||(a+c<=b)||(b+c<=a))
		printf("NO\n");
	else
		printf("YES\n");
	return 0;
}
