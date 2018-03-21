#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define Size(x) (x?x->size:0)
#define SUM1(x) (x?x->sum1:0)
#define SUM2(x) (x?x->sum2:0)
#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 100010
#define MAXM 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,a[MAXN];
bool flag;

struct task{
	char opt[5];
	int l,r,k;
	void in(){
		scanf("%s",opt);
		if(opt[0]=='1')scanf("%d",&l),flag=true;
		else{
			scanf("%d%d",&l,&r);
			if(opt[1]=='1' && opt[2]=='0')scanf("%d",&k);
		}
	}
}t[MAXM];

struct node{
	node *ch[2],*fa;
	int size,rev;
	ll sum1,sum2,val;
	node(){ch[0]=ch[1]=fa=NULL;rev=size=sum1=sum2=val=0;}
	void maintain(){
		size=Size(ch[0])+Size(ch[1])+1;
		sum1=SUM1(ch[0])+SUM1(ch[1]);
		sum2=SUM2(ch[0])+SUM2(ch[1]);
		if(val>0) sum2+=val;
		else sum1+=val;
	}
	void pushdown(){
		if(rev){
			swap(ch[0],ch[1]);
			if(ch[0]) ch[0]->rev^=1;
			if(ch[1]) ch[1]->rev^=1;
		}
	}
}*root;

void pushup(node *p){
	if(p->fa) pushup(p->fa);
	p->pushdown();
}

void build(node *&p,int l,int r){
	p=new node;
	if(l==r){
		p->val=a[l];p->maintain();
	}else{
		int mid=(l+r)>>1;
		p->val=a[mid];
		if(l<=mid-1){
			build(ls,l,mid-1);
			ls->fa=p;
		}
		if(mid+1<=r){
			build(rs,mid+1,r);
			rs->fa=p;
		}
		p->maintain();
	}
}

int wh(node *p){
	return p->fa->ch[1]==p;
}

node *find(int tot){
	node *cur=root;
	while(1){
		cur->pushdown();
		int lcnt=Size(cur->ch[0]);
		if(lcnt+1==tot) return cur;
		else if(tot<=lcnt) cur=cur->ch[0];
		else{
			cur=cur->ch[1];
			tot-=lcnt+1;
		}
	}
}

void rot(node *p){
	node *f=p->fa,*g=f->fa;
	int c=wh(p);
	f->ch[c]=p->ch[!c];
	if(f->ch[c]) f->ch[c]->fa=f;
	if(f==root){
		p->fa=NULL;
		root=p;
	}else{
		p->fa=g;
		g->ch[wh(f)]=p;
	}
	p->ch[!c]=f;f->fa=p;
	f->maintain();p->maintain();
	if(g) g->maintain(); 
}

void splay(node *p){
	pushup(p);
	for(;p!=root;rot(p)){
		if(p->fa!=root)
			rot(wh(p)==wh(p->fa)?p:p->fa);
	}
}

ll cal(int x){
	node *p=find(x+2);splay(p);
	node *q=find(1);splay(q);
	return SUM1(p->ch[0])+SUM2(p->ch[0]);
}

void solve(int ID){
	int opt=(t[ID].opt[0]-'0')*4+(t[ID].opt[1]-'0')*2+(t[ID].opt[2]-'0')*1;
	int l=t[ID].l,r=t[ID].r,k=t[ID].k;
	if(opt==1){
		ll ans1=0,ans2=0;
		ll res=cal(l);
		if(l==r){
			cout<<res<<endl;
			return;
		}
		if(res>0) ans2+=res;
		else ans1+=res;
		node *p=find(r+2);splay(p);
		node *q=find(l+1);splay(q);
		ans1+=SUM1(p->ch[0]);ans2+=SUM2(p->ch[0]);
		cout<<max(-ans1,ans2)<<endl;
	}else if(opt==2){
		node *p=find(l+1);splay(p);
		p->val+=k;p->maintain();
		if(r<n){
			p=find(r+2);splay(p);
			p->val-=k;p->maintain();
		}
	}else if(opt==3){
		node *p=find(r+2);splay(p);
		node *q=find(l);splay(q);
		p->ch[0]->rev^=1;
	}else{
		for(int i=ID;i>=ID-l;i--){
			if(t[i].opt[1]=='1' && t[i].opt[2]=='0'){
				t[0]=t[i];t[0].k=-t[i].k;
				solve(0);
			}else if(t[i].opt[1]=='1' && t[i].opt[2]=='1'){
				solve(i);
			}
		}
	}
}

void solve1(){
	build(root,0,n+1);
	for(int i=1;i<=m;i++)
		solve(i);
}

int main(){
    freopen("T22725.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=n;i>=1;i--)a[i]=a[i]-a[i-1];
    for(int i=1;i<=m;i++)t[i].in();
    solve1();
    return 0;
}