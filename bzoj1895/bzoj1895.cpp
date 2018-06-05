#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

//splay模版题
//区间翻转 旋转 最值 插入 删除 

#define MAXN 100010
#define INF 1e9

int n,m,a[MAXN];
map <string,int> mp;

inline int read(){
	int x=0,w=0;char ch;
	while(ch<'0' || ch>'9') 
		w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w ? -x : x;
}
 
struct splay{
	struct node{
		int key,minx,size,rev,add;
		node *fa,*ch[2];
	}*root;
	int get(node *p){
		return p->fa->ch[1]==p;
	}
	void newnode(node *&p){
		p=new node;
		p->key=p->minx=p->size=p->rev=p->add=0;
		p->ch[0]=p->ch[1]=p->fa=NULL;
	}
	void pushdown(node *&p){
		if(p->rev){
			if(p->ch[0]) p->ch[0]->rev^=1;
			if(p->ch[1]) p->ch[1]->rev^=1;
			swap(p->ch[0],p->ch[1]);
			p->rev=0;
		}
		if(p->add!=0){
			if(p->ch[0]){
				p->ch[0]->minx+=p->add;
				p->ch[0]->add+=p->add;
				p->ch[0]->key+=p->add;
			}
			if(p->ch[1]){
				p->ch[1]->minx+=p->add;
				p->ch[1]->add+=p->add;
				p->ch[1]->key+=p->add;
			}
			p->add=0;
		}
	}
	void update(node *&p){
		p->minx=p->key;p->size=1;
		if(p->ch[0]) p->minx=min(p->minx,p->ch[0]->minx);
		if(p->ch[1]) p->minx=min(p->minx,p->ch[1]->minx);
		p->size+=p->ch[0] ? p->ch[0]->size : 0;
		p->size+=p->ch[1] ? p->ch[1]->size : 0;
	}
	void rot(node *&p){
		node *fa=p->fa;node *g=fa->fa;
		pushdown(fa),pushdown(p);
		int k=get(p);
		fa->ch[k]=p->ch[!k];
		if(p->ch[!k]) p->ch[!k]->fa=fa;
		p->fa=g;
		if(g) g->ch[get(fa)]=p;
		p->ch[!k]=fa;
		fa->fa=p;
		update(fa);
		update(p);
	}
	void build(node *&p,int l,int r){
		if(l>r) return;
		int mid=(l+r)>>1;
		if(!p) newnode(p);
		p->key=a[mid];
		build(p->ch[0],l,mid-1);
		build(p->ch[1],mid+1,r);
		if(p->ch[0]) p->ch[0]->fa=p;
		if(p->ch[1]) p->ch[1]->fa=p;
		update(p);
	}
	node *find(node *&p,int k){
		node *cur=root;
		while(cur){
			pushdown(cur);
			int lcnt=cur->ch[0] ? cur->ch[0]->size : 0;
			if(k==lcnt+1) return cur;
			else if(k<=lcnt) cur=cur->ch[0];
			else cur=cur->ch[1],k-=lcnt+1;
		}
		return NULL;
	}
	void Splay(node *x,node *y){
		for(node *fa;(fa=x->fa)!=y;rot(x))
			if(fa->fa!=y)
				rot(get(fa)==get(x) ? fa : x);
		if(!y) root=x;
	}
	void ADD(int x,int y,int z){
		node *aa=find(root,x);
		node *bb=find(root,y+2);
		Splay(aa,NULL);
		Splay(bb,aa);
		root->ch[1]->ch[0]->key+=z;
		root->ch[1]->ch[0]->minx+=z;
		root->ch[1]->ch[0]->add+=z;
		update(root->ch[1]);
		update(root);
	}
	void REVERSE(int x,int y){
		node *aa=find(root,x);
		node *bb=find(root,y+2);
		Splay(aa,NULL);
		Splay(bb,aa);
		root->ch[1]->ch[0]->rev^=1;
	}
	void MIN(int x,int y){
		node *aa=find(root,x);
		node *bb=find(root,y+2);
		Splay(aa,NULL);
		Splay(bb,aa);
		cout<<root->ch[1]->ch[0]->minx<<endl;
	}
	void INSERT(int x,int z){
		node *aa=find(root,x);
		node *bb=find(root,x+1);
		Splay(aa,NULL);
		Splay(bb,aa);
		newnode(bb->ch[0]);
		bb->ch[0]->key=z;bb->ch[0]->fa=bb;
		update(bb->ch[0]);
		update(bb);
		update(aa);
	}
	void DELETE(int x){
		node *aa=find(root,x-1);
		node *bb=find(root,x+1);
		Splay(aa,NULL);
		Splay(bb,aa);
		bb->ch[0]=NULL;
		update(bb),update(aa);
	}
	void print(node *p){
		if(!p) return;
		pushdown(p);
		print(p->ch[0]);
		printf("%d ",p->key);
		print(p->ch[1]);
	}
}t;

void solve(){
	string type;
	int x,y,z;
	cin>>type;
	switch (mp[type]){
		case 1:x=read(),y=read(),z=read();
		if(x>y)swap(x,y);t.ADD(x,y,z);break;
		case 2:x=read(),y=read();
		if(x>y)swap(x,y);t.REVERSE(x,y);break;
		case 3:x=read(),y=read();
		if(x>y)swap(x,y);z=read()%(y-x+1);if(!z) break;
		t.REVERSE(x,y),t.REVERSE(x,x+z-1),t.REVERSE(x+z,y);break;
		case 4:x=read()+1;z=read();t.INSERT(x,z);break;
		case 5:x=read()+1;t.DELETE(x);break;
		case 6:x=read(),y=read();
		if(x>y)swap(x,y);t.MIN(x,y);
	}
}

void init(){
	mp["ADD"]=1;mp["REVERSE"]=2;mp["REVOLVE"]=3;
	mp["INSERT"]=4;mp["DELETE"]=5;mp["MIN"]=6;	
	a[1]=-INF,a[n+2]=INF;t.root=NULL;t.build(t.root,1,n+2);
}

int main(){
    freopen("input","r",stdin);
    //freopen("out1","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++)
    	scanf("%d",&a[i+1]);
    init(); cin>>m;
    while(m--)
    	solve();
   // t.print(t.root);
    return 0;
}
