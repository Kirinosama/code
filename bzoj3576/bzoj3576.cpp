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

int sg[MAXN],T,f;
int book[MAXN],bz[MAXN];

int cal(int x,int y){
	if(!(x&1) || !(y&1)) return 0;
	return 1;
}

int get(int x){
	if(x<f) return 0;
	if(bz[x]) return sg[x];bz[x]=1;
	for(int i=2;i<=x;i=x/(x/i)+1){
		int t=x/i,l=i,r=min(x,x/(x/i));
		int c[2]={0};
		c[0]=l;if(r>l) c[1]=l+1;
		for(int i=0;i<2;i++)if(c[i]){
			int res=0;
			if((x%c[i])&1) res^=get(t+1);
			if((c[i]-x%c[i])&1) res^=get(t);
			book[res]=x;
		}
	}
	for(int i=0;i<=100000;i++) if(book[i]!=x){
		return sg[x]=i;
	}
	return 0;
}

int main(){
    freopen("bzoj3576.in","r",stdin);
    scanf("%d%d",&T,&f);
    while(T--){
    	int n,x,res=0;
    	scanf("%d",&n);
    	for(int i=1;i<=n;i++){
    		scanf("%d",&x);
    		res^=get(x);
    	}
    	printf("%d",res?1:0);
    	if(T) printf(" ");
    }
    return 0;
}