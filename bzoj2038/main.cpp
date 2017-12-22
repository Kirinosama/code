#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define SQR 210
#define MAXN 50010
typedef long long LL;

struct node
{
	int l,r;
	int pos;
	void in(){
		scanf("%d %d",&l,&r);
	}
	bool operator < (node a)
	const{
		if(l/SQR==a.l/SQR) return r/SQR<a.r/SQR;
		else return l/SQR<a.l/SQR;
	}
}q[MAXN];

int col[MAXN];
int ll,rr,n,m;
LL cnt[MAXN],sum;
LL ans1[MAXN],ans2[MAXN];

LL ch(LL x) {return x*(x-1)/2;}

LL gcd(LL x,LL y)
{
	if(!x) return y;
	if(!y) return x;
	if(x>y) swap(x,y);
	return gcd(y%x,x);
}

void make(LL u,LL d,int t)
{
	LL k=gcd(u,d);
	u/=k;d/=k;
	ans1[t]=u;
	ans2[t]=d;
}

int main()
{
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",&col[i]);
	for(int i=1;i<=m;i++)
	{
		q[i].in();
		q[i].pos=i;
	}
	sort(q+1,q+1+m);
	ll=1;rr=1;cnt[col[1]]=1;sum=0;
	for(int i=1;i<=m;i++)
	{
		int l=q[i].l;
		int r=q[i].r;
		while(l<ll)
		{
			ll--;
			LL num=++cnt[col[ll]];
			sum+=ch(num)-ch(num-1);
		}
		while(r>rr)
		{
			rr++;
			LL num=++cnt[col[rr]];
			sum+=ch(num)-ch(num-1);
		}
		while(l>ll)
		{
			LL num=--cnt[col[ll]];
			sum+=ch(num)-ch(num+1);
			ll++;
		}
		while(r<rr)
		{
			LL num=--cnt[col[rr]];
			sum+=ch(num)-ch(num+1);
			rr--;
		}
		make(sum,ch((LL)r-l+1),q[i].pos);
	}
	for(int i=1;i<=m;i++)
		printf("%lld/%lld\n",ans1[i],ans2[i]);
	return 0;
}