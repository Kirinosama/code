#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,ch[MAXN],c[MAXN],p[MAXN],pre[MAXN][MAXN];
ll f[MAXN][MAXN],w[MAXN][MAXN];

int main(){
    freopen("diablo.in","r",stdin);
    freopen("diablo.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	scanf("%d%d",&c[i],&p[i]);
    	for(int j=1;j<=p[i];j++)scanf("%lld",&w[i][j]);
    }
	memset(f,0xc0,sizeof(f));f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=p[i];j++)
			for(int k=j*c[i];k<=m;k++)if(f[i-1][k-j*c[i]]!=0xc0c0c0c0){
				if(f[i-1][k-j*c[i]]+w[i][j]>f[i][k]){
					f[i][k]=f[i-1][k-j*c[i]]+w[i][j];
					pre[i][k]=j;
				}
			}
	}
	ll ans=0;int last;
	for(int i=0;i<=m;i++)if(f[n][i]>ans){
		ans=f[n][i];
		last=i;
	}
	cout<<ans<<endl;
	for(int i=n;i>=1;i--){
		ch[i]=pre[i][last];
		last-=pre[i][last]*c[i];
	}
	for(int i=1;i<=n;i++) printf("%d\n",ch[i]);
    return 0;
}