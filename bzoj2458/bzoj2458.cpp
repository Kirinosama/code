#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define eps 1e-7
#define MAXN 200010
#define ii pair<int,int>
#define INF 1e10
typedef long long ll;

struct point{
	int x,y;
}p[MAXN],v[MAXN];

double ans;
int n;

bool cmp1(const point &a,const point &b){
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}

bool cmp2(const point &a,const point &b){
	if(a.y==b.y) return a.x<b.x;
	return a.y<b.y;
}

double dis(const point &a,const point &b){
	return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}

void solve(int l,int r){
	if(r-l+1<3) return;
	int mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	int cnt=0;
	for(int i=mid;i>=l;i--){
		if(p[mid].x-p[i].x>ans/2+eps)
			break;
		v[++cnt]=p[i];
	}
	for(int i=mid+1;i<=r;i++){
		if(p[i].x-p[mid].x>ans/2+eps)
			break;
		v[++cnt]=p[i];
	}
	sort(v+1,v+cnt+1,cmp2);
	int L=1,R=1;
	while(cnt-L+1>=3){
		while(R+1<=cnt && v[R+1].y-v[L].y<=ans/2+eps)
			R++;
		for(int i=L;i<=R-2;i++)
			for(int j=i+1;j<=R-1;j++)
				for(int k=j+1;k<=R;k++)
					ans=min(ans,dis(v[i],v[j])+dis(v[i],v[k])+dis(v[j],v[k]));
		L++;
	}
}


int main(){
    freopen("bzoj2458.in","r",stdin);
    scanf("%d",&n);ans=INF;
    for(int i=1;i<=n;i++)
    	scanf("%d %d",&p[i].x,&p[i].y);
    sort(p+1,p+1+n,cmp1);
    solve(1,n);
    printf("%.6lf",ans);
    return 0;
}