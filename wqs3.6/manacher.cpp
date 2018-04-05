#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 4000010
#define MOD 10000000007
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,l[MAXN];
char s[MAXN];

void solve(){
	int ans=0,pos=-1,maxright=-1;
	for(int i=1;i<=n;i++){
		if(i<=maxright) l[i]=min(l[2*pos-i],maxright-i+1);
		else l[i]=1;
		for(int &j=l[i];i+j<=n && i-j>=1 && s[i+j]==s[i-j];j++);
		if(i&1) ans=(ans+(l[i]+1)/2)%MOD;
		else ans=(ans+l[i]/2)%MOD;
	}
	printf("%d",ans);
}

int main(){
	freopen("manacher.in","r",stdin);
	scanf("%d\n",&n);n=(n<<1)-1;
	for(int i=1;i<=n;i++)if(i&1){
		scanf("%c",&s[i]);
	}else{
		s[i]='#';
	}
	solve();
	return 0;
}
