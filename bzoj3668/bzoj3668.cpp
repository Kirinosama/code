#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,res[40][2];

int main(){
    freopen("bzoj3668.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<=30;i++)res[i][1]=1;
    for(int i=1;i<=n;i++){
    	char type[5];int x;
    	scanf("%s %d",type,&x);
    	for(int j=0;j<=30;j++){
    		int c=(x>>j)&1;
    		if(type[0]=='A') res[j][0]&=c,res[j][1]&=c;
    		else if(type[0]=='O') res[j][0]|=c,res[j][1]|=c;
    		else res[j][0]^=c,res[j][1]^=c;
    	}
    }
    int sum=0;int ans=0;
    for(int i=30;i>=0;i--){
    	if(res[i][0]==1) ans+=1<<i;
    	else if(res[i][1]==1 && sum+(1<<i)<=m) ans+=1<<i,sum+=(1<<i);
    }
    printf("%d",ans);
    return 0;
}