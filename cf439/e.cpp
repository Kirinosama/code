#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define MAXN 2010
#define MAXM 2000010

int n,a[MAXN],b[MAXN],book[MAXM];
int cnt;

int main()
{
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),book[a[i]]=1;
	for(int i=1;i<=n;i++) scanf("%d",&b[i]),book[b[i]]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(book[(a[i]^b[j])]==1)
				cnt++;
	if(cnt&1) cout<<"Koyomi";
	else cout<<"Karen";
	return 0;
}