#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 51061
#define ls son[x][0]
#define rs son[x][1]
#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

unsigned int sum[MAXN],add[MAXN],mul[MAXN],val[MAXN];
int n,q,fa[MAXN],rev[MAXN],size[MAXN];
int son[MAXN][2];

void update(int x){
	size[x]=(size[ls]+size[rs]+1)%MOD;
	sum[x]=(sum[ls]+sum[rs]+val[x])%MOD;
}

bool isroot(int x){
	return son[fa[x]][1]!=x && son[fa[x]][0]!=x;
}

int wh(int x){ 
	return son[fa[x]][1]==x?1:0;
}

void make(int x,int Add,int Mul){
	val[x]=(val[x]*Mul+Add)%MOD;
	sum[x]=(sum[x]*Mul+size[x]*Add)%MOD;
	mul[x]=(mul[x]*Mul)%MOD;
	add[x]=(add[x]*Mul)%MOD;
	add[x]=(add[x]+Add)%MOD;
}

void push_down(int x){
	if(rev[x]){
		swap(ls,rs);
		rev[ls]^=1;
		rev[rs]^=1;
		rev[x]=0;
	}
	if(add[x] || mul[x]!=1){
		make(ls,add[x],mul[x]);
		make(rs,add[x],mul[x]);
	}
	mul[x]=1,add[x]=0;
}

void push_up(int x){
	if(!isroot(x)) push_up(fa[x]);
	push_down(x);
}

void rot(int x){
	int f=fa[x],g=fa[f];
	int c=wh(x);
	son[f][c]=son[x][!c];
	fa[son[x][!c]]=f;
	if(!isroot(f)) son[g][wh(f)]=x;
	fa[x]=g;
	son[x][!c]=f,fa[f]=x;
	update(f),update(x);
}

void splay(int x){
	push_up(x);
	//printf("splay %d:\n",x);
	for(;!isroot(x);rot(x))
		if(!isroot(fa[x]))
			rot(wh(x)==wh(fa[x])?fa[x]:x);
}

void access(int x){
	for(int t=0;x;t=x,x=fa[x])
		splay(x),son[x][1]=t,update(x);
}

void makeroot(int x){
	access(x),splay(x);rev[x]^=1;
}

void del(int x,int y){
	makeroot(x);
	access(y),splay(y);
	son[y][0]=fa[x]=0;
	update(y);
}

void link(int x,int y){
	makeroot(x);
	fa[x]=y;
}

void solve(){
	char ch[5];
	int u1,v1,u2,v2,x;
	scanf("%s",ch);
	switch(ch[0]){
		case '+':
			scanf("%d %d %d",&u1,&v1,&x);
			makeroot(u1),access(v1),splay(v1),make(v1,x,1);
			break;
		case '-':
			scanf("%d %d %d %d",&u1,&v1,&u2,&v2);
			del(u1,v1),link(u2,v2);
			break;
		case '*':
			scanf("%d %d %d",&u1,&v1,&x);
			makeroot(u1),access(v1),splay(v1),make(v1,0,x);
			break;
		case '/':
			scanf("%d %d",&u1,&v1);
			makeroot(u1),access(v1),splay(v1),printf("%u\n",sum[v1]);
	}
}

int main(){
    freopen("bzoj2631.in","r",stdin);
    freopen("bzoj2631.out","w",stdout);
    cin>>n>>q;
    for(int i=1;i<=n;i++) size[i]=sum[i]=val[i]=1;
    for(int i=1;i<n;i++){
    	static int x,y;
    	scanf("%d %d",&x,&y);
    	link(x,y);
    }
    while(q--)
    	solve();
    return 0;
}