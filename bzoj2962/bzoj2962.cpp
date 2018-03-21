#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 19940417
#define ls p->ch[0]
#define rs p->ch[1]
#define MAXN 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m;
ll a[MAXN],ch[MAXN][21];

struct node{
	node *ch[2];
	ll add,f[21];
	int rev,size;
}*root;

const ll read(){
	ll x=0;int w=0;char ch;
	while(ch<'0' || ch>'9')
		w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

const void reverse_node(node *p){
	p->rev^=1;p->add=MOD-p->add;
	for(int i=1;i<=20;i++)if(i&1)
		p->f[i]=MOD-p->f[i];
}

const void add_node(node *p,ll k){
	p->add=(p->add+k)%MOD;
	for(int i=min(p->size,20);i>=1;i--){
		ll sum=0,mul=1;
		for(int j=0;j<=i;j++,mul=(mul*k)%MOD){
			sum+=(((mul*p->f[i-j])%MOD)*ch[p->size-i+j][j])%MOD;
			sum%=MOD;
		}
		p->f[i]=sum;
	}
}

const void pushdown(node *p){
	if(p->rev){
		if(ls) reverse_node(ls);
		if(rs) reverse_node(rs);
		p->rev=0;
	}
	if(p->add){
		if(ls) add_node(ls,p->add);
		if(rs) add_node(rs,p->add);
		p->add=0;
	}
}

const void maintain(node *p){
	memset(p->f,0,sizeof(p->f));
	for(int i=0;i<=min(ls->size,20);i++)
		for(int j=0;j<=min(20-i,rs->size);j++)
			p->f[i+j]+=(ls->f[i]*rs->f[j])%MOD;
	for(int i=0;i<min(20,p->size);i++) p->f[i]%=MOD;
}

const void build(node *&p,int l,int r){
	p=new node;ls=rs=NULL;
	memset(p->f,0,sizeof(p->f));p->f[0]=1;
	p->add=p->rev=0;p->size=r-l+1;
	if(l==r){
		p->f[1]=(a[l]%MOD+MOD)%MOD;
	}else{
		int mid=(l+r)>>1;
		build(ls,l,mid);build(rs,mid+1,r);
		maintain(p);
	}
}

const void increase(node *p,int l,int r,int L,int R,ll z){
	if(l>R || r<L) return;
	if(l>=L && r<=R){
		add_node(p,z);
	}else{
		int mid=(l+r)>>1;
		pushdown(p);
		increase(ls,l,mid,L,R,z);
		increase(rs,mid+1,r,L,R,z);
		maintain(p);
	}
}

const void reverse(node *p,int l,int r,int L,int R){
	if(l>R || r<L)return;
	if(l>=L && r<=R){
		reverse_node(p);
	}else{
		int mid=(l+r)>>1;
		pushdown(p);
		reverse(ls,l,mid,L,R);
		reverse(rs,mid+1,r,L,R);
		maintain(p);
	}
}

const ll query(node *p,int l,int r,int L,int R,int z){
	if(l>R || r<L){
		if(z) return 0;
		else return 1;
	}
	if(l>=L && r<=R){
		return p->f[z];
	}else{
		int mid=(l+r)>>1;ll sum=0;
		pushdown(p);
		for(int i=0;i<=min(ls->size,z);i++){
			sum+=(query(ls,l,mid,L,R,i)*query(rs,mid+1,r,L,R,z-i))%MOD;
			sum%=MOD;
		}
		maintain(p);return sum;
	}
}

const void solve(){
	char ch[5];int x,y;ll z; 
	scanf("%s",ch);
	switch(ch[0]){
		case 'I':
			x=read(),y=read(),z=read();
			increase(root,1,n,x,y,(z%MOD+MOD)%MOD);
			break;
		case 'R':
			x=read(),y=read();
			reverse(root,1,n,x,y);
			break;
		case 'Q':
			x=read(),y=read(),z=read();
			printf("%lld\n",query(root,1,n,x,y,z));
	}
}

void getc(){
	ch[0][0]=1;
	for(int i=1;i<50000;i++){
		ch[i][0]=1;
		for(int j=1;j<=20;j++)
			ch[i][j]=(ch[i-1][j-1]+ch[i-1][j])%MOD;
	}
}

int main(){
    freopen("bzoj2962.in","r",stdin);
    n=read(),m=read();
    for(int i=1;i<=n;i++)a[i]=read();
    build(root,1,n);getc();
	while(m--)solve();
    return 0;
}