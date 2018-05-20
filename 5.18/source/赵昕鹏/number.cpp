#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll t[]={0,9ll,99ll,999ll,9999ll,99999ll,999999ll,9999999ll,99999999ll,999999999ll,9999999999ll,99999999999ll,999999999999ll,9999999999999ll,99999999999999ll,999999999999999ll,9999999999999999ll,99999999999999999ll};
char s[19],s0[19],s1[19];
bool equaly(int l,int r,ll x,bool c=1)
{
	int M=0;
	memset(s0,0,sizeof(s0));
	if(!x) return 0;
	while(x) s0[++M]=(x%10)^'0',x/=10;
	if(c) for(int i=1;i<=M/2;i++) swap(s0[i],s0[M-i+1]);
	for(int i=0;i<M&&i+l<=r;i++)
		if(s[i+l]!=s0[i+1]) return 0;
	return 1;
}
void work()
{
	scanf("%s",s+1);
	int N=strlen(s+1);
	ll Ans=0;
	for(int i=1;i<=N;i++)
		Ans=Ans*10+(s[i]^'0');
	for(int l=1;l<=N;l++)
	{
		bool g=0;
		for(int m=1;m+l-1<=N&&m<=l;m++)
		{
			int len=l;
			ll last=0;
			if(s[m]=='0') continue;
			bool f=1;
			for(int i=0;i<len;i++)
				last=last*10+(s[i+m]^'0');
			if(m!=1&&!equaly(1,m-1,last-1,0)) continue;
			for(int i=m+len;i<=N;i+=len)
			{
				if(last==t[len]) ++len;
				ll res=0;
				if(s[i]=='0')
				{
					f=0;
					break;
				}
				if(i+len-1>N)
				{
					if(equaly(i,N,last+1))
						Ans=min(Ans,last+1),g=1;
					f=0;
				}
				else
				{
					for(int j=0;j<len;j++)
						res=res*10+(s[i+j]^'0');
					if(i!=1&&res!=last+1)
					{
						f=0;
						break;
					}
					last=res;
				}
			}
			if(f) Ans=min(Ans,last),g=1;
		}
		if(l>N/2)
		{
			for(int m=N-l+2;m<=l;m++)
			{
				ll x1=0,x2=0;
				int l1=0,l2=0;
				memset(s0,0,sizeof(s0));
				memset(s1,0,sizeof(s1));
				if(s[m]=='0') continue;
				for(int i=m;i<=N;i++)
					x1=x1*10+(s[i]^'0');
				for(int i=1;i<m;i++)
					x2=x2*10+(s[i]^'0');
				++x2;
				bool f=1;
				while(x1) s0[++l1]=(x1%10)^'0',x1/=10;
				while(x2) s1[++l2]=(x2%10)^'0',x2/=10;
				if(l2==m) s1[l2]='\0',--l2;
				for(int i=1;i<=l1/2;i++) swap(s0[i],s0[l1-i+1]);
				for(int i=1;i<=l/2;i++) swap(s1[i],s1[l-i+1]);
				for(int i=l-l2+1;i<=l1;i++)
					if(s0[i]!=s1[i])
					{
						f=0;
						break;
					}
				if(!f) continue;
				for(int i=1;i<=l1;i++)
					x1=x1*10+(s0[i]^'0');
				for(int i=l1+1;i<=l;i++)
					x1=x1*10+(s1[i]^'0');
				Ans=min(Ans,x1),g=1;
			}
		}
		if(g)
		{
			printf("%lld\n",Ans);
			return;
		}
	}
	printf("%s\n",s+1);
	return ;
}
int main()
{
	int T;
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	scanf("%d",&T);
	while(T--) work();
}
