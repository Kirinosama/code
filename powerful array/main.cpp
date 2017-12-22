#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>

const int cd=555;
#define MAXN 200010


struct ques
{
	int ll,rr,num;
}Q[MAXN];

int n,m,a[MAXN],l[MAXN],r[MAXN];
int cl,cr,cnt[1000010];
long long ans;
long long anss[MAXN];

bool operator < (const ques &a,const ques &b)
{
	if(a.ll==b.ll)
		return a.rr<b.rr;
	else
		return a.ll<b.ll;
}

void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		ans+=(long long)((cnt[a[i]]*2+1)*a[i]);
		++cnt[a[i]];
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d",&l[i],&r[i]);
		Q[i].ll=l[i]/cd+1;
		Q[i].rr=r[i]/cd+1;
		Q[i].num=i;
	}
	std::sort(Q+1,Q+m+1);
	cl=1;cr=n;
}

int main()
{
	freopen("input","r",stdin);
	read();
	for(int i=1;i<=m;i++)
	{
		int xxx=Q[i].num;
		while(cl<l[xxx])//删点
		{
			ans-=(long long)((cnt[a[cl]]*2-1)*a[cl]);
			--cnt[a[cl]];
			cl++;
		}
		while(cl>l[xxx])
		{
			--cl;
			ans+=(long long)((cnt[a[cl]]*2+1)*a[cl]);
			++cnt[a[cl]];
		}
		while(cr<r[xxx])
		{
			++cr;
			ans+=(long long)((cnt[a[cr]]*2+1)*a[cr]);
			cnt[a[cr]]++;
		}
		while(cr>r[xxx])
		{
			ans-=(long long)((cnt[a[cr]]*2-1)*a[cr]);
			cnt[a[cr]]--;
			--cr;
		}
		anss[xxx]=ans;
	}
	for(int i=1;i<=m;i++)
		std::cout<<anss[i]<<std::endl;
	return 0;
}