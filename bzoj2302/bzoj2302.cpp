#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 310
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int cnt[MAXN],sum[MAXN],n,m,t;
ll f[MAXN][MAXN],MOD;
ll c[MAXN][MAXN];
bool book[MAXN][MAXN];

void premake(){
	for(int i=0;i<=n;i++) c[i][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
}

void solve(){
	int x,y;
	scanf("%d %d %lld",&n,&m,&MOD);
	memset(cnt,0,sizeof(cnt));
	memset(sum,0,sizeof(sum));
	premake();
	for(int i=1;i<=m;i++){
		scanf("%d %d",&x,&y);
		cnt[y]++;
	}
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+cnt[i];
	memset(f,0,sizeof(f));
	memset(book,false,sizeof(book));
	f[0][0]=1;book[0][0]=true;
	for(int i=1;i<=n;i++){
		for(int j=max(max(i,i-1+cnt[i]),sum[i]);j<=n-(sum[n]-sum[i]);j++)
			for(int k=i-1;k<=j-cnt[i];k++){
				f[i][j]=(f[i][j]+f[i-1][k]*c[n-k-(sum[n]-sum[i-1])][j-k-cnt[i]])%MOD;
				if(book[i-1][k]) book[i][j]=true;
			}
	}
	if(!book[n][n]) printf("NO\n");
	else printf("YES %lld\n",f[n][n]);
}

int main(){
    freopen("bzoj2302.in","r",stdin);
    cin>>t;
    while(t--)
    	solve();
    return 0;
}