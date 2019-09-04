/**
* 分析：求起点S到终点T长度为L的路径条数，结果要求mod 1000000007
*       即求邻接矩阵的L次幂，数据类型使用long long，求幂时也要mod 1000000007，否则可能溢出为负数
**/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 60;
const LL mod = 1000000007;

int n,m,l,a,b,k;
LL g[maxn][maxn],temp[maxn][maxn],ans[maxn][maxn];

//n阶矩阵的L次幂
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
