#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 2010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m;
int A[MAXN][MAXN],B[MAXN][MAXN];

void solve(){
	ll sum=0;int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	int x1=min(a,c),x2=max(a,c);
	int y1=min(b,d),y2=max(b,d);
	for(int i=1;i<=n;i++)
		sum+=(ll)(A[x2][i]-A[x1-1][i])*(ll)(B[i][y2]-B[i][y1-1]);
	printf("%lld\n",sum);
}

int main(){
    freopen("bzoj2901.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++){
    		scanf("%d",&A[i][j]);
    		A[i][j]+=A[i-1][j];
    	}
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++){
    		scanf("%d",&B[i][j]);	
    		B[i][j]+=B[i][j-1];
 		}
 	while(m--)
 		solve();
    return 0;
}
