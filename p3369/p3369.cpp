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
	int cnt,sum,val,key;
	node(){ch[0]=ch[1]=NULL;cnt=sum=val=0;key=rand();}
	node(int x){ch[0]=ch[1]=NULL;cnt=sum=1;val=x;key=rand();}
	void maintain(){
		sum=cnt;
		if(ch[0]) sum+=ch[0]->sum;
		if(ch[1]) sum+=ch[1]->sum;
	}
}*root;

int n;

node * rot(node *p,int c){
	node *q=p->ch[c];
	p->ch[c]=q->ch[!c];
	q->ch[!c]=p;
	p->maintain();q->maintain();
	return q;
}

void insert(node *&p,int x){
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

node* del(node *p,int x){
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

int getrank(int x){
	int tot=0;
	node *p=root;
	while(p){
		if(p->val>=x) p=ls;
		else tot+=(ls?ls->sum:0)+p->cnt,p=rs;
	}
	return tot;
}

int whrank(int x){
	node *p=root;
	while(1){
		int lcnt=ls?ls->sum:0;
		if(x<=lcnt) p=ls;
		else if(x>lcnt && x<=lcnt+p->cnt) return p->val;
		else x-=lcnt+p->cnt,p=rs;
	}
}

int getpre(int x){
	int res=-INF;
	node *p=root;
	while(p){
		if(p->val>=x) p=ls;
		else res=max(res,p->val),p=rs;
	}
	return res;
}

int getsuc(int x){
	int res=INF;
	node *p=root;
	while(p){
		if(p->val<=x) p=rs;
		else res=min(res,p->val),p=ls;
	}
	return res;
}


int main(){
    freopen("p3369.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++){
    	int opt,x;
    	scanf("%d%d",&opt,&x);
    	switch(opt){
    		case 1:insert(root,x);break;
    		case 2:root=del(root,x);break;
    		case 3:cout<<getrank(x)+1<<endl;break;
    		case 4:cout<<whrank(x)<<endl;break;
    		case 5:cout<<getpre(x)<<endl;break;
    		case 6:cout<<getsuc(x)<<endl;
    	}
    }
    return 0;
}