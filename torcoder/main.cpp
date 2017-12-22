#include <cstdlib>
#include <cstdio>

#define MAXN 100010

struct node
{
	int sum;
	bool lazy;
}t[30][MAXN*8];

int n,m;
int v[MAXN],num[27];
char s[MAXN];

void build(int id,int x,int l,int r)
{
	t[id][x].sum=0;
	t[id][x].lazy=false;
	if(l!=r)
	{
		int mid=(l+r)/2;
		build(id,x*2,l,mid);
		build(id,x*2+1,mid+1,r);
	}
}

void made(int id,int x,int l,int r,int ll,int rr,int k)
{
	if(l>rr || r<ll)
		return;
	if(l>=ll && r<=rr)
	{
		t[id][x].sum=k*(r-l+1);
		t[id][x].lazy=true;
		return;
	}
	else
	{
		int mid=(l+r)/2;
		if(t[id][x].lazy==true)
		{
			t[id][x].lazy=false;
			t[id][x*2].lazy=true;
			t[id][x*2+1].lazy=true;
			if(t[id][x].sum==0)
				t[id][x*2].sum=t[id][x*2+1].sum=0;
			else
			{
				t[id][x*2].sum=mid-l+1;
				t[id][x*2+1].sum=r-mid;
			}
		}
		made(id,x*2,l,mid,ll,rr,k);
		made(id,x*2+1,mid+1,r,ll,rr,k);
		t[id][x].sum=t[id][x*2].sum+t[id][x*2+1].sum;
	}
}

int ask(int id,int x,int l,int r,int ll,int rr)
{
	if(l>rr || r<ll)
		return 0;
	if(l>=ll && r<=rr)
		return t[id][x].sum;
	else
	{
		int mid=(l+r)/2;
		return ask(id,x*2,l,mid,ll,rr)+ask(id,x*2+1,mid+1,r,ll,rr);
	}
}

void premake()
{
	for(int i=1;i<=26;i++)
		build(i,1,1,n);
	for(int i=1;i<=n;i++)
		made(s[i]-'a'+1,1,1,n,i,i,1);
}

void solve()
{
	int ll,rr;
	scanf("%d %d",&ll,&rr);
	for(int i=1;i<=26;i++)
		num[i]=ask(i,1,1,n,ll,rr);
	int pos=1;int res=0;
	for(int i=1;i<=26;i++)
		if(num[i]%2==1)
			res++;
	if(res>1)
		return;
	if(res==1 && (rr-ll+1)%2==0)
		return;
	if(res==0 && (rr-ll+1)%2==1)
		return;
	for(int i=1;i<=26;i++)
		if(num[i]%2==1)
		{
			v[(rr+ll)/2]=i;
			num[i]--;
		}
	for(int i=ll;i<(rr+ll)/2;i++)
	{
		for(int j=1;j<=26;j++)
			while(num[j]>=2)
			{
				num[j]-=2;
				v[i]=v[rr+ll-i]=j;
				i++;
			}
	}
	for(int i=1;i<=26;i++)
		made(i,1,1,n,ll,rr,0);
	for(int i=ll;i<=rr;i++)
		made(v[i],1,1,n,i,i,1);
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	scanf("%s",s);
	for(int i=n;i>=1;i--)
		s[i]=s[i-1];
	premake();
	for(int i=1;i<=m;i++)
		solve();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=26;j++)
			if(ask(j,1,1,n,i,i)==1)
				printf("%c",j-1+'a');
	return 0;
}	