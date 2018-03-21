#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

char str[1000010];
int len,n,fail[1000010],cnt[1000010],anc[1000010][25];
ll num[1000010];

void solve(){
	ll res=1;
	fail[0]=-1;
	for(int i=0;i<len-1;i++){
		int cur=fail[i];
		while(cur!=-1 && str[cur+1]!=str[i+1]) cur=fail[cur];
		fail[i+1]=str[cur+1]==str[i+1]?cur+1:-1;
	}
	for(int i=0;i<len;i++){
		cnt[i]=fail[i]==-1?0:cnt[fail[i]]+1;
		anc[i][0]=fail[i];
		for(int j=1;j<=20;j++){
			if(anc[i][j-1]==-1) anc[i][j]=-1;
			else anc[i][j]=anc[anc[i][j-1]][j-1];
		}
	}
	for(int i=0;i<len;i++){
		if(fail[i]==-1) continue;
		int cur=i;
		for(int j=20;j>=0;j--)if(anc[cur][j]+1>(i+1)/2){
			cur=anc[cur][j];	
		}
		res=(res*(cnt[cur]+1LL))%1000000007LL;
	}
	printf("%lld\n",res);
}

int main(){
    freopen("bzoj3670.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%s",str);len=strlen(str);
    	solve();
    }
    return 0;
}