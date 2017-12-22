#include<cstdio>
#include<algorithm>
#define inf 0x7fffffff
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,ans=-inf,sum[50005];
struct data{int x,y;}a[50005];
inline bool cmp(data a,data b)
{return a.x-b.y<b.x-a.y;}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	    a[i].x=read(),a[i].y=read();
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(sum[i-1]-a[i].y>ans)ans=sum[i-1]-a[i].y;
		sum[i]=sum[i-1]+a[i].x;
	}
	printf("%d",ans);
	return 0;
}
