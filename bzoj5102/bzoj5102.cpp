#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 2000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int l,r,id;
}s[MAXN];

int n,k,ans,anspos;
int a[MAXN],cnt[MAXN];

void pushdown(int pos){
	if(a[pos*2]<a[pos] || a[pos*2+1]<a[pos]){
		if(a[pos*2]<a[pos*2+1]) swap(cnt[pos*2],cnt[pos]),swap(a[pos*2],a[pos]),pushdown(pos*2);
		else swap(cnt[pos*2+1],cnt[pos]),swap(a[pos*2+1],a[pos]),pushdown(pos*2+1);
	}
}

void push(int x,int id){
	pushdown(1);
	if(x>a[1]) a[1]=x,cnt[1]=id;
	pushdown(1);
}

bool cmp(const edge &a,const edge &b){
	return a.l<b.l;
}

int main(){
    freopen("bzoj5102.in","r",stdin);
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++)
    	scanf("%d %d",&s[i].l,&s[i].r),s[i].id=i;
    sort(s+1,s+1+n,cmp);
    memset(a,0x7f,sizeof(a));
    for(int i=1;i<=k;i++) a[i]=0;
    for(int i=1;i<=n;i++){
    	push(s[i].r,s[i].id);
    	if(i>=k && a[1]>s[i].l){
    		if(a[1]-s[i].l>ans)
    			ans=a[1]-s[i].l,anspos=i;
    	}
    }
    memset(a,0x7f,sizeof(a));
    for(int i=1;i<=k;i++) a[i]=0;
    for(int i=1;i<=anspos;i++)
    	push(s[i].r,s[i].id);
    printf("%d\n",ans);
    for(int i=1;i<=k;i++) printf("%d ",cnt[i]);
    return 0;
}