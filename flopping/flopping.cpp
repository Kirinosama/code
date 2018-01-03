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

int ans,sum[MAXN][MAXN];
int n,m,xmin,ymin,k;
int a[MAXN][MAXN];

int sqr(int lx,int ly,int rx,int ry){
	return sum[rx][ry]+sum[lx-1][ly-1]-sum[rx][ly-1]-sum[lx-1][ry];
}

int cal(int power){
	int sum=0,res;
	for(int i=1;i<=n-xmin+1;i++)
		for(int j=1;j<=m-ymin+1;j++)
			for(int k=i+xmin-1;k<=n;k++){
				res=0;
				int L=j+ymin-1,R=m;
				while(L<=R){
					int mid=(L+R)>>1;
					if(sqr(i,j,k,mid)<power) res=mid,L=mid+1;
					else R=mid-1;
				}
				if(res) sum+=res-(j+ymin-1)+1;
				else break;
			}
	return sum;
}

int main(){
    freopen("flopping.in","r",stdin);
    cin>>n>>m>>xmin>>ymin>>k;
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++){
    		scanf("%d",&a[i][j]);
    		sum[i][j]=sum[i][j-1]+a[i][j];
    	}
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		sum[i][j]+=sum[i-1][j];
    int L=0,R=sum[n][m];
    while(L<=R){
    	int mid=(L+R)>>1;
    	if(cal(mid)>=k) ans=mid,R=mid-1;
    	else L=mid+1;
    }
    cout<<ans;
    return 0;
}