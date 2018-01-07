#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	int sum,dif;
	node *ch[2];
	void maintain(){
		dif=0;
		if(ch[0]) dif+=ch[0]->dif;
		if(ch[1]) dif+=ch[1]->dif;
	}
}*root[MAXN];

int n,m,t,col[MAXN],dfn[MAXN],tail[MAXN],cnt,id[MAXN];
vector <int> to[MAXN];

void dfs(int x,int f){
	dfn[x]=++cnt;id[cnt]=x;
	for(int i=0;i<to[x].size();i++)
		if(to[x][i]!=f)
			dfs(to[x][i],x);
	tail[x]=cnt;
}

int lowbit(int x){
	return x&-x;
}

void update(node *&p,int l,int r,int pos,int k){
	node *ls=p?p->ch[0]:NULL,*rs=p?p->ch[1]:NULL;
	int cursum=p->sum,curdif=p->dif;
	p=new node;p->sum=cursum+k;
	if(pos==l && pos==r){
		if(p->sum==1 && k==1) p->dif=1;
		if(p->sum==0 && k==-1) p->dif=0;
		p->ch[0]=p->ch[1]=NULL;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid){
		p->ch[1]=rs;
		update(p->ch[0],l,mid,pos,k);
	}
	else{
		p->ch[0]=ls;
		update(p->ch[1],mid+1,r,pos,k);
	}
	p->maintain();
}

void query(int l,int r,int L,int R){
	asd
}

void solve(){
}

void premake(){
	dfs(1,1);
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=lowbit(j))
			update(root[j],1,n,col[id[i]],1);
	}
}

int main(){
    freopen("xmastree1.in","r",stdin);
    scanf("%d %d %d",&n,&m,&t);
   	for(int i=1;i<=n;i++) scanf("%d",&col[i]);
   	for(int i=1;i<n;i++){
   		static int x,y;
   		scanf("%d %d",&x,&y);
   		to[x].push_back(y);
   		to[y].push_back(x);
   	}
   	premake();
   	while(m--)
   		solve();
    return 0;
}