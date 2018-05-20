#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MOD=10007;
int n,m,s,mul[10010];
int g[110][110],f[110][110][110];

int main(){
	//freopen("input","r",stdin);
	cin>>n>>m>>s;
	if(n==1 && m==1 && s==0){
		cout<<1;
		return 0;
	}
	g[0][0]=1;
	for(int i=1;i<=max(n,m);i++)
		for(int j=0;j<=s;j++)
			for(int k=0;k<=j;k++)
				g[i][j]=(g[i][j]+g[i-1][j-k])%MOD;
	f[1][1][0]=1;
	for(int sum=2;sum<n+m;sum++){
		for(int i=1;i<n;i++){
			int j=sum-i;
			if(j==m) continue;
			for(int k=0;k<=s;k++){
				for(int add=0;add<=s-k;add++){
					f[i+1][j][k+add]=(f[i+1][j][k+add]+f[i][j][k]*add)%MOD;
					f[i][j+1][k+add]=(f[i][j+1][k+add]+f[i][j][k]*(add+1))%MOD;
				}
			}	
		}
	}
	int ans=0;mul[0]=1;
	for(int i=1;i<=n*m;i++)mul[i]=(mul[i-1]*(s+1))%MOD;
	for(int i=1;i<=n-1;i++){
		int tot=n*m-1-2*(m+i-2)-(n-i);
		for(int k=0;k<=s;k++){
			ans+=(f[i][m][k]*g[n-i][s-k])%MOD*mul[tot];
			ans%=MOD;
		}
	}
	for(int i=1;i<=m-1;i++){
		int tot=n*m-1-2*(n+i-2)-(m-i);
		for(int k=0;k<=s;k++){
			ans+=(f[n][i][k]*g[m-i][s-k])%MOD*mul[tot];
			ans%=MOD;
		}
	}
	cout<<ans;
	return 0;
}
