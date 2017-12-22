#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 6010
int n,a[MAXN],b[MAXN],c[MAXN],f[MAXN*5],m,ans;

inline int read()
{
    int data=0,w=1; char ch=0;
    while(ch!='-' && (ch<'0' || ch>'9')) ch=getchar();
    if(ch=='-') w=-1,ch=getchar();
    while(ch>='0' && ch<='9') data=data*10+ch-'0',ch=getchar();
    return data*w;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		a[i]=read();b[i]=read();c[i]=read();
		int temp=0x3f3f3f3f;
		if(a[i]) temp=min(temp,a[i]);
		if(b[i]) temp=min(temp,b[i]);
		if(c[i]) temp=min(temp,c[i]);
		m+=temp;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=0;j--)
		{
			int temp=0x3f3f3f3f;
			if(a[i] && j-a[i]>=0) temp=min(temp,f[j-a[i]]);
			if(b[i]) temp=min(temp,f[j]+b[i]);
			if(c[i] && j-c[i]>=0) temp=min(temp,f[j-c[i]]+c[i]);
			f[j]=temp;
		}
	}
	ans=0x7fffffff;
	for(int i=0;i<=m;i++) ans=min(ans,max(i,f[i]));
		cout<<ans;
	return 0;
}