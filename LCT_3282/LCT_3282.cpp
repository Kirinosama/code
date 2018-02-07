#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 300010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int rev[MAXN],sum[MAXN],a[MAXN],ch[2][MAXN],fa[MAXN];
int n,m;

void maintain(int x){
	sum[x]=a[x];
	if(ch[0][x]) sum[x]^=sum[ch[0][x]];
	if(ch[1][x]) sum[x]^=sum[ch[1][x]];
}

void pushdown(int x){
	if(rev[x]){
		rev[x]=0;
		swap(ch[0][ch[0][x]],ch[1][ch[0][x]]),rev[ch[0][x]]^=1;
		swap(ch[0][ch[1][x]],ch[1][ch[1][x]]),rev[ch[1][x]]^=1;
	}
}

void pushup(int x){
	if(fa[x]) pushup(fa[x]);
	pushdown(x);
}

bool isroot(int x){
	return ch[0][fa[x]]!=x && ch[1][fa[x]]!=x;
}

int wh(int x){
	return ch[1][fa[x]]==x;
}

void rot(int x){
	int f=fa[x],g=fa[f],c=wh(x);
	if(!isroot(f)) ch[wh(f)][g]=x;
	fa[x]=g;
	ch[c][f]=ch[!c][x];fa[ch[c][f]]=f;
	ch[!c][x]=f;fa[f]=x;
	maintain(f),maintain(x);
}

void splay(int x){
	pushup(x);
	for(;!isroot(x);rot(x)){
		if(!isroot(fa[x]))
			rot(wh(fa[x])==wh(x)?fa[x]:x);
	}
}

void access(int x){
	for(int c=0;x;c=x,x=fa[x]){
		splay(x);ch[1][x]=c;maintain(x);
	}
}

void makeroot(int x){
	access(x);splay(x);
	swap(ch[0][x],ch[1][x]);rev[x]^=1;
}

void solve(){
	static int c,x,y;
	scanf("%d%d%d",&c,&x,&y);
	switch(c){
		case 0:
			makeroot(x);access(y);splay(y);
			printf("%d\n",sum[y]);
			break;
		case 1:
			makeroot(x);access(y);splay(y);
			if(ch[0][y]!=x) fa[x]=y;
			break;
		case 2:
			makeroot(x);access(y);splay(y);
			if(ch[0][y]==x){
				ch[0][y]=fa[x]=0;maintain(y);
			}break;
		case 3:
			access(x);splay(x);a[x]=y;maintain(x);
	}
}

int main(){
    freopen("LCT_3282.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	sum[i]=a[i];
    }
    while(m--)solve();
    return 0;
}