#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int T,F,sg[MAXN],book[MAXN];

int dfs(int x){
	if(x<F) return sg[x]=0;
	if(sg[x]) return sg[x];
	memset(book,0,sizeof(book));
	for(int i=2;i<=x;i++){
		int cur=0;
		for(int j=1;j<=i-x%i;j++) cur^=sg[x/i];
		for(int j=1;j<=x%i;j++) cur^=sg[x/i+1];
		book[cur]=1;
	}
	for(int i=0;i<=1000;i++)if(!book[i])
		return sg[x]=i;
	return 0;
}

int main(){
    freopen("bzoj3576.in","r",stdin);
    scanf("%d %d",&T,&F);
    for(int i=1;i<=1000;i++) dfs(i);
    while(T--){
    	int n,x,res=0;
    	scanf("%d",&n);
    	for(int i=1;i<=n;i++){
    		scanf("%d",&x);res^=sg[x];
    	}
    	printf("%d",res?1:0);
    	if(T) printf(" ");
    }
    return 0;
}