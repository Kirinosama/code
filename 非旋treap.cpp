#include <bits/stdc++.h>
using namespace std;

#define nn pair<node*,node*>
#define Size(x) (x?x->size:0)
int n;

struct node{
	node *ls,*rs;
	int size,val,pri;
	void maintain(){
		size=1;
		if(ls)size+=ls->size;
		if(rs)size+=rs->size;
	}
}*rt;

node* newnode(int x){
	node *p=new node;
	p->size=1;
	p->ls=p->rs=NULL;
	p->val=x,p->pri=rand();
	return p;
}

node *merge(node *x,node *y){
	if(!x) return y;
	if(!y) return x;
	if(x->pri<y->pri){
		x->rs=merge(x->rs,y);
		x->maintain();
		return x;
	}else{
		y->ls=merge(x,y->ls);
		y->maintain();
		return y;
	}
}

nn split(node *p,int k){
	if(!p) return nn(NULL,NULL);
	nn res;
	if(Size(p->ls)>=k){
		res=split(p->ls,k);
		p->ls=res.second;
		p->maintain();
		res.second=p;
	}else{
		res=split(p->rs,k-Size(p->ls)-1);
		p->rs=res.first;
		p->maintain();
		res.first=p;
	}
	return res;
}

int getrank(int x){
	node *p=rt;
	int sum=0;
	while(p){
		if(p->val<=x) sum+=Size(p->ls)+1,p=p->rs;
		else p=p->ls;
	}
	return sum;
}

int whatisrank(int x){
	node *p=rt;
	while(1){
		int lcnt=Size(p->ls);
		if(x==lcnt+1) return p->val;
		else if(x<=lcnt) p=p->ls;
		else p=p->rs,x-=lcnt+1;
	}
}

void add(int x){
	nn cur=split(rt,getrank(x));
	rt=merge(cur.first,newnode(x));
	rt=merge(rt,cur.second);
}

void del(int x){
	int k=getrank(x);
	nn cur=split(rt,k);
	rt=merge(split(cur.first,k-1).first,cur.second);
}

void print(node *p){
	if(!p) return;
	print(p->ls);
	printf("%d ",p->val);
	print(p->rs);
}

int main(){
	freopen("input","r",stdin);
	srand(1223);
	cin>>n;rt=NULL;
	while(n--){
		int x,y;
		scanf("%d%d",&x,&y);
		switch(x){
			case 1:add(y);break;
			case 2:del(y);break;
			case 3:printf("%d\n",getrank(y-1)+1);break;
			case 4:printf("%d\n",whatisrank(y));break;
			case 5:printf("%d\n",whatisrank(getrank(y-1)));break;
			case 6:printf("%d\n",whatisrank(getrank(y)+1));
		}
	}
	return 0;
}
