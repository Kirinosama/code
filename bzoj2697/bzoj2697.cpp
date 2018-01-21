#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

bool cmp(const int &a,const int &b){
	return a>b;
}

int n,m,a[310],ans;

int main(){
    freopen("bzoj2697.in","r",stdin);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    	scanf("%d",&a[i]);
    sort(a+1,a+1+m,cmp);
    int cur=1;
    for(int i=1;i<=n/2 && cur<=m;i++)
    	ans+=(n+1-i-i)*a[cur++];
    printf("%d",ans);
    return 0;
}