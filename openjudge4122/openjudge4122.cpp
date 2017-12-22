#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int f[1010];
int n;
string s;

bool judge(int l,int r){
	for(int i=l;i<=r;i++)
		if(s[i]!=s[l+r-i])
			return false;
	return true;
}

void solve(){
	int len=s.length();s=' '+s;
	memset(f,0x3f,sizeof(f));
	f[0]=-1;
	for(int i=1;i<=len;i++)
		for(int j=0;j<=i;j++)
			if(judge(j+1,i))
				f[i]=min(f[i],f[j]+1);
	printf("%d\n",f[len]);
}

int main(){
    freopen("openjudge4122.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	cin>>s;solve();
    }
    return 0;
}