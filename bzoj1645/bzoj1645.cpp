#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

#define MAXN 40010
#define length(x) (mp2[x->r]-mp2[x->l])
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,maxlen;
map <ll,int> mp1;
map <int,ll> mp2;
vector <ll> v;

struct node{
	node *ch[2];
	ll sum,h;
	int l,r;
	void maintain(){
		if(h!=-1){
			if(ch[0]){
				ch[0]->h=h;
				ch[0]->sum=length(ch[0])*h;
			}
			if(ch[1]){
				ch[1]->h=h;
				ch[1]->sum=length(ch[1])*h;
			}
		}
	}
	void update(){
		sum=0;
		if(ch[0]) sum+=ch[0]->sum;
		if(ch[1]) sum+=ch[1]->sum;
	}
}*root;

struct data{
	ll x,y,h;
}t[MAXN];

bool cmp(const data &a,const data &b){
	return a.h<b.h;
}

void build(node *&p,int l,int r){
	p=new node;
	p->ch[0]=p->ch[1]=NULL;
	p->sum=p->h=0;p->l=l;p->r=r;
	if(l+1!=r){
		int mid=(l+r)>>1;
		build(p->ch[0],l,mid);
		build(p->ch[1],mid,r);
	}
}

void insert(node *&p,int L,int R,ll h){
	if(!p) return;
	if(p->l>=R || p->r<=L) return;
	else if(p->l>=L && p->r<=R){
		p->h=h;p->sum=length(p)*h;
		return;
	}
	else if(p->l+1!=p->r){
		p->maintain();
		p->h=-1;
		insert(p->ch[0],L,R,h);
		insert(p->ch[1],L,R,h);
		p->update();
	}
}

int main(){
    freopen("bzoj1645.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%lld %lld %lld",&t[i].x,&t[i].y,&t[i].h);
    	v.push_back(t[i].x);v.push_back(t[i].y);
    }
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++)
    	if(!mp1[v[i]]){
    		mp1[v[i]]=++maxlen;
    		mp2[maxlen]=v[i];
    	}
    build(root,1,maxlen);
    sort(t+1,t+n+1,cmp);
    for(int i=1;i<=n;i++)
    	insert(root,mp1[t[i].x],mp1[t[i].y],t[i].h);
    printf("%lld",root->sum);
    return 0;
}