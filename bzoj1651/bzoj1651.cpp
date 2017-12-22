#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,c[MAXN],res,ans;

int main(){
    freopen("bzoj1651.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	static int l,r;
    	scanf("%d %d",&l,&r);
    	c[l]++,c[r+1]--;
    }
    for(int i=1;i<=1000000;i++){
    	res+=c[i];
    	ans=max(ans,res);
    }
    printf("%d",ans);
    return 0;
}