#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXM 1010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct seg{
	int l,r,w;
}t[MAXM];

bool cmp(const seg&a,const seg&b){
	return a.r<b.r;
}

int n,m,k,ans,f[MAXM];

int main(){
    freopen("bzoj1642.in","r",stdin);
    scanf("%d %d %d",&n,&m,&k);
    t[1].l=t[1].r=-1e9;m++;
    for(int i=2;i<=m;i++)
    	scanf("%d %d %d",&t[i].l,&t[i].r,&t[i].w);
    sort(t+1,t+m+1,cmp);
    memset(f,0xef,sizeof(f));
    f[1]=0;ans=0;
    for(int i=2;i<=m;i++)
    	for(int j=1;t[j].r<=t[i].l-k;j++){
    		f[i]=max(f[i],f[j]+t[i].w);
    		ans=max(ans,f[i]);
    	}
    printf("%d",ans);
    return 0;
}