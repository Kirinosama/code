#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct point{
	int x,y;
}p[MAXN];

int ansx,ansy,n;
ll ans;

bool cmp1(const point &a,const point &b){
	return a.x<b.x;
}

bool cmp2(const point &a,const point &b){
	return a.y<b.y;
}

ll solve(int x,int y){
	ll res=0;
	for(int i=1;i<=n;i++)
		res+=(ll)(abs(p[i].x-x)+abs(p[i].y-y));
	return res;
}

int main(){
    freopen("bzoj3210.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d %d",&p[i].x,&p[i].y);
    	int new1=p[i].x+p[i].y,new2=p[i].x-p[i].y;
    	p[i].x=new1,p[i].y=new2;
    }
    nth_element(p+1,p+(n+1)/2,p+n+1,cmp1); ansx=p[(n+1)/2].x;
    nth_element(p+1,p+(n+1)/2,p+n+1,cmp2); ansy=p[(n+1)/2].y;
    ans=1e18;
    if((ansx&1)==(ansy&1))ans=min(ans,solve(ansx,ansy));
    else{
	    ans=min(ans,solve(ansx-1,ansy));
	    ans=min(ans,solve(ansx+1,ansy));
	    ans=min(ans,solve(ansx,ansy-1));
	    ans=min(ans,solve(ansx,ansy+1));
	}
    printf("%lld",ans/2);
    return 0;
}