#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 60
typedef long long ll;

int a[MAXN][MAXN],n,m,ans1;

int lowbit(int x){
	return x&-x;
}

int cnt(int mask){
	int sum=0;
	for(int i=mask;i;i-=lowbit(i))
		sum++;
	return sum;
}

int cal(int row,int mask){
	int res=0;
	for(int i=1;i<=row;i++){
		if(mask&1) res+=a[row][i];
		mask>>=1;
	}
	return res;
}

void solve1(){
	int f[2][1200][40];
	int ans=-1;
	memset(f,-1,sizeof(f));
	for(int i=0;i<=(1<<n)-1;i++){
		f[n%2][i][cnt(i)]=cal(n,i);
		ans=max(ans,f[n%2][i][cnt(i)]);
	}
	for(int i=n-1;i>=1;i--){
		memset(f[i%2],-1,sizeof(f[i%2]));
		for(int j=0;j<=(1<<n)-1;j++)
			for(int k=0;k<=(1<<(n+1))-1;k++)
				for(int t=0;t<=m;t++){
					if((k&(j|(j<<1)))==(j|(j<<1))){
						if(t-cnt(j)>=0 && f[(i+1)%2][k][t-cnt(j)]!=-1){
							f[i%2][j][t]=max(f[i%2][j][t],f[(i+1)%2][k][t-cnt(j)]+cal(i,j));
							ans=max(ans,f[i%2][j][t]);
						}
					}
				}
	}
	cout<<ans;
}

void dfs(int x,ll mask,int sum,int num){
	ans1=max(ans1,sum);
	if(x==0 || num==m) return;
	for(ll i=0;i<(1<<x);i++){
		if(num+cnt(i)>m) continue;
		if((mask&(i|(i<<1)))==(i|(i<<1)))
			dfs(x-1,i,sum+cal(x,i),num+cnt(i));
	}
}

void solve2(){
	dfs(n,(ll)(1<<(n+1))-1,0,0);
	cout<<ans1;
}

int main(){
    freopen("block.in","r",stdin);
    freopen("block.out","w",stdout); 
    cin>>n>>m;
    for(int i=n;i>=1;i--)
    	for(int j=1;j<=i;j++)
    		scanf("%d",&a[i][j]);
   	if(n<=10) solve1();
    else solve2();
    return 0;
}