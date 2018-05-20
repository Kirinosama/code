#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int read()
{
	char ch=getchar();int x=0,f=1;
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
char s[25];
int x[25],y[25];
int now[55],t[55],top;
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int T=read();
	while(T--)
	{
		ll n=0;
		scanf("%s",s+1);
		int m=strlen(s+1);
		for(int i=1;i<=m;i++)
		n=n*10+s[i]-'0';
		ll ans=n;
		for(int i=1;i<m;i++)
		{
			if(s[i+1]=='0') continue;
			for(int j=i+1;j<=m;j++) y[j-i]=s[j]-'0';
			ll temp=0;
			for(int j=1;j<=i;j++) temp=temp*10+s[j]-'0';
			temp++;
			for(int j=i;j;j--) x[j]=temp%10,temp/=10;
			int len=min(i,m-i);
			for(int j=len;j>=0;j--)
			{
				bool ac=1;
				for(int k=1;k<=j;k++)
				{
					if(x[k]!=y[m-i-j+k])
					{
						ac=0;break;
					}
				}
				if(ac)
				{
					temp=0;
					for(int k=1;k<=m-i;k++) temp=temp*10+y[k];
					for(int k=j+1;k<=i;k++) temp=temp*10+x[k];
					ans=min(ans,temp);
					break;
				}
			}
		}
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=i;j++)
			{
				if(s[j]=='0') continue;
				if(j+i-1>m) break;
				ll temp=0;
				for(int k=j;k<=j+i-1;k++)
				{
					now[k]=s[k]-'0';
					temp=temp*10+now[k];
				}
				ll temp1=temp-1;
				
				for(int k=j-1;k;k--)
				{
					now[k]=temp1%10;
					temp1/=10;
				}
				int r=j+i;temp1=temp;
				while(r<=m)
				{
					temp++;
					temp1=temp;
					top=0;
					while(temp1)
					{
						t[++top]=temp1%10;
						temp1/=10;
					}
					while(top&&r<=m)
					{
						now[r++]=t[top];
						top--;
					}
				}
				bool ac=1;
				for(int k=1;k<=m;k++)
				{
					if(now[k]!=s[k]-'0')
					{
						ac=0;
						break;
					}
				}
				if(ac) ans=min(ans,temp);
			}
		}
		printf("%lld\n",ans);
	}
}

