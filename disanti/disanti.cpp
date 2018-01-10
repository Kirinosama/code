#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 1000000007
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int T,k1,k2,l[10],r[10],L[10],R[10];
int MIN1,MAX1,MIN2,MAX2;

ll gcd(ll x,ll y){
	if(!x) return y;
	if(!y) return x;
	return gcd(y,x%y);
}

ll lcm(ll x,ll y){
	return x*y/gcd(x,y);
}

struct fenshu{
	ll x,y;
	void clear(){
		x=0,y=1;
	}
	fenshu operator+(fenshu a){
		fenshu res;
		res.y=lcm(y,a.y);
		res.x=x*(res.y/y)+a.x*(res.y/a.y);
		res.y%=MOD,res.x%=MOD;
		return res;
	}
	fenshu operator-(fenshu a){
		fenshu res;
		res.y=lcm(y,a.y);
		res.x=x*(res.y/y)-a.x*(res.y/a.y);
		res.y%=MOD,res.x%=MOD;
		return res;
	}
	fenshu operator*(fenshu a){
		fenshu res;
		res.y=y*a.y;
		res.x=x*a.x;
		ll g=gcd(res.x,res.y);
		res.x=(res.x/g)%MOD;
		res.y=(res.y/g)%MOD;
		return res;
	}
}f1[10][10010],f2[10][10010],sum1[10010],sum2[10010],sum[10010],ans1,ans2,ans3;

ll pow(ll x,ll k){
	ll res=1;
	while(k){
		if(k&1) res=(res*x)%MOD;
		x=(x*x)%MOD,k>>=1;
	}
	return res;
}

void init(){
	cin>>k1;
    for(int i=1;i<=k1;i++)
    	scanf("%d %d",&l[i],&r[i]);
    cin>>k2;
    for(int i=1;i<=k2;i++)
    	scanf("%d %d",&L[i],&R[i]);
}

fenshu getsum1(int p,int q){
	if(!p) return sum1[q];
	else return sum1[q]-sum1[p-1];
}

fenshu getsum2(int p,int q){
	if(!p) return sum2[q];
	else return sum2[q]-sum2[p-1];
}

void solve(){
	for(int i=0;i<=k1;i++)
		for(int j=0;j<=10000;j++)
			f1[i][j].clear(),f2[i][j].clear();
	f1[0][0]=f2[0][0]=(fenshu){1,1};
	sum1[0]=sum2[0]=(fenshu){1,1};
	for(int i=1;i<=10000;i++){
		sum1[i]=sum1[i-1]+f1[0][i];
		sum2[i]=sum2[i-1]+f2[0][i];
	}
	MIN1=0,MAX1=0;
	for(int i=1;i<=k1;i++){
		MIN1+=l[i],MAX1+=r[i];
		for(int j=MIN1;j<=MAX1;j++){
			int left=max(0,j-r[i]),right=j-l[i];
			f1[i][j]=(fenshu){1,(r[i]-l[i]+1)}*getsum1(left,right);
		}
		sum1[0]=f1[i][0];
		for(int j=1;j<=10000;j++)
			sum1[j]=sum1[j-1]+f1[i][j];
	}
	MIN2=0,MAX2=0;
	for(int i=1;i<=k2;i++){
		MIN2+=L[i],MAX2+=R[i];
		for(int j=MIN2;j<=MAX2;j++){
			int left=max(0,j-R[i]),right=j-L[i];
			f2[i][j]=(fenshu){1,(R[i]-L[i]+1)}*getsum2(left,right);
		}
		sum2[0]=f2[i][0];
		for(int j=1;j<=10000;j++)
			sum2[j]=sum2[j-1]+f2[i][j];
	}
	for(int i=0;i<=MAX1;i++) sum[i].clear();
	sum[0]=f1[k1][0];
	for(int i=1;i<=10000;i++)
		sum[i]=sum[i-1]+f1[k1][i];
	ans1.clear(),ans2.clear(),ans3.clear();
	for(int i=MIN2;i<=MAX2;i++){
		if(MAX1>i)
			ans1=ans1+f2[k2][i]*(su1m[MAX1]-sum[i]);
		ans2=ans2+f2[k2][i]*f1[k1][i];
		if(MIN1<i)
			ans3=ans3+f2[k2][i]*(sum[i-1]-sum[MIN1-1]);
	}
	printf("%lld %lld %lld",ans1.x*pow(ans1.y,MOD-2)%MOD,ans2.x*pow(ans2.y,MOD-2)%MOD,ans3.x*pow(ans3.y,MOD-2)%MOD);
}

int main(){
    freopen("disanti.in","r",stdin);
    cin>>T;
    while(T--){
    	init();
    	solve();
    }
    return 0;
}