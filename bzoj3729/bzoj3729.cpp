#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define XOR0(x) (x?x->Xor[0]:0)
#define XOR1(x) (x?x->Xor[1]:0)
#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,L,a[MAXN],ID[MAXN],ti,dfn[MAXN],dep[MAXN];
vector <int> to[MAXN];

struct node{
	node *ch[2],*fa;
	int Xor[2],num;
	node(){ch[0]=ch[1]=fa=NULL,Xor[0]=Xor[1]=0;}
	void maintain(){
		Xor[0]=XOR0(ch[0])^XOR0(ch[1]);
		Xor[1]=XOR1(ch[0])^XOR1(ch[1]);
		Xor[dep[num]&1]^=a[num];
	}
}*root;

void dfs(int x,int f){
	dep[x]=dep[f]+1;dfn[x]=++ti;ID[ti]=x;
	for(int i=0;i<to[x].size();i++)if(to[x][i]!=f)
		dfs(to[x][i],x);
	dfn[x+100000]=++ti;ID[ti]=x+100000;
}

int wh(node *p){
	return p->fa->ch[1]==p;
}

void rot(node *p){
	node *f=p->fa,*g=f->fa;
	int c=wh(p);
	f->ch[c]=p->ch[!c];
	if(f->ch[c]) f->ch[c]->fa=f;
	p->fa=g;if(g) g->ch[wh(f)]=p;
	p->ch[!c]=f;f->fa=p;
	f->maintain();p->maintain();
	if(f==root) p=root;
}

void splay(node *p){
	for(;p!=root;rot(p))
		if(p->fa!=root)
			rot(wh(p)==wh(p->fa)?p:p->fa);
}

void build(node *&p,int l,int r){
	p=new node;
	int mid=(l+r)>>1;p->num=ID[mid];
	p->Xor[dep[ID[mid]]&1]=a[ID[mid]];
	if(l==r) return;
	if(l<mid)build(ls,l,mid-1),ls->fa=p;
	if(r>mid)build(rs,mid+1,r),rs->fa=p;
	p->maintain();
}

int main(){
    freopen("bzoj3729.in","r",stdin);
    scanf("%d%d",&n,&L);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	a[i]%=(L+1);
    }
    for(int i=1;i<n;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	to[x].push_back(y);
    	to[y].push_back(x);
    }
    dfs(1,1);
    build(root,1,ti);
    return 0;
}