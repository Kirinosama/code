#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int T,n,case_num,cnt,query_num;
ll Log,m[100],a[100];
bool flag;

void solve(ll bit_mask){
	for(ll i=1,highbit=1LL<<(Log-1);i<=Log;i++,highbit>>=1LL)
		if(bit_mask&highbit) bit_mask^=m[i];
	if(!bit_mask)
		flag=true;
	else
		for(ll i=1,highbit=1LL<<(Log-1);i<=Log;i++,highbit>>=1LL)
			if(bit_mask&highbit){
				m[i]=bit_mask;
				for(int j=1;j<i;j++)
					if(m[j]&highbit) m[j]^=bit_mask;
				break;
			}	
}

void init(){
	cin>>n;flag=false;cnt=0;
	memset(m,0,sizeof(m));
	for(int i=1;i<=n;i++){
		static ll x;
		scanf("%lld",&x);
		solve(x);
	}	
}

void solve(){
	printf("Case #%d:\n",++case_num);
	init();
	for(int i=Log;i>=1;i--)
		if(m[i]) a[++cnt]=m[i];
	cin>>query_num;
	while(query_num--){
		ll q,res=0;
		scanf("%lld",&q);
		if(flag) q--;
		for(ll i=1,mul=1;i<=cnt;i++,mul<<=1)
			if(q&mul) res^=a[i],q-=mul;
		printf("%lld\n",(q?-1:res));
	}
}

int main(){
    freopen("hdu3949.in","r",stdin);
    cin>>T;Log=63;
    while(T--)
    	solve();
    return 0;
}