#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 300010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct node{
	node *ch[2];
	int val,add;
	void maintain(){
		val=-INF;
		if(ch[0]) val=max(val,ch[0]->val);
		if(ch[1]) val=max(val,ch[1]->val);
	}
	void push_down(){
		if(add){
			if(ch[0]) ch[0]->add+=add,ch[0]->val+=add;
			if(ch[1]) ch[1]->add+=add,ch[1]->val+=add;
			add=0;
		}
	}
}*root;

struct query{
	char type[10];
	int x,y;
	void in(){
		scanf("%s",type);
		if(type[0]=='U') scanf("%d %d",&x,&y);
		if(type[0]=='A' && type[1]=='1') scanf("%d %d",&x,&y);
		if(type[0]=='A' && type[1]=='2') scanf("%d %d",&x,&y);
		if(type[0]=='A' && type[1]=='3') scanf("%d",&x);
		if(type[0]=='F' && type[1]=='1') scanf("%d %d",&x,&y);
		if(type[0]=='F' && type[1]=='2') scanf("%d %d",&x,&y);
		if(type[0]=='F' && type[1]=='3') scanf("%d",&x);
	}
}task[MAXN];

int n,m,a[MAXN],father[MAXN],tail[MAXN],id[MAXN],cnt;
int w[MAXN];
vector <int> to[MAXN];
 
void build(node *&p,int l,int r){
	p=new node;p->add=0;
	p->ch[0]=p->ch[1]=NULL;
	if(l==r) p->val=w[l];
	else{
		int mid=(l+r)>>1;
		build(p->ch[0],l,mid);
		build(p->ch[1],mid+1,r);
		p->maintain();
	}
}

void update(node *&p,int l,int r,int L,int R,int k){
	if(!p) return;
	if(l>=L && r<=R){
		p->add+=k;
		p->val+=k;
		return;
	}
	else if(l>R || r<L) return;
	else if(l!=r){
		int mid=(l+r)>>1;
		p->push_down();
		update(p->ch[0],l,mid,L,R,k);
		update(p->ch[1],mid+1,r,L,R,k);
		p->maintain();
	}
}

int Query(node *p,int l,int r,int L,int R){
	if(!p) return -INF;
	if(l>=L && r<=R)
		return p->val;
	else if(l>R || r<L)
		return -INF;
	else if(l!=r){
		int mid=(l+r)>>1;
		p->push_down();
		int res=max(Query(p->ch[0],l,mid,L,R),Query(p->ch[1],mid+1,r,L,R));
		p->maintain();
		return res;
	}
	return -INF;
}

int find(int x){
	return father[x]==x?x:father[x]=find(father[x]);
}

void dfs(int x){
	id[x]=++cnt;
	for(int i=0;i<to[x].size();i++)
		dfs(to[x][i]);
}

void solve(query &cur){
	if(cur.type[0]=='U'){
		int fx=find(cur.x),fy=find(cur.y);
   		if(fx==fy) return;
   		father[fy]=tail[fx];
   		tail[fx]=tail[fy];
	}
	if(cur.type[0]=='A' && cur.type[1]=='1')
		update(root,1,n,id[cur.x],id[cur.x],cur.y);
	if(cur.type[0]=='A' && cur.type[1]=='2'){
		int fx=find(cur.x);
		update(root,1,n,id[fx],id[tail[fx]],cur.y);
	}
	if(cur.type[0]=='A' && cur.type[1]=='3')
		update(root,1,n,1,n,cur.x);
	if(cur.type[0]=='F' && cur.type[1]=='1')
		printf("%d\n",Query(root,1,n,id[cur.x],id[cur.x]));
	if(cur.type[0]=='F' && cur.type[1]=='2'){
		int fx=find(cur.x);
		printf("%d\n",Query(root,1,n,id[fx],id[tail[fx]]));
	}
	if(cur.type[0]=='F' && cur.type[1]=='3')
		printf("%d\n",Query(root,1,n,1,n));
}

int main(){
    freopen("2333.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	father[i]=i;tail[i]=i;
    }
    scanf("%d",&m);
   	for(int i=1;i<=m;i++){
   		task[i].in();
   		if(task[i].type[0]=='U'){
   			int x=task[i].x,y=task[i].y;
   			int fx=find(x),fy=find(y);
   			if(fx==fy) continue;
   			to[tail[fx]].push_back(fy);
   			father[fy]=tail[fx];
   			tail[fx]=tail[fy];
   		}
   	}
   	for(int i=1;i<=n;i++)
   		if(father[i]==i)
   			dfs(i);
   	for(int i=1;i<=n;i++){
   		father[i]=i,tail[i]=i;
   		w[id[i]]=a[i];
   	}
   	build(root,1,n);
   	for(int i=1;i<=m;i++)
   		solve(task[i]);
    return 0;
}