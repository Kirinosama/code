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

int f[MAXN][1<<20];
int n,num[MAXN],mask[MAXN],w[MAXN];
int a[MAXN][MAXN],ans;

int lowbit(int x){
	return x&-x;
}

int cnt(int mask){
	int res=0;
	while(mask)
		res++,mask-=lowbit(mask);
	return res;
}

int main(){
    freopen("z.in","r",stdin);
    freopen("z.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
    	scanf("%d",&num[i]);
    	for(int j=1;j<=num[i];j++)
    		scanf("%d",&a[i][j]),mask[i]|=(1<<(a[i][j]-1));
    }
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    for(int j=0;j<=n;j++)
    	for(int k=0;k<(1<<n);k++)
    		f[j][k]=INF;
    f[0][0]=0;
    for(int i=0;i<n;i++)
    	for(int j=i;j>=0;j--){
	    	for(int k=(1<<n)-1;k>=0;k--){
	    		int to=k|mask[i+1];
	    		if(f[j][k]!=INF){
	    			f[j+1][to]=min(f[j+1][to],f[j][k]+w[i+1]);
	    			if(j+1==cnt(to)) ans=min(ans,f[j+1][to]);
	    		}
	    	}
	    }
	cout<<ans;
    return 0;
}