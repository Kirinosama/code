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

int n,m,q,a[MAXN],pre[MAXN],last[MAXN];
int c[MAXN],ans[MAXN];

struct seg{
	int l,r,id;
}s[MAXN];

bool cmp(const seg &a,const seg &b){
	return a.r<b.r;
}

int lowbit(int x){
	return x&-x;
}

void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i))
		c[i]+=k;
}

int getsum(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=c[i];
	return res;
}

int main(){
    freopen("bzoj2743.in","r",stdin);
    scanf("%d %d %d",&n,&m,&q);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	pre[i]=last[a[i]];
    	last[a[i]]=i;
    }
    for(int i=1;i<=q;i++)
    	scanf("%d%d",&s[i].l,&s[i].r),s[i].id=i;
    sort(s+1,s+1+q,cmp);
    int pos=1;
    for(int i=1;i<=q;i++){
    	while(pos<=s[i].r){
    		if(pre[pre[pos]]) add(pre[pre[pos]],-1);
    		if(pre[pos]) add(pre[pos],1);
    		pos++;
    	}
    	ans[s[i].id]=getsum(s[i].r)-getsum(s[i].l-1);
    }
    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    return 0;
}