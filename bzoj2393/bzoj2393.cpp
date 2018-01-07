#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll l,r,s1[2000],s[2000],ans,last;
int cnt,cnt1;

void getnum(ll x){
	if(x>r) return;
	s1[++cnt1]=x;
	getnum(x*10+2);
	getnum(x*10+9);
}

int gcd(ll x,ll y){
	if(!x) return y;
	if(!y) return x;
	return gcd(y,x%y);
}

ll cal(ll x,ll y,ll z){
	return y/z-(x+z-1)/z+1;
}

ll lcm(ll x,ll y){
	return x*y/gcd(x,y);
}

void dfs(int num,ll mul){
	if(num){
		if(num&1) ans+=cal(l,r,mul);
		else ans-=cal(l,r,mul);
	}
	for(int i=last+1;i<=cnt;i++){
		if(lcm(s[i],mul)>r) continue;
		int cur=last;
		last=i;
		dfs(num+1,lcm(mul,s[i]));
		last=cur;
	}
}

int main(){
    freopen("bzoj2393.in","r",stdin);
    scanf("%lld %lld",&l,&r);
    getnum(2);
    getnum(9);
    sort(s1+1,s1+1+cnt1);
    for(int i=1;i<=cnt1;i++){
    	bool flag=false;
    	for(int j=1;j<i;j++)
    		if(!(s1[i]%s1[j]))
    			flag=true;
    	if(!flag) s[++cnt]=s1[i];
    }
	last=0;
	dfs(0,1);
	printf("%lld",ans);
    return 0;
}