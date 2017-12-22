#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100010
#define LOGN 300

struct node{
	node *ch[2];
	int val,deep;
}*root;

int cnt,n,k;
vector <node*> v[LOGN+20];

void build(node *& p,int l,int r){
	if(!p){
		p=new node();
		cnt++;p->ch[0]=p->ch[1]=NULL;
		if(l==r-1) p->val=1,p->deep=0;
		else p->val=0;
	}
	if(r!=l+1){
		int mid=(l+r)>>1;
		build(p->ch[0],l,mid);
		build(p->ch[1],mid,r);
		p->deep=max(p->ch[0]->deep,p->ch[1]->deep)+1;
	}
	v[p->deep].push_back(p);
}

void print(node* p,int l,int r,int ll,int rr){
	if(p->val==1){
		for(int i=ll;i<=rr;i++) printf("%d ",i);
		return ;
	}
	else{
		int mid=(l+r)>>1;
		print(p->ch[0],l,mid,rr+1+l-mid,rr);
		print(p->ch[1],mid,r,ll,ll+r-mid-1);
	}

}

void solve(){
	for(int i=1;i<=LOGN;i++){
		for(int j=0;j<v[i].size();j++){
			if(cnt==k) break;
			else cnt-=2,v[i][j]->val=1;
		}
		if(cnt==k) break;
	}
	print(root,0,n,1,n);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&k);
	build(root,0,n);
	if((!(k&1)) || k>cnt) cout<<-1;
	else solve();
	return 0;
}