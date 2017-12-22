#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int a[MAXN],n,m,l,ans;

int cal(int mid){
	int last=1,cnt=0;
	for(int i=2;i<=n;i++){
		if(a[i]-a[last]<mid)
			cnt++;
		else last=i;
	}
	return cnt;
}

int main(){
    freopen("bzoj1650.in","r",stdin);
    scanf("%d %d %d",&l,&n,&m);
    a[1]=0,a[2]=l,n+=2;
    for(int i=3;i<=n;i++)
    	scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    int l=1,r=a[n]-a[1];
    while(l<=r){
    	int mid=(l+r)>>1;
    	if(cal(mid)<=m) l=mid+1,ans=mid;
    	else r=mid-1;
    }
    printf("%d",ans);
    return 0;
}