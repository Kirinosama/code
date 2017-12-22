#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 100010

int bg[MAXN*2],ed[MAXN*2];
int n,f[MAXN],ans;
char c;

int main()
{
	freopen("input","r",stdin);
	scanf("%d\n",&n);
	memset(bg,-1,sizeof(bg));
	memset(ed,-1,sizeof(ed));
	bg[n]=ed[n]=0;
	for(int i=1;i<=n;i++){
		scanf("%c",&c);
		f[i]=f[i-1]+(c=='1' ? 1 : -1);
	//	cout<<f[i]<<endl;
		if(bg[f[i]+n]==-1) bg[f[i]+n]=i;
		ed[f[i]+n]=i;
	}
	for(int i=0;i<=2*n;i++){
		if(bg[i]!=-1 && ed[i]!=-1)
			ans=max(ans,ed[i]-bg[i]);
	}
	cout<<ans;
	return 0;
}