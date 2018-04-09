#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010

struct node{
	int x,y,ID;
}p[MAXN];

int n,sum[MAXN],w[MAXN];

bool cmp1(const node &a,const node &b){
	return a.x<b.x;
}

bool cmp2(const node &a,const node &b){
	return a.y<b.y;
}

int main(){
	freopen("bzoj3170.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&p[i].x,&p[i].y);
		int x=p[i].x+p[i].y,y=p[i].x-p[i].y;
		p[i].x=x,p[i].y=y;
		p[i].ID=i;
	}
	sort(p+1,p+n+1,cmp1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+p[i].x;
	for(int i=1;i<=n;i++){
		w[p[i].ID]+=(i-1)*p[i].x-sum[i-1];
		w[p[i].ID]+=sum[n]-sum[i]-(n-i)*p[i].x;
	}
	sort(p+1,p+n+1,cmp2);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+p[i].y;
	for(int i=1;i<=n;i++){
		w[p[i].ID]+=(i-1)*p[i].y-sum[i-1];
		w[p[i].ID]+=sum[n]-sum[i]-(n-i)*p[i].y;
	}
	sort(w+1,w+n+1);
	printf("%d",w[1]/2);
	return 0;
}
