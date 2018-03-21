#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

void exgcd(int a,int b,int &d,int &x,int &y){
	if(!b){
		d=a,x=1,y=0;
	}else{
		exgcd(b,a%b,d,y,x);
		y-=(a/b)*x;
	}
}

int inv(int p,int q){
	int d,x,y;
	exgcd(p,q,d,x,y);
	return d==1 ? (x+q)%q : -1;
}

int n,x[10010],y[10010];

int main(){
    freopen("china_math.in","r",stdin);
    cin>>n;int mul=1,ans=0;
    for(int i=1;i<=n;i++)scanf("%d %d",&x[i],&y[i]),mul*=x[i];
    for(int i=1;i<=n;i++){
    	int X=mul/x[i];
    	ans+=(y[i]*X*inv(X,x[i]))%mul;
   		ans%=mul;
    }
    cout<<ans;
    return 0;
}