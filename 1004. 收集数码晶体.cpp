/**
* �����������S���յ�T����ΪL��·�����������Ҫ��mod 1000000007
*       �����ڽӾ����L���ݣ���������ʹ��long long������ʱҲҪmod 1000000007������������Ϊ����
**/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 60;
const LL mod = 1000000007;

int n,m,l,a,b,k;
LL g[maxn][maxn],temp[maxn][maxn],ans[maxn][maxn];

//n�׾����L����
void MatrixPow(int n,int l) {
	for(int i=0; i<maxn; i++)
		ans[i][i]=1;
	for(int cnt=0; cnt<l; cnt++) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				temp[i][j]=0;
				for(int k=0; k<n; k++) {
					//temp[i][j]=temp[i][j]+ans[i][k]*g[k][j];
					temp[i][j]=(temp[i][j]+(ans[i][k]*g[k][j]%mod+mod))%mod;
				}
			}
		}
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				ans[i][j]=temp[i][j];
			}
		}
	}
}

int main() {
	scanf("%d%d%d",&n,&m,&l);
	for(int i=0; i<m; i++) {
		scanf("%d%d",&a,&b);
		g[a][b]=1;
	}
	MatrixPow(n,l);
	scanf("%d",&k);
	while(k--) {
		scanf("%d%d",&a,&b);
		printf("%lld\n",(ans[a][b]%mod+mod)%mod);
	}
	return 0;
}
