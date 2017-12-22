#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 100010

int k;
char a[MAXN];
int sum,ans,cnt[10];

int main()
{
//	freopen("input","r",stdin);
	scanf("%d\n",&k);
	scanf("%s",a);
	int l=strlen(a);
	for(int i=0;i<l;i++)
	{
		sum+=a[i]-'0';
		cnt[a[i]-'0']++;
	}
	for(int i=0;i<=8;i++)
	{
		if(sum>=k)  break;
		int num=min(cnt[i],(k-sum+8-i)/(9-i));
		sum+=num*(9-i); ans+=num;
	}
	printf("%d",ans);
	return 0;
}