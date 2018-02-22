#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,a,b,ans[1000010];

void solve(int x,int y){
	for(int i=1;i<=x;i++){
		for(int j=1+(i-1)*a;j<1+i*a-1;j++)
			ans[j]=j+1;
		ans[1+i*a-1]=1+(i-1)*a;
	}
	for(int i=1;i<=y;i++){
		for(int j=a*x+1+(i-1)*b;j<a*x+1+i*b-1;j++)
			ans[j]=j+1;
		ans[a*x+1+i*b-1]=a*x+1+(i-1)*b;
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
}

int main(){
    freopen("cf463.in","r",stdin);
    scanf("%d %d %d",&n,&a,&b);
    for(int i=0;i<=n/a;i++){
    	if(!((n-i*a)%b)){
    		solve(i,(n-i*a)/b);
    		return 0;
    	}
    }
    cout<<-1;
    return 0;
}