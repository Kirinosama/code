#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int read()
{
	char ch=getchar();int x=0,f=1;
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int getlen(int x)
{
	int l=1,r=100000,ans;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(1LL*mid*(mid-1)/2>=x)
		{
			ans=mid;r=mid-1;
		}
		else l=mid+1;
	}
	return ans;
}
void solve(int n,int x)
{
	//cout<<n<<" "<<x<<endl;
	int len=0;char now='0';
	for(int i=getlen(x);i;i--)
	{
		int temp=i*(i-1)/2;
		while(x>=temp&&len+i<=n)
		{
			//cout<<n<<" "<<len<<endl;
			for(int j=1;j<=i;j++) putchar(now);
			x-=temp;if(now=='0') now='1';else now='0';
			len+=i;
		}
		
		
	}
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int T=read();
	while(T--)
	{
		int x=read();
		int len=getlen(x);
		solve(len,len*(len-1)/2-x);
		puts("");
		//cerr<<"ok";
	}
}
/*
4
1
4
7
11
*/
