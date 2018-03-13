#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	node *ch[2];
	int cnt,sum,key;
	ll val;
	node(){ch[0]=ch[1]=NULL;cnt=sum=val=0;key=rand();}
	node(int x){ch[0]=ch[1]=NULL;cnt=sum=1;val=x;key=rand();}
	void maintain(){
		sum=cnt;
		if(ch[0]) sum+=ch[0]->sum;
		if(ch[1]) sum+=ch[1]->sum;
	}
}*root;

int n,m;
ll a[30010];

node * rot(node *p,int c){
	node *q=p->ch[c];
	p->ch[c]=q->ch[!c];
	q->ch[!c]=p;
	p->maintain();q->maintain();
	return q;
}

void insert(node *&p,ll x){
	if(!p){
		p=new node(x);
		return;
	}
	p->sum++;
	if(p->val==x) p->cnt++;
	else if(x<p->val){
		insert(ls,x);
		if(ls->key<p->key) p=rot(p,0);
	}else{
		insert(rs,x);
		if(rs->key<p->key) p=rot(p,1);
	}
}

node* del(node *p,ll x){
	if(p->val==x){
		if(p->cnt)p->cnt--,p->sum--;
		if(!p->cnt){
			if(!ls) p=rs;
			else if(!rs) p=ls;
			else{
				if(ls->key<rs->key) p=rot(p,0),rs=del(rs,x);
				else p=rot(p,1),ls=del(ls,x);
				p->maintain();
			}
		}
	}else{
		p->ch[x>p->val]=del(p->ch[x>p->val],x);
		p->maintain();
	}
	if(!p) return p;
	if(ls && rs){
		if(ls->key<rs->key && ls->key<p->key) p=rot(p,0);
		else if(rs->key<rs->key && rs->key<p->key) p=rot(p,1);
	}else if(rs && rs->key<p->key){
		p=rot(p,1);
	}
	else if(ls && ls->key<p->key){
		p=rot(p,0);
	}
	return p;
}

ll whrank(int x){
	node *p=root;
	while(p){
		int rcnt=rs?rs->sum:0;
		if(x<=rcnt) p=rs;
		else if(x>rcnt && x<=rcnt+p->cnt) return p->val;
		else x-=rcnt+p->cnt,p=ls;
	}
	return -1;
}

int main(){
    freopen("war.in","r",stdin);
    freopen("war.out","w",stdout);
    cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),insert(root,a[i]);
	cin>>m;
	for(int i=1;i<=m;i++){
		char opt;ll x,y;
		scanf("\n%c %lld ",&opt,&x);
		if(opt!='Q')scanf("%lld",&y);
		switch(opt){
			case 'A':
				root=del(root,a[x]);
				a[x]-=y;if(a[x]>0)insert(root,a[x]);break;
			case 'C':
				root=del(root,a[x]);
				a[x]+=y;insert(root,a[x]);break;
			case 'Q':
				cout<<whrank(x)<<endl;
		}
	}
	printf("%d",root?root->sum:0);
    return 0;
}