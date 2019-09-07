/**
* ·ÖÎö£ºnext[i] Ëãµ½i-1 
**/

#include <bits/stdc++.h>
using namespace std;

int main() {
	string s,ts;
	int n,ans=0;
	cin>>s>>n;
	s=s.substr(0,n);
	ts=s;
	reverse(ts.begin(),ts.end());
	for(int i=1; i<n; i++) {
		if(i!=s.size()) {
			string s1=s.substr(0,i);
			string s2=ts.substr(0,i);
			reverse(s2.begin(),s2.end());
			if(s1==s2)
				ans=max(ans,i);
		}
	}
	printf("%d\n",ans);
	return 0;
}
