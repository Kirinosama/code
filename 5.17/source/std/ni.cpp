#include <bits/stdc++.h>
#define Ls(n)  (n<<1)
#define Rs(n)  (Ls(n)|1)
using namespace std;

int n,e[500010],t[4000010],tag[4000010],siz[4000010],ans;
multiset <int> S;

int modify(int n,int l,int r,int L,int R)
{
	if ((L<=l)&&(r<=R))  {tag[n]--,t[n]--;  return siz[n];}
	else
	{
		int mid=(l+r)>>1,s=0;
		if (L<=mid)  s+=modify(Ls(n),l,mid,L,R);
		if (mid<R)  s+=modify(Rs(n),mid+1,r,L,R);
		t[n]=min(t[Ls(n)],t[Rs(n)])+tag[n];
		return s;
	}
}

void insert(int n,int l,int r,int x,int k)
{
	if (l==r)  t[n]=x-k,siz[n]++;
	else
	{
		int mid=(l+r)>>1;
		k+=tag[n],x<=mid?insert(Ls(n),l,mid,x,k):insert(Rs(n),mid+1,r,x,k);
		t[n]=min(t[Ls(n)],t[Rs(n)])+tag[n],siz[n]=siz[Ls(n)]+siz[Rs(n)];
	}
}

void work()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++)  scanf("%d",&e[i]),e[i]=min(n,max(-n,e[i]));
	memset(t,127,sizeof(t));
	for (int i=1,x,s; i<=n; i++)
	{
		if (e[i]<0)
		{
			S.insert(e[i]);
			if ((*S.rbegin())+int(S.size())>0)
				x=*S.rbegin(),S.erase(S.find(x));
			else  x=n+1;
		}
		else  x=e[i];
		
		if (x<=n)
		{
			if (x!=n)  s=modify(1,-n,n,x+1,n);  else  s=0;
			insert(1,-n,n,x,i-s);
		}
		else  modify(1,-n,n,-n,n);
		printf("%d\n",min(t[1],-2*int(S.size()))+i);
	}
}

int main()
{
	freopen("ni.in","r",stdin);
	freopen("ni.out","w",stdout);
	work();
	return 0;
}
