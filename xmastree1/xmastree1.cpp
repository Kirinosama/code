#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	int sum;
	node *ch[2];
}*root[MAXN];

int n,m,t,col[MAXN],dfn[MAXN],tail[MAXN],cnt,id[MAXN];
int pre[MAXN],last[MAXN],ne[MAXN];
vector <int> to[MAXN];

void dfs(int x,int f){
	dfn[x]=++cnt;id[cnt]=x;
	for(int i=0;i<to[x].size();i++)
		if(to[x][i]!=f)
			dfs(to[x][i],x);
	tail[x]=cnt;
}

int lowbit(int x){
	return x&-x;
}

void update(node *&p,int l,int r,int pos,int k){
	if(!p){
		p=new node;
		p->ch[0]=p->ch[1]=NULL;
		p->sum=0;
	}
	p->sum+=k;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		update(p->ch[0],l,mid,pos,k);
	else
		update(p->ch[1],mid+1,r,pos,k);
}

void premake(){
	dfs(1,1);
	for(int i=1;i<=n;i++){
		int c=col[id[i]];
		pre[i]=last[c];
		ne[last[c]]=i;
		last[c]=i;
		for(int j=i;j<=n;j+=lowbit(j))
			update(root[j],0,n-1,pre[i],1);
	}
}

int Query(node *p,int l,int r,int L,int R){
	if(!p) return 0;
	if(l>=L && r<=R) return p->sum;
	else if(l>R || r<L) return 0;
	else if(l!=r){
		int mid=(l+r)>>1;
		return Query(p->ch[0],l,mid,L,R)+Query(p->ch[1],mid+1,r,L,R);
	}
	return 0;
}

void query(int l,int r){
	int sum=0;
	for(int i=r;i;i-=lowbit(i))
		sum+=Query(root[i],0,n-1,0,l-1);
	for(int i=l-1;i;i-=lowbit(i))
		sum-=Query(root[i],0,n-1,0,l-1);
	printf("%d\n",sum);
}

void solve(){
	int opt,x,l,r;
	scanf("%d",&opt);
	switch(opt){
		case 1:
			scanf("%d %d %d",&x,l,r);
			if(t) x^=lastans,l^=lastans,r^=lastans;
			query()
		case 2:
	}
}

int main(){
    freopen("xmastree1.in","r",stdin);
    scanf("%d %d %d",&n,&m,&t);
   	for(int i=1;i<=n;i++){
   		scanf("%d",&col[i]);
   	}
   	for(int i=1;i<n;i++){
   		static int x,y;
   		scanf("%d %d",&x,&y);
   		to[x].push_back(y);
   		to[y].push_back(x);
   	}
   	premake();
   	while(m--)
   		solve();
    return 0;
}