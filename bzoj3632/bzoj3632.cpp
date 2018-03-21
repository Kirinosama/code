#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int a[60],n,dis[60][60];

int solve(){
	int res=0;
	double T=100;
	while(T>0.01){
		T*=0.97;
		if(T>0.1){
			int ch=rand()%n+1;bool flag=true;
			for(int i=1;i<=res;i++)if(!dis[ch][a[i]]){
				flag=false;break;
			}
			if(flag) a[++res]=ch;
		}else{
			int ch=rand()%n+1;bool flag=true;
			for(int i=1;i<=res;i++)if(!dis[ch][a[i]]){
				flag=false;break;
			}
			if(flag && rand()%2) a[++res]=ch;
		}
	}
	return res;
}

int main(){
    freopen("bzoj3632.in","r",stdin);
    srand(20010529);
    scanf("%d",&n);int x,y;
    while(scanf("%d%d",&x,&y)!=EOF){
    	dis[x][y]=dis[y][x]=1;
    }int ans=0;
    for(int i=1;i<=20000;i++) ans=max(ans,solve());
    printf("%d",ans);
    return 0;
}