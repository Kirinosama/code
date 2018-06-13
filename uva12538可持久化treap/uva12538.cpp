#include <bits/stdc++.h>
using namespace std;

#define MAXN 50010
#define nn pair<node*,node*>
#define Size(x) (x?x->size:0)

struct node{
	node *ls,*rs;
	int size,pri;
	char val;
	void maintain(){
		size=1+Size(ls)+Size(rs);
	}
}*rt[MAXN];

int T,d,now;

node* newnode(char x){
	node* p=new node;
	p->val=x;p->size=1,p->pri=rand();
	p->ls=p->rs=NULL;
	return p;
}

node* newnode(node* x){
	node *p= new node;
	if(!x) p=NULL;
	else *p=*x;
	return p;
}

node* merge(node *x,node *y){
	if(!x) return newnode(y);
	if(!y) return newnode(x);
	if(x->pri<y->pri){
		node *p=newnode(x);
		p->rs=merge(p->rs,y);
		p->maintain();
		return p;
	}else{
		node *p=newnode(y);
		p->ls=merge(x,p->ls);
		p->maintain();
		return p;
	}
}

nn split(node *p,int k){
	if(!p) return nn(NULL,NULL);
	nn res;
	if(Size(p->ls)>=k){
		node *q=newnode(p);
		res=split(q->ls,k);
		q->ls=res.second;
		q->maintain();
		res.second=q;
	}else{
		node *q=newnode(p);
		res=split(q->rs,k-Size(p->ls)-1);
		q->rs=res.first;
		q->maintain();
		res.first=q;
	}
	return res;
}

node* build(string s){
	node *tot=NULL;
	for(int i=0;i<s.length();i++)
		tot=merge(tot,newnode(s[i]));
	return tot;
}

void print(node *p){
	if(!p) return;
	print(p->ls);
	printf("%c",p->val);
	if(p->val=='c') d--;
	print(p->rs);
}

void solve(){
	int opt,x,y,z;
	string s;nn cur;
	scanf("%d%d",&opt,&x);
	switch(opt){
		case 1:
			x+=d;cin>>s;now++;
			cur=split(rt[now-1],x);
			rt[now]=merge(merge(cur.first,build(s)),cur.second);
			break;
		case 2:
			scanf("%d",&y);x+=d,y+=d;now++;
			cur=split(rt[now-1],x-1);
			rt[now]=merge(cur.first,split(cur.second,y).second);
			break;
		case 3:
			scanf("%d%d",&y,&z);x+=d,y+=d,z+=d;
			node *k=newnode(rt[x]);
			cur=split(k,y-1);
			print(split(cur.second,z).first);
			cout<<endl;
	}
}

int main(){
	freopen("input","r",stdin);
	srand(1223);
	cin>>T;
	for(int i=1;i<=T;i++)
		solve();
	return 0;
}
