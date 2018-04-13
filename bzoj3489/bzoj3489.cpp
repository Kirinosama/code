#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010

int n,m,pre[MAXN],ne[MAXN],a[MAXN];
int lastans,lastpos[MAXN];
int l1[MAXN*4],l2[MAXN*4],l3[MAXN*4],r1[MAXN*4],r2[MAXN*4],r3[MAXN*4];
int ls[MAXN*4],rs[MAXN*4],Max[MAXN*4],num,root;

struct point{
	int pre,ne,pos,val;
	point(){}
	point(int x,int y,int z,int t){pre=x,ne=y,pos=z,val=t;}
}p[MAXN];


bool cmp1(const point &a,const point &b){
	return a.pre<b.pre;
}

bool cmp2(const point &a,const point &b){
	return a.ne<b.ne;
}

bool cmp3(const point &a,const point &b){	
	return a.pos<b.pos;
}

void maintain(int x){
	Max[x]=max(Max[ls[x]],Max[rs[x]]);
	l1[x]=min(l1[ls[x]],l1[rs[x]]);
	l2[x]=min(l2[ls[x]],l2[rs[x]]);
	l3[x]=min(l3[ls[x]],l3[rs[x]]);
	r1[x]=max(r1[ls[x]],r1[rs[x]]);
	r2[x]=max(r2[ls[x]],r2[rs[x]]);
	r3[x]=max(r3[ls[x]],r3[rs[x]]);
}

void build(int &cur,int l,int r,int opt){
	cur=++num;
	if(l==r){
		Max[cur]=p[l].val;
		l1[cur]=r1[cur]=p[l].pre;
		l2[cur]=r2[cur]=p[l].ne;
		l3[cur]=r3[cur]=p[l].pos;
	}else{
		int mid=(l+r)>>1;
		if(opt==1){
			nth_element(p+l,p+mid,p+r+1,cmp1);
			build(ls[cur],l,mid,2);build(rs[cur],mid+1,r,2);
		}else if(opt==2){
			nth_element(p+l,p+mid,p+r+1,cmp2);
			build(ls[cur],l,mid,3);build(rs[cur],mid+1,r,3);
		}else{
			nth_element(p+l,p+mid,p+r+1,cmp3);
			build(ls[cur],l,mid,1);build(rs[cur],mid+1,r,1);
		}
		maintain(cur);
	}
}

void premake(){
	for(int i=1;i<=n;i++){
		pre[i]=lastpos[a[i]];
		ne[lastpos[a[i]]]=i;
		lastpos[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		if(!ne[i]) ne[i]=n+1;
		p[i]=point(pre[i],ne[i],i,a[i]);
	}
	build(root,1,n,1);
}

bool judge(int cur,int l,int r){
	if(r1[cur]<0 || l1[cur]>l-1) return false;
	if(r2[cur]<r+1 || l2[cur]>n+1) return false;
	if(r3[cur]<l || l3[cur]>r) return false;
	return true;
}

void query(int cur,int l,int r,int L,int R,int opt){
	if(l==r){
		lastans=p[l].val;
	}else{
		int mid=(l+r)>>1;
		if(opt==1){
			if(Max[ls[cur]]>lastans && judge(ls[cur],L,R)) query(ls[cur],l,mid,L,R,2);
			if(Max[rs[cur]]>lastans && judge(rs[cur],L,R)) query(rs[cur],mid+1,r,L,R,2);
		}else if(opt==2){
			if(Max[ls[cur]]>lastans && judge(ls[cur],L,R)) query(ls[cur],l,mid,L,R,3);
			if(Max[rs[cur]]>lastans && judge(rs[cur],L,R)) query(rs[cur],mid+1,r,L,R,3);
		}else{
			if(Max[ls[cur]]>lastans && judge(ls[cur],L,R)) query(ls[cur],l,mid,L,R,1);
			if(Max[rs[cur]]>lastans && judge(rs[cur],L,R)) query(rs[cur],mid+1,r,L,R,1);
		}
	}
}

void solve(int l,int r){
	lastans=0;
	query(root,1,n,l,r,1);
	cout<<lastans<<endl;
}

int main(){
	freopen("bzoj3489.in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	premake();
	while(m--){
		int x,y,l,r;scanf("%d%d",&x,&y);
		l=min((x+lastans)%n+1,(y+lastans)%n+1);
		r=max((x+lastans)%n+1,(y+lastans)%n+1);
		solve(l,r);
	}
	return 0;
}
