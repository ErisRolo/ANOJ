/**
* ·ÖÎö£ºË®Ìâ 
**/

#include <bits/stdc++.h>
using namespace std;

set<char> st;

int main() {
	int n,ans=0;
	string s;
	cin>>n;
	while(n--) {
		cin>>s;
		st.clear();
		for(int i=0; i<s.size(); i++) {
			if(isalpha(s[i]))
				st.insert(s[i]);
		}
		ans+=st.size();
	}
	printf("%d\n",ans);
	return 0;
}
