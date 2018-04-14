#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 400010

int mul[40],n,a[MAXN],now;
int pre[MAXN],suc[MAXN];

struct node{
	node* ch[2];
	node(){ch[0]=ch[1]=NULL;}
};

struct trie{
	node *root;
	void aDD(node *&p,int x,int k){
		if(k==-1) return;
		int c=x&mul[k]?1:0;
		if(!p->ch[c]) p->ch[c]=new node;
		aDD(p->ch[c],x,k-1);
	}
	void Add(int x){
		aDD(root,x,30);
	}
	int getmax(int x){
		node *p=root;int res=0;
		for(int i=30;i>=0;i--){
			int c=x&mul[i]?1:0;
			if(p->ch[!c]) res+=mul[i],p=p->ch[!c];
			else p=p->ch[c];
		}
		return res;
	}
}t;

int main(){
	freopen("bzoj4260.in","r",stdin);
	cin>>n;mul[0]=1;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=30;i++)mul[i]=mul[i-1]<<1;
	t.root=new node;t.Add(0);now=0;
	for(int i=1;i<=n;i++){
		t.Add(now^=a[i]);
		pre[i]=max(pre[i-1],t.getmax(a[i]));
	}
	t.root=new node;t.Add(0);now=0;
	for(int i=n;i>=1;i--){
		t.Add(now^=a[i]);
		suc[i]=max(suc[i+1],t.getmax(a[i]));
	}
	int ans=0;
	for(int i=1;i<n;i++)ans=max(ans,pre[i]+suc[i+1]);
	cout<<ans;
	return 0;
}
