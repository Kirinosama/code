#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct flower{
	int a,b,c,cnt,less;
}f[MAXN],a[MAXN];

int n,k,c[MAXM],t,ans[MAXN];

bool cmp1(const flower &a,const flower &b){
	if(a.a==b.a){
		if(a.b==b.b)
			return a.c<b.c;
		return a.b<b.b;
	}
	return a.a<b.a;
}

bool cmp2(const flower &a,const flower &b){
	return a.b<b.b;
}

int lowbit(int x){
	return x&-x;
}

void add(int x,int K){
	for(int i=x;i<=k;i+=lowbit(i))
		c[i]+=K;
}

int query(int x){
	int sum=0;
	for(int i=x;i;i-=lowbit(i))
		sum+=c[i];
	return sum;
}

void solve(int l,int r){
	if(l==r)
		return;
	int mid=(l+r)>>1;
	solve(l,mid);solve(mid+1,r);
	sort(f+l,f+1+mid,cmp2);
	sort(f+mid+1,f+1+r,cmp2);
	int x=l,y=mid+1;
	while(x<=mid && y<=r){
		if(f[x].b<=f[y].b){
			add(f[x].c,f[x].cnt);
			a[x]=f[x],x++;
		}
		else{
			f[y].less+=query(f[y].c);
			a[y]=f[y],y++;
		}
	}
	while(x<=mid){
		add(f[x].c,f[x].cnt);
		a[x]=f[x],x++;
	}
	while(y<=r){
		f[y].less+=query(f[y].c);
		a[y]=f[y],y++;
	}
	for(int i=l;i<=mid;i++)
		add(f[i].c,-f[i].cnt);
	for(int i=l;i<=r;i++)
		f[i]=a[i];
}

int main(){
    freopen("bzoj3262.in","r",stdin);
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++){
    	scanf("%d %d %d",&f[i].a,&f[i].b,&f[i].c);
    	f[i].cnt=1;f[i].less=0;
    }
    sort(f+1,f+1+n,cmp1);
    for(int i=1;i<=n;i++){
    	if((f[i].a!=f[t].a) || (f[i].b!=f[t].b) || (f[i].c!=f[t].c))
    		f[++t]=f[i];
    	else f[t].cnt++,f[t].less++;
    }
    solve(1,t);
    for(int i=1;i<=t;i++)
    	ans[f[i].less]+=f[i].cnt;
    for(int i=0;i<n;i++)
    	printf("%d\n",ans[i]);
    return 0;
}