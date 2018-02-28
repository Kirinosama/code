#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 20010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,k,ans,fail[MAXN],g[MAXN];
char str[MAXN];

void solve(int x){
	fail[x]=x-1;
	for(int i=x;i<n;i++){
		int cur=fail[i];
		while(cur!=x-1 && str[cur+1]!=str[i+1]) cur=fail[cur];
		if(str[cur+1]==str[i+1]) fail[i+1]=cur+1;
		else fail[i+1]=x-1;
	}
	for(int i=x;i<n;i++){
		g[i]=-1;
		if(fail[i]==x-1) continue;
		if(g[fail[i]]!=-1) g[i]=g[fail[i]];
		else if(fail[i]-x+1>=k) g[i]=fail[i];
	}
	for(int i=x;i<n;i++){
		if(g[i]!=-1 && 2*(g[i]-x+1)<i-x+1) ans++;
	}
}

int main(){
    freopen("bzoj3620.in","r",stdin);
    scanf("%s %d",str,&k);n=strlen(str);
    for(int i=0;i<n;i++) solve(i);
    printf("%d",ans);
    return 0;
}