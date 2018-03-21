#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 2000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,len,a[MAXN],b[MAXN],num[MAXN],last[MAXN];
map <int,int> mp1,mp2;

struct node{
	int Min;
	node *ch[2];
	void maintain(){
		Min=min(ch[0]->Min,ch[1]->Min);
	}
}*root[MAXN];

void build(node *&p,int l,int r){
	p=new node;p->Min=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
}

void make(node *&p,node *q,int l,int r,int pos,int k){
	p=new node;p->Min=0;
	if(l==r){
		p->Min=k;
		return;
	}
	else{
		int mid=(l+r)>>1;
		if(pos<=mid){
			rs=q->ch[1];
			make(ls,q->ch[0],l,mid,pos,k);
		}else{
			ls=q->ch[0];
			make(rs,q->ch[1],mid+1,r,pos,k);
		}
		p->maintain();
	}
}

void premake(){
	for(int i=1;i<=n;i++) b[n+i]=a[i]+1;
	b[2*n+1]=0;
	sort(b+1,b+2*n+2);
	for(int i=1;i<=2*n+1;i++)if(!mp1[b[i]]){
		mp1[b[i]]=++len;
		mp2[len]=b[i];
	}	
	build(root[0],1,len);
	for(int i=1;i<=n;i++) make(root[i],root[i-1],1,len,mp1[a[i]],i);
}

int query(node *p,int q,int l,int r){
	if(l==r) return mp2[l];
	else{
		int mid=(l+r)>>1;
		if(ls->Min<q) return query(ls,q,l,mid);
		else return query(rs,q,mid+1,r);
	}
}

int main(){
    freopen("bzoj3585.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
   	premake();
    while(m--){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	printf("%d\n",query(root[y],x,1,len));
    }
    return 0;
}