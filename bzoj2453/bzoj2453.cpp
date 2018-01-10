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

struct node{
	node *ch[2];
	int sum;
}*root[MAXN];

int n,m,a[MAXN],last[MAXN],ne[MAXN],pre[MAXN];

int lowbit(int x){
	return x&-x;
}

void update(node *&p,int l,int r,int pos,int k){
	if(!p){
		p=new node;p->sum=0;
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
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=lowbit(j))
			update(root[j],0,n-1,pre[i],1);
}

int Query(node *p,int l,int r,int L,int R){
	if(!p) return 0;
	if(l>R || r<L) return 0;
	else if(l>=L && r<=R) return p->sum;
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

void change(int x,int y){
	if(last[a[x]]==x){
		last[a[x]]=pre[x];
		ne[pre[x]]=0;
	}
	else{
		ne[pre[x]]=ne[x];
		for(int i=ne[x];i<=n;i+=lowbit(i))
			update(root[i],0,n-1,pre[ne[x]],-1);
		pre[ne[x]]=pre[x];
		for(int i=ne[x];i<=n;i+=lowbit(i))
			update(root[i],0,n-1,pre[ne[x]],1);
	}
	for(int i=x;i<=n;i+=lowbit(i))
		update(root[i],0,n-1,pre[x],-1);
	if(!last[y]){
		last[y]=x;
		pre[x]=0;
	}
	else{
		if(last[y]<x){
			pre[x]=last[y];
			ne[last[y]]=x;
			last[y]=x;
		}
		else{
			for(int i=x+1;i<=n;i++)
				if(a[i]==y && pre[i]<x){
					for(int j=i;j<=n;j+=lowbit(j))
						update(root[j],0,n-1,pre[i],-1);
					pre[x]=pre[i],ne[pre[i]]=x,pre[i]=x;ne[x]=i;
					for(int j=i;j<=n;j+=lowbit(j))
						update(root[j],0,n-1,pre[i],1);
					break;
				}
		}
	}
	for(int i=x;i<=n;i+=lowbit(i))
		update(root[i],0,n-1,pre[x],1);
	a[x]=y;
}

void solve(){
	int x,y;char opt[5];
	scanf("%s %d %d",opt,&x,&y);
	switch(opt[0]){
		case 'Q':
			query(x,y);
			break;
		case 'R':
			change(x,y);
	}
}

int main(){
    freopen("bzoj2453.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	pre[i]=last[a[i]];
    	ne[last[a[i]]]=i;
    	last[a[i]]=i;
    }
    premake();
    while(m--)
    	solve();
    return 0;
}