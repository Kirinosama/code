#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define MAXN 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int dep[MAXN],father[MAXN],size[MAXN],son[MAXN];
int dfn[MAXN],top[MAXN],tail[MAXN],id[MAXN],cnt;
int n,m,a[MAXN],num,lastans,s,t,k;
vector <int> to[MAXN],v;
map <int,int> mp,mp1;

struct node{
	int sum;
	node *ch[2];
}*root[MAXN];

void dfs1(int x,int f){
	father[x]=f,dep[x]=dep[f]+1;
	size[x]=1;son[x]=0;
	for(int i=0;i<to[x].size();i++){
		int y=to[x][i];
		if(y==f) continue;
		dfs1(y,x);
		size[x]+=size[y];
		if(size[y]>size[son[x]]) son[x]=y;
	}
}

void dfs2(int x,int tp){
	dfn[x]=++cnt;id[cnt]=x;top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=0;i<to[x].size();i++){
		int y=to[x][i];
		if(y==father[x] || y==son[x]) continue;
		dfs2(y,y);
	}
	tail[x]=cnt;
} 

void build(node *&p,int l,int r){
	p=new node;
	p->ch[0]=p->ch[1]=NULL;
	p->sum=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(p->ch[0],l,mid);
	build(p->ch[1],mid+1,r);
}

void make(node *&p,node *q,int l,int r,int pos){
	p=new node;
	p->sum=q->sum+1;
	p->ch[0]=p->ch[1]=NULL;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid){
		p->ch[1]=q->ch[1];
		make(p->ch[0],q->ch[0],l,mid,pos);
	}
	else{
		p->ch[0]=q->ch[0];
		make(p->ch[1],q->ch[1],mid+1,r,pos);
	}
}

void premake(){
	build(root[0],1,num);
	for(int i=1;i<=n;i++)
		make(root[i],root[i-1],1,num,mp[a[id[i]]]);
}

int Query(node *p,node *q,int l,int r,int L,int R){
	if(l>=L && r<=R) return p->sum-q->sum;
	else if(l>R || r<L) return 0;
	else if(l!=r){
		int mid=(l+r)>>1;
		return Query(p->ch[0],q->ch[0],l,mid,L,R)+Query(p->ch[1],q->ch[1],mid+1,r,L,R);
	}
	return 0;
}

int query(int l,int r,int L,int R){
	return Query(root[r],root[l-1],1,num,L,R);
}

int count(int cur){
	int sum=0;
	while(s!=t){
		if(dep[s]<dep[t]) swap(s,t);
		if(top[s]==top[t]) sum+=query(dfn[t],dfn[s],1,cur),s=t;
		else{
			sum+=query(dfn[top[s]],dfn[s],1,cur);
			s=father[top[s]];
		}
	}
	return sum;
}

void solve(){
	int res;int S,T;
	scanf("%d %d %d",&S,&T,&k);
	S^=lastans;
	int L=1,R=num;
	while(L<=R){
		s=S,t=T;
		int mid=(L+R)>>1;
		if(count(mid)>=k) res=mp1[mid],R=mid-1;
		else L=mid+1;
	}
	lastans=res;
	printf("%d\n",res);
}

int main(){
    freopen("bzoj2588.in","r",stdin);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++)
    	if(!mp[v[i]]){
    		mp[v[i]]=++num;
    		mp1[num]=v[i];
    	}
    for(int i=1;i<n;i++){
    	static int x,y;
    	scanf("%d %d",&x,&y);
    	to[x].push_back(y),to[y].push_back(x);
    }
    dfs1(1,1);
    dfs2(1,1);
    premake();
    for(int i=1;i<=m;i++)
 	   solve();
    return 0;
}