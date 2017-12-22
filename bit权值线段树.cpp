#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define LOGN 20
#define MAXN 250010
#define MAXNN 20*MAXN

struct node
{
	node *ls,*rs;
	int data;
}*root[MAXN],*node1[LOGN],*node2[LOGN],*tail;

node mem_pool[MAXNN];
int n,m,a[MAXN],cnt1,cnt2,MAX_NUM;

inline long long read(){
    long long num=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')    f=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        num=num*10+ch-'0';
        ch=getchar();
    }
    return num*f;
}

int lowbit(int x){
	return x&-x;
}

void insert(node *&p,int l,int r,int x,int num)
{
	if(!p){
		p=tail++;
		p->ls=p->rs=NULL;
		p->data=0;
	}
	p->data+=num;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(x<=mid) insert(p->ls,l,mid,x,num);
	else insert(p->rs,mid+1,r,x,num);
}

int query(int l,int r,int k)
{
	if(l==r) return l;
	int x=0,y=0;
	for(int i=1;i<=cnt2;i++)
		if(node2[i]) x+=node2[i]->ls->data;
	for(int i=1;i<=cnt1;i++)
		if(node1[i]) y+=node1[i]->ls->data;
	int mid=(l+r)>>1;
	if(k<=x-y){
		for(int i=1;i<=cnt1;i++) if(node1[i]) node1[i]=node1[i]->ls;
		for(int i=1;i<=cnt2;i++) if(node2[i]) node2[i]=node2[i]->ls;
		return query(l,mid,k);
	}
	else{
		for(int i=1;i<=cnt1;i++) if(node1[i]) node1[i]=node1[i]->rs;
		for(int i=1;i<=cnt2;i++) if(node2[i]) node2[i]=node2[i]->rs;
		return query(mid+1,r,k-(x-y));
	}
}

void solve()
{
	int type,x,tx,l,r,k;
	type=read();
	if(type==1){
		x=read(),tx=read();
		for(int i=x;i<=n;i+=lowbit(i)){
			insert(root[i],1,MAX_NUM,a[x],-1);
			insert(root[i],1,MAX_NUM,tx,1);
		}
	}
	else{
		l=read(),r=read(),k=read();
		cnt1=0;cnt2=0;
		for(int i=l-1;i;i-=lowbit(i)) node1[++cnt1]=root[i];
		for(int i=r;i;i-=lowbit(i)) node2[++cnt2]=root[i];
		printf("%d\n",query(1,MAX_NUM,k));
	}
}

void init()
{
	tail=mem_pool;
	for(int i=0;i<=n;i++) root[i]=NULL;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j+=lowbit(j))
			insert(root[j],1,MAX_NUM,a[i],1);
	}
}

int main()
{
	freopen("input","r",stdin);
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		MAX_NUM=max(MAX_NUM,a[i]);
	}
	init();
	while(m--)
		solve();
	return 0;
}