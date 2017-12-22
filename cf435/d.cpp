#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define fl fflush(stdout)

int pos0,pos1,k,n;

void dfs(int l,int r,int cur)
{
	int res,cnt[2];
	int mid=(l+r)>>1;
	if(l==r)
	{
		if(cur==0) pos0=l;
		else pos1=l;
		printf("! %d %d\n",pos0,pos1);
		fl;return;
	}
	printf("? ");
	for(int i=1;i<l;i++) printf("0");
	for(int i=l;i<=mid;i++) printf("1");
	for(int i=mid+1;i<=n;i++) printf("0");
	cout<<endl;fl;scanf("%d",&res);
	cnt[1]=(mid-l+1+k-res)>>1;//l到mid1的个数
	cnt[0]=mid-l+1-cnt[1];
	if(cnt[cur]) dfs(l,mid,cur);
	else dfs(mid+1,r,cur);
}

void solve()
{
	int ans1,ans2;
	printf("? ");
	for(int i=1;i<=n;i++) printf("0");
	cout<<endl;fl;
	scanf("%d",&ans1);
	k=ans1;
	printf("? 1");
	for(int i=1;i<n;i++) printf("0");
	cout<<endl;fl;
	scanf("%d",&ans2);
	if(ans1==ans2+1) pos1=1;
	else pos0=1;
	dfs(1,n,pos1 ? 0:1);
}

int main()
{
	//freopen("input","r",stdin);
	scanf("%d",&n);
	solve();
	return 0;
}
