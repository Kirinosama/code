#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
#define ii pair<int,int>
#define INF 0x3f3f3f3f

int n,a,b,ans,cnt,num[200010];
int tot1,tot2;
char s[200010];

int main(){
	freopen("input","r",stdin);
	scanf("%d%d%d\n",&n,&a,&b);
	for(int i=1;i<=n;i++)scanf("%c",&s[i]);
	for(int i=1;i<=n;i++){
		if(s[i]=='.' && s[i-1]!='.') cnt++;
		if(s[i]=='.') num[cnt]++;
	}
	for(int i=1;i<=cnt;i++){
		tot1+=num[i]/2;
		if(num[i]&1) tot2++;
	}
	ans+=min(a,tot1)+min(b,tot1);
	a-=min(a,tot1);b-=min(b,tot1);
	ans+=min(a+b,tot2);
	cout<<ans;
	return 0;
}
