#include <bits/stdc++.h>
using namespace std;

#define MOD 239

int n,k;
int f[100010][31];

int main(){
	cin>>n>>k;
	f[1][1]=1;
	for(int i=1;i<n;i++){
		for(int j=1;j<=k;j++){
			f[i+1][j]+=(f[i][j]*j*2)%MOD;
			f[i+1][j+1]+=(f[i][j]*(i+1-j*2))%MOD;
			f[i+1][j]%=MOD,f[i+1][j+1]%=MOD;
		}
	}
	cout<<f[n][k];
	return 0;
}
