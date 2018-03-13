#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 500010
#define MAXM 10010
#define MAXQ 510
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct query{
	int l,r,p,ans;
	void in(){scanf("%d%d%d",&l,&r,&p);ans=INF;}
}Q[MAXM];

struct node{
	node *ch[2];
	int Max;
	node(){ch[0]=ch[1]=NULL,Max=-INF;}
}*root;

vector <int> ID[MAXQ];
int n,m,a[MAXN];

void build(node *&p,int l,int r){
	p=new node;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}

void add(node *&p,int l,int r,int pos){
	p->Max=max(p->Max,pos);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) add(ls,l,mid,pos);
	else add(rs,mid+1,r,pos);
}

int get_max(node *p,int l,int r,int L,int R){
	if(l>R || r<L) return 0;
	if(l>=L && r<=R) return p->Max;
	else{
		int mid=(l+r)>>1;
		return max(get_max(ls,l,mid,L,R),get_max(rs,mid+1,r,L,R));
	}
}

void make(query &cur){
	int sum=0;
	if(cur.r-cur.l+1>=cur.p+1){
		cur.ans=0;return;
	}
	build(root,0,cur.p-1);add(root,0,cur.p-1,0);
	for(int i=cur.l;i<=cur.r;i++){
		sum=(sum+a[i])%cur.p;
		cur.ans=min(cur.ans,(sum-get_max(root,0,cur.p-1,0,sum)+cur.p)%cur.p);
		if(sum<cur.p-1) cur.ans=min(cur.ans,(sum-get_max(root,0,cur.p-1,sum+1,cur.p-1)+cur.p)%cur.p);
		add(root,0,cur.p-1,sum);
	}
}

int main(){
    //freopen("3.7seq.in","r",stdin);
    //freopen("3.7seq.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=m;i++){
    	Q[i].in();
    	ID[Q[i].p].push_back(i);
    }
    for(int i=1;i<=500;i++){
    	for(int j=0;j<ID[i].size();j++)
    		make(Q[ID[i][j]]);
    }
    for(int i=1;i<=m;i++) printf("%d\n",Q[i].ans);
    return 0;
}