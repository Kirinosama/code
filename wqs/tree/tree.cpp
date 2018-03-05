#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int a[MAXN],tot,cnt,n,l[MAXN],r[MAXN],t[MAXN];
int c[MAXN],c1[MAXN],ti,ls[MAXN],rs[MAXN];
ll ans;

int lowbit(int x){
	return x&-x;
}

void add(int *c,int x,int k){
	for(int i=x;i<=n;i+=lowbit(i)) c[i]+=k;
}

int getsum(int *c,int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=c[i];
	return res;
}

int init(){
	int cur=++ti;
	int c;tot=max(tot,cur);
	scanf("%d",&c);
	t[cur]=c;l[cur]=cnt+1;
	if(!c){
		ls[cur]=init();rs[cur]=init();
		r[cur]=cnt;
	}else{
		a[++cnt]=c;
		l[cur]=r[cur]=cnt;
	} 
	return cur;
}

void dfs(int x){
	if(t[x])return;
	dfs(ls[x]);dfs(rs[x]);
	ll all=(ll)(r[ls[x]]-l[ls[x]]+1)*(ll)(r[rs[x]]-l[rs[x]]+1);
	ll lcnt=0;
	for(int i=l[ls[x]];i<=r[ls[x]];i++) add(c1,a[i],1);
	for(int i=l[rs[x]];i<=r[rs[x]];i++)	lcnt+=getsum(c1,a[i]-1);
	ll rcnt=all-lcnt;
	if(lcnt<rcnt) ans-=rcnt-lcnt;
	for(int i=l[ls[x]];i<=r[ls[x]];i++) add(c1,a[i],-1);
}

void premake(){
	for(int i=1;i<=n;i++){
		add(c,a[i],1);ans+=a[i]-1-getsum(c,a[i]-1);
	}
}

int main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    cin>>n;
    init();
    premake();
    dfs(1);
    cout<<ans;
    return 0;
}