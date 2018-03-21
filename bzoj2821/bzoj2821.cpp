#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,c,q,sqr,a[MAXN],num[MAXN];
int cnt[320][MAXN],ans[320][320];
int res[MAXN],lastans;

void solve(){
	int x,y;
	scanf("%d%d",&x,&y);
	x=(x+lastans)%n+1;
	y=(y+lastans)%n+1;
	if(x>y) swap(x,y);
	lastans=0;
	if(x/sqr==y/sqr){
		for(int i=x;i<=y;i++){
			res[a[i]]++;
			if(!(res[a[i]]&1)) lastans++;
			else if(res[a[i]]!=1) lastans--;
		}
		for(int i=x;i<=y;i++) res[a[i]]=0;
	}
	else{
		lastans=ans[x/sqr+1][y/sqr-1];
		for(int i=x;i<(x/sqr+1)*sqr;i++){
			res[a[i]]++;
			if(!((res[a[i]]+cnt[y/sqr-1][a[i]]-cnt[x/sqr][a[i]])&1)) lastans++;
			else if(res[a[i]]+cnt[y/sqr-1][a[i]]-cnt[x/sqr][a[i]]!=1) lastans--;
		}
		for(int i=y/sqr*sqr;i<=y;i++){
			res[a[i]]++;
			if(!((res[a[i]]+cnt[y/sqr-1][a[i]]-cnt[x/sqr][a[i]])&1)) lastans++;
			else if(res[a[i]]+cnt[y/sqr-1][a[i]]-cnt[x/sqr][a[i]]!=1) lastans--;
		}
		for(int i=x;i<(x/sqr+1)*sqr;i++) res[a[i]]--;
		for(int i=y/sqr*sqr;i<=y;i++) res[a[i]]--;	
	}
	printf("%d\n",lastans);
}

int main(){
    freopen("bzoj2821.in","r",stdin);
    cin>>n>>c>>q;sqr=(int)sqrt(n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	cnt[i/sqr][a[i]]++;
    }
    for(int i=1;i<=n/sqr;i++)
    	for(int j=1;j<=c;j++)
    		cnt[i][j]+=cnt[i-1][j];
    for(int i=1/sqr;i<=n/sqr;i++){
    	int cur=0;
    	for(int j=i*sqr;j<=n;j++){
    		num[a[j]]++;
    		if(!(num[a[j]]&1)) cur++;
    		else if(num[a[j]]!=1) cur--;
    		ans[i][j/sqr]=cur;
    	}
    	memset(num,0,sizeof(num));
    }
    while(q--)
    	solve();
    return 0;
}