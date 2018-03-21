#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 30010
#define ls son[x][0]
#define rs son[x][1]
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,w[MAXN],sum[MAXN],son[MAXN][2];
int fa[MAXN],rev[MAXN],father[MAXN];

int wh(int x){
	return son[fa[x]][1]==x;
}

bool isroot(int x){
	return son[fa[x]][0]!=x && son[fa[x]][1]!=x;
}

void push_down(int x){
	if(rev[x]){
		swap(ls,rs);
		rev[ls]^=1,rev[rs]^=1;
		rev[x]=0;
	}
}

void push_up(int x){
	if(!isroot(x)) push_up(fa[x]);
	push_down(x);
}

void update(int x){
	sum[x]=sum[ls]+sum[rs]+w[x];
}

void rot(int x){
	int f=fa[x],g=fa[f];
	int c=wh(x);
	son[f][c]=son[x][!c];
	fa[son[x][!c]]=f;
	if(!isroot(f)) son[g][wh(f)]=x;
	fa[x]=g;
	fa[f]=x,son[x][!c]=f;
	update(f),update(x);
}

void splay(int x){
	push_up(x);
	for(;!isroot(x);rot(x))
		if(!isroot(fa[x]))
			rot(wh(fa[x])==wh(x)?fa[x]:x);
}

void access(int x){
	for(int t=0;x;t=x,x=fa[x]){
		splay(x),son[x][1]=t,update(x);
	}
}

void makeroot(int x){
	access(x),splay(x);
	rev[x]^=1;
}

void link(int x,int y){
	makeroot(x);
	fa[x]=y;
}

int find(int x){
	access(x),splay(x);
	while(ls) x=ls;
	return x;
}

void solve(){
	char ch[20];int x,y;
	scanf("%s %d %d",ch,&x,&y);
	switch(ch[0]){
		case 'b':
			if(find(x)==find(y)) printf("no\n");
			else printf("yes\n"),link(x,y);
			break;
		case 'p':
			splay(x);w[x]=y,update(x);
			break;
		case 'e':
			if(find(x)==find(y)){
				makeroot(x),access(y),splay(y);
				printf("%d\n",sum[y]);
			}
			else printf("impossible\n");
	}
}

int main(){
    freopen("bzoj2843.in","r",stdin);
   	cin>>n;
   	for(int i=1;i<=n;i++)
   		scanf("%d",&w[i]),sum[i]=w[i];
   	cin>>m;
   	while(m--) solve();
    return 0;
}