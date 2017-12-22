#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

long long a[100],num,k,f[100];
char s[100];


long long getnum(long long *a,int u,int v)
{
	long long sum=0;{
	for(int i=u;i<=v;i++)
	{
		sum=sum*10+a[i];
		if(sum>=k)	return 0x7fffffffffffffff;
	}
	return sum;
}

int main()
{
	freopen("input","r",stdin);
	cin>>k;
	scanf("%s",s);
	long long length=strlen(s);
	for(int i=1;i<=length;i++)
		a[i]=s[i-1]-'0';
	memset(f,0x7f,sizeof(f));
	f[0]=0;

	for(int i=1;i<=length;i++)
	{	
		for(int j=i-1;j>=0;j--)
		{
			long long num=getnum(a,j+1,i);
			if(num>=k)
				break;
			if(a[j+1]==0 && j+1!=i)
				continue;
			if(f[j]>(1000000000000000000-num)/k)
				continue;
			f[i]=min(f[i],f[j]*k+num);
		}
	}
	cout<<f[length];
	return 0;
}