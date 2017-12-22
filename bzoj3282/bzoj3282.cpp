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

int a[MAXN],n,m;

struct node{
	node *ch[2],*fa;
	int rev,XOR,val;
	void update(){
		XOR=val;
		if(ch[0]) XOR^=ch[0]->XOR;
		if(ch[1]) XOR^=ch[1]->XOR;
	}
}*p[MAXN],*s[MAXN];

bool isroot(node *cur){
	return (!cur->fa) || ((cur->fa->ch[0]!=cur) && (cur->fa->ch[1]!=cur));
}

void push_down(node *cur){
	if(cur->rev){
		if(cur->ch[0])
			cur->ch[0]->rev^=1;
		if(cur->ch[1])
			cur->ch[1]->rev^=1;
		swap(cur->ch[0],cur->ch[1]);
		cur->rev^=1;
	}
}

void push_up(node *cur){//更新从根到x的这条链
	int top=0;s[++top]=cur;
	while(!isroot(cur)){
		s[++top]=cur->fa;
		cur=cur->fa;
	}
	while(top)
		push_down(s[top--]);
}

int wh(node *cur){
	return cur->fa->ch[1]==cur;
}

void rotate(node *cur){
	node *f=cur->fa;
	node *g=f->fa;
	int c=wh(cur);	
	f->ch[c]=cur->ch[!c];
	if(f->ch[c]) f->ch[c]->fa=f;
	cur->fa=g;if(!isroot(f)) g->ch[wh(f)]=cur;
	cur->ch[!c]=f;f->fa=cur;
	f->update(),cur->update();
}

void splay(node *cur){
	push_up(cur);
	while(!isroot(cur)){
		node *f=cur->fa;
		if(!isroot(f)){
			if(wh(cur)^wh(f)) rotate(cur);
			else rotate(f);
		}
		rotate(cur);
	}
}

void access(node *cur){
	for(node *son=NULL;cur;son=cur,cur=cur->fa){
		splay(cur);cur->ch[1]=son;cur->update();
	}
}	

void premake(){
	for(int i=1;i<=n;i++){
		p[i]=new node;
		p[i]->ch[0]=p[i]->ch[1]=p[i]->fa=NULL;
		p[i]->val=p[i]->XOR=a[i],p[i]->rev=0;
	}
}

void makeroot(node *cur){
	access(cur);
	splay(cur);
	cur->rev^=1;
}	

void query(int x,int y){
	makeroot(p[x]);
	access(p[y]);
	splay(p[y]);
	printf("%d\n",p[y]->XOR);
}

void link(int x,int y){
	makeroot(p[x]);
	p[x]->fa=p[y];
}

void del(int x,int y){
	makeroot(p[x]);
	access(p[y]);
	splay(p[y]);
	if(p[y]->ch[0]==p[x] && (!p[x]->ch[1]))
		p[y]->ch[0]=p[x]->fa=NULL;
}

void change(int x,int y){
	access(p[x]);
	splay(p[x]);
	p[x]->val=y;
	p[x]->update();
}

node* find(int x){
	access(p[x]),splay(p[x]);
	node *cur=p[x];
	while(cur->ch[0])
		cur=cur->ch[0];
	return cur;
}

void solve(){
	int type,x,y;
	scanf("%d %d %d",&type,&x,&y);
	switch(type){
		case 0:query(x,y);break;
		case 1:if(find(x)!=find(y))link(x,y);break;
		case 2:if(find(x)==find(y))del(x,y);break;
		case 3:change(x,y);
	}
}

int main(){
    freopen("bzoj3282.in","r",stdin);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    	scanf("%d",&a[i]);
    premake();
    while(m--)
    	solve();
    return 0;
}