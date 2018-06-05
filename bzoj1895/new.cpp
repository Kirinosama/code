#include <bits/stdc++.h>
using namespace std;

#define MAXN 200010
#define ls ch[x][0]
#define rs ch[x][1]

int addtag[MAXN],fa[MAXN];
int rev[MAXN],Min[MAXN],size[MAXN],data[MAXN],ch[MAXN][2];
int rt,a[MAXN],n,m,nodecnt;
	
void pushdown(int x){
	if(rev[x]){
		swap(ls,rs);
		if(ls) rev[ls]^=1;
		if(rs) rev[rs]^=1;
		rev[x]=0;
	}
	if(addtag[x]){
		if(ls){
			addtag[ls]+=addtag[x];
			data[ls]+=addtag[x];
			Min[ls]+=addtag[x];
		}
		if(rs){
			addtag[rs]+=addtag[x];
			data[ls]+=addtag[x];
			Min[rs]+=addtag[x];
		}
		addtag[x]=0;
	}
}

void maintain(int x){
	Min[x]=data[x];
	if(ls) Min[x]=min(Min[x],Min[ls]);
	if(rs) Min[x]=min(Min[x],Min[rs]);
	size[x]=1;
	if(ls) size[x]+=size[ls];
	if(rs) size[x]+=size[rs];
}

int build(int l,int r){
	int now=++nodecnt;size[now]=1;
	if(l==r) Min[now]=data[now]=a[l];
	else{
		int mid=(l+r)>>1;data[now]=a[mid];
		if(l<mid) ch[now][0]=build(l,mid-1),fa[ch[now][0]]=now;
		if(r>mid) ch[now][1]=build(mid+1,r),fa[ch[now][1]]=now;
		maintain(now);
	}
	return now;
}

int find(int x){
	int now=rt;
	while(now){
		pushdown(now);maintain(now);
		int lcnt=size[ch[now][0]];
		if(x==lcnt+1) return now;
		else if(x<=lcnt) now=ch[now][0];
		else x-=lcnt+1,now=ch[now][1];
	}
	return -1;
}

void pushup(int x){
	if(fa[x]) pushup(fa[x]);
	pushdown(x);
}

int wh(int x){
	return ch[fa[x]][1]==x;
}

void rot(int x){
	int f=fa[x],g=fa[f],c=wh(x);
	ch[f][c]=ch[x][!c];
	if(ch[f][c]) fa[ch[f][c]]=f;
	if(g) ch[g][wh(f)]=x;
	fa[x]=g;
	fa[f]=x;ch[x][!c]=f;
	maintain(f);maintain(x);
	if(f==rt) rt=x;
}

void splay(int x,int f){
	pushup(x);
	for(;fa[x]!=f;rot(x))
		if(fa[fa[x]]!=f)
			rot(wh(fa[x])==wh(x)?fa[x]:x);
}

int gettype(){
	char s[10];
	scanf("%s",s);
	if(s[0]=='A') return 0;
	else if(s[0]=='R' && s[3]=='E') return 1;
	else if(s[0]=='R' && s[3]=='O') return 2;
	else if(s[0]=='I') return 3;
	else if(s[0]=='D') return 4;
	else return 5;
}

void add(int x,int y,int z){
	int p=find(x),q=find(y+2);
	splay(p,0);splay(q,p);
	addtag[ch[q][0]]+=z;
	data[ch[q][0]]+=z;Min[ch[q][0]]+=z;
	maintain(q);maintain(p);
}

void reverse(int x,int y){
	int p=find(x),q=find(y+2);
	splay(p,0);splay(q,p);
	rev[ch[q][0]]^=1;
}

void insert(int x,int y){
	int p=find(x+1),q=find(x+2);
	splay(p,0);splay(q,p);
	ch[q][0]=++nodecnt;
	data[nodecnt]=Min[nodecnt]=y;
	size[nodecnt]=1;fa[nodecnt]=q;
	maintain(q);maintain(p);
}

void del(int x){
	int p=find(x),q=find(x+2);
	splay(p,0);splay(q,p);
	ch[q][0]=0;
	maintain(q);maintain(p);
}

void getmin(int x,int y){
	int p=find(x),q=find(y+2);
	splay(p,0);splay(q,p);
	pushdown(ch[q][0]);maintain(ch[q][0]);
	printf("%d\n",Min[ch[q][0]]);
}

int main(){
	freopen("input","r",stdin);
	//freopen("out2","w",stdout);
	cin>>n;a[0]=a[n+1]=0x7fffffff;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	rt=build(0,n+1);cin>>m;
	for(int i=1;i<=m;i++){
		int opt=gettype(),x,y,z;
		switch(opt){
			case 0:scanf("%d%d%d",&x,&y,&z);add(x,y,z);break;
			case 1:scanf("%d%d",&x,&y);reverse(x,y);break;
			case 2:scanf("%d%d%d",&x,&y,&z);z%=(y-x+1);if(!z)break;
				   reverse(x,x+z-1);reverse(x+z,y);reverse(x,y);break;
			case 3:scanf("%d%d",&x,&y);insert(x,y);break;
			case 4:scanf("%d",&x);del(x);break;
			case 5:scanf("%d%d",&x,&y);getmin(x,y);
		}
	}
	return 0;
}

