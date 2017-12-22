#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 500010
#define MAXM 4*MAXN

struct node{
	int sum;
	node *ch[2];
	void update(){
		sum=0;
		if(ch[0]) sum+=ch[0]->sum;
		if(ch[1]) sum+=ch[1]->sum;
	}
}*root,mem_pool[MAXM],*tail;

int n,m,x,y,type,k;

inline int read()
{
    int X=0,w=1; char ch=0;
    while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}

void add(node *&p,int l,int r,int pos,int k){
	if(!p){
		p=tail++;p->sum=0;p->ch[0]=p->ch[1]=NULL;
	}
	p->sum+=k;
	if(l!=r){
		int mid=(l+r)>>1;
		if(pos<=mid )add(p->ch[0],l,mid,pos,k);
		else add(p->ch[1],mid+1,r,pos,k);
		p->update();
	} 
}

int getsum(node *p,int l,int r,int L,int R){
	if(!p || l>R || r<L) return 0;
	else if(l>=L && r<=R) return p->sum;
	else if(l!=r){
		int mid=(l+r)>>1;
		return getsum(p->ch[0],l,mid,L,R)+getsum(p->ch[1],mid+1,r,L,R);
	}
}

void solve(){
	type=read();
	if(type==1){
		x=read(),k=read();
		add(root,1,n,x,k);
	}
	else{
		x=read(),y=read();
		cout<<getsum(root,1,n,x,y)<<endl;
	}
}

int main()
{
    freopen("P3374_2.in","r",stdin);
    n=read(),m=read();root=NULL;tail=mem_pool;
    for(int i=1;i<=n;i++){
    	x=read();
    	add(root,1,n,i,x);
    }
    while(m--) solve();
    return 0;
}