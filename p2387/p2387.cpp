#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ch(x,y) (y?rs[x]:ls[x])
#define MAXN 150010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
	int x,y,a,b;
	bool operator < (const edge &c)const{
		if(a==c.a) return b<c.b;
		return a<c.a;
	}
}E[MAXN];

int n,m;
int rev[MAXN],mx[MAXN],val[MAXN],ls[MAXN],rs[MAXN],fa[MAXN];

void maintain(int x){
	mx[x]=x;
	if(val[mx[ls[x]]]>val[mx[x]]) mx[x]=mx[ls[x]];
	if(val[mx[rs[x]]]>val[mx[x]]) mx[x]=mx[rs[x]];
}

void pushdown(int x){
	if(rev[x]){
		if(ls[x]) rev[ls[x]]^=1;
		if(rs[x]) rev[rs[x]]^=1;
		swap(ls[x],rs[x]);
		rev[x]=0;
	}
}

bool isroot(int x){
	return !fa[x] || (ls[fa[x]]!=x && rs[fa[x]]!=x);
}

void pushup(int x){
	if(!isroot(x))
		pushup(fa[x]);
	pushdown(x);
}

int wh(int x){
	return rs[fa[x]]==x;
}

void rot(int x){
	int f=fa[x],g=fa[f],c=wh(x);
	ch(f,c)=ch(x,!c);fa[ch(f,c)]=f;
	fa[x]=g;if(!isroot(f)) ch(g,wh(f))=x;
	ch(x,!c)=f;fa[f]=x;
	maintain(f),maintain(x);
}

void splay(int x){
	pushup(x);
	for(;!isroot(x);rot(x)){
		if(!isroot(fa[x]) && !isroot(fa[fa[x]]))
			rot(wh(fa[x])==wh(x)?fa[x]:x);
	}
}

void access(int x){
	for(int cur=0;x;cur=x,x=fa[x]){
		splay(x);rs[x]=cur;maintain(x);
	}
}

void makeroot(int x){
	access(x);splay(x);rev[x]^=1;
}

int find(int x){
	access(x);splay(x);
	while(ls[x]) x=ls[x];
	return x;
}

void cut(int x,int y){
	makeroot(x);access(y);splay(y);
	ls[y]=fa[x]=0;
	maintain(y);
}

void link(int x,int y){
	makeroot(x);fa[x]=y;
}

void solve(){
	int ans=INF;
	for(int i=1;i<=m;i++){
		if(find(E[i].x)==find(E[i].y)){
			makeroot(E[i].x);access(E[i].y);splay(E[i].y);
			int t=mx[E[i].y];
			if(val[t]>E[i].b){
				cut(t,E[t-n].x),cut(t,E[t-n].y);
				link(i+n,E[i].x);link(i+n,E[i].y);
			}
		}
		else link(i+n,E[i].x),link(i+n,E[i].y);
		if(find(1)==find(n)){
			makeroot(1);access(n);splay(n);
			ans=min(ans,E[i].a+val[mx[n]]);
		}
	}
	printf("%d",ans==INF?-1:ans);
}

int main(){
    freopen("p2387.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
    	scanf("%d%d%d%d",&E[i].x,&E[i].y,&E[i].a,&E[i].b);
    }
    sort(E+1,E+m+1);
    for(int i=1;i<=m;i++) val[i+n]=E[i].b;
 	for(int i=1;i<=n+m;i++) mx[i]=i;
    solve();
    return 0;
}