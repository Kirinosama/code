#include <bits/stdc++.h>
using namespace std;

#define MOD 19911223
#define mul 101

int n,m,Pow[100010],h[100010];
char a[100010];

struct node{
	node *ls,*rs,*fa;
	int	key,pos;
}*rt;

node* newnode(int x){
	node *p=new node;
	p->ls=p->rs=p->fa=NULL;
	p->key=rand(),p->pos=x;
	return p;
}

int get(int l,int r){
	int minus=(h[l-1]*Pow[r-l+1])%MOD;
	return h[r]-minus>=0?h[r]-minus:h[r]-minus+MOD;
}

bool judge(int x,int y){
	if(!y) return false;
	int res,l=0,r=min(x,y)-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(get(x-mid+1,x)==get(y-mid+1,y)) res=mid,l=mid+1;
		else r=mid-1;
	}
	return a[x-res]<a[y-res];
}

node* lrot(node* p){
	node* q=p->ls;
	p->ls=q->rs;
	q->rs=p;
	return q;
}

node* rrot(node* p){
	node* q=p->rs;
	p->rs=q->ls;
	q->ls=p;
	return q;
}

node* add(node *p,int pos){
	if(!p)return newnode(pos);
	if(judge(pos,p->pos)){
		p->ls=add(p->ls,pos);
		if(p->ls->key<p->key)
			p=lrot(p);
	}else{
		p->rs=add(p->rs,pos);
		if(p->rs->key<p->key)
			p=rrot(p);
	}
	return p;
}

void solve(){
	char ch=getchar();
	a[++n]=ch;
	h[n]=(h[n-1]*mul+ch)%MOD;
	rt=add(rt,n);
}

void print(node* p){
	if(!p) return;
	print(p->ls);
	for(int i=p->pos;i>=1;i--)printf("%c",a[i]);
	cout<<endl;
	print(p->rs);
}

int main(){
	freopen("input","r",stdin);
	cin>>m;getchar();
	Pow[0]=1;rt=NULL;
	for(int i=1;i<=100000;i++)Pow[i]=(Pow[i-1]*mul)%MOD;
	while(m--)
		solve();
	print(rt);
	return 0;
}
