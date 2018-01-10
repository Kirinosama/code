#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 500010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct line{
	int l,r;
}s[MAXN];

int n,m,p[MAXN];

int main(){
    freopen("xmasinterval.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    	scanf("%d %d",&s[i].l,&s[i].r);
    for(int i=1;i<=m;i++)
    	scanf("%d",&p[i]);
    sort(s+1,s+n+1,cmp);
    sort(p+1,p+m+1);
    int L=0;
    for(int i=1;i<=m;i++){
    	while(s[L+1].l<=p[i])
    		maxr=max(maxr,p[i].r),L++;
    	if(lastr>=p[i]) continue;
    	else ans++,lastr=maxr;
    }
    return 0;
}