#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll MOD=1e9+7;

int t;

struct matrix{
	int n,m;
	ll num[4][4];
	void clear(){
		n=m=0;
		memset(num,0,sizeof(num));
	}
	matrix operator * (const matrix &b){
		matrix c;c.clear();
		c.n=n,c.m=b.m;
		for(int i=1;i<=c.n;i++)
			for(int j=1;j<=c.m;j++)
				for(int k=1;k<=m;k++)
					c.num[i][j]=(c.num[i][j]+num[i][k]*b.num[k][j])%MOD;
		return c;
	}
}a,b;

matrix Pow(matrix x,int k){
	if(k==1) return x;
	else if(k%2) return x*Pow(x*x,k/2);
	else return Pow(x*x,k/2);
}

void solve(){
	int x;
	scanf("%d",&x);
	if(x<=3){
		cout<<1<<endl;
		return;
	}
	a.clear();a.n=1,a.m=3;
	a.num[1][1]=a.num[1][2]=a.num[1][3]=1;
	b.clear();b.n=b.m=3;
	b.num[1][3]=b.num[2][1]=b.num[3][2]=b.num[3][3]=1;
	matrix c=a*Pow(b,x-3);
	cout<<c.num[1][3]<<endl;
}

int main(){
	freopen("input","r",stdin);
	cin>>t;
	while(t--) solve();
	return 0;
}