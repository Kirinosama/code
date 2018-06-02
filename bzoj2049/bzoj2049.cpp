#include <bits/stdc++.h>
using namespace std;

#define MAXN 20010

int fa[MAXN],ch[MAXN][2],rev[MAXN];
int n,m;

int isroot(int x){
	if(!fa[x]) return 1;
	return ch[fa[x]][1]!=x && ch[fa[x]][0]!=x;
}

int wh(int x){
	return ch[fa[x]][1]==x;
}

void rot(int x){
	int f=fa[x],g=fa[f],c=wh(x);
	ch[f][c]=ch[x][!c];
	if(ch[f][c])fa[ch[f][c]]=f;
	if(!isroot(f)) ch[g][wh(f)]=x;
	fa[x]=g;fa[f]=x;ch[x][!c]=f;
}

void pushdown(int x){
	if(rev[x]){
		swap(ch[x][0],ch[x][1]);
		if(ch[x][0])rev[ch[x][0]]^=1;
		if(ch[x][1])rev[ch[x][1]]^=1;
		rev[x]=0;
	}
}

void pushup(int x){
	if(fa[x]) pushup(fa[x]);
	pushdown(x);
}

void splay(int x){
	pushup(x);
	for(;!isroot(x);rot(x))
		if(!isroot(fa[x]))
			rot(wh(fa[x])==wh(x)?fa[x]:x);
}

void access(int x){
	for(int p=0;x;p=x,x=fa[x]){
		splay(x),ch[x][1]=p;
	}
}

void makeroot(int x){
	access(x);splay(x);
	rev[x]^=1;
}

int find(int x){
	access(x),splay(x);
	int tmp=x;
	while(ch[tmp][0])
		tmp=ch[tmp][0];
	return tmp;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		char opt[10];int x,y;
		scanf("%s %d %d",opt,&x,&y);
		switch(opt[0]){
			case 'Q':printf("%s\n",find(x)==find(y)?"Yes":"No");break;
			case 'C':if(find(x)!=find(y))makeroot(x),fa[x]=y;break;
			case 'D':makeroot(x),access(y),splay(y);if(ch[y][0]==x)fa[x]=ch[y][0]=0;
		}
	}
	return 0;
}

