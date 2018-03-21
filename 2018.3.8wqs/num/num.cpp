#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 999983
#define MAXN 1010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll f[MAXN][9010],ans;
int n,book[20];
string s;

int main(){
    freopen("num.in","r",stdin);
    freopen("num.out","w",stdout);
    cin>>n>>s;
    for(int i=0;i<s.length();i++)book[s[i]-'0']=1;
  	f[0][0]=1;
    for(int i=1;i<=n;i++)
    	for(int j=0;j<=i*9;j++)
    		for(int k=0;k<=9;k++)if(book[k] && j-k>=0)
    			f[i][j]=(f[i][j]+f[i-1][j-k])%MOD;
    for(int i=0;i<=9*n;i++)ans=(ans+(f[n][i]*f[n][i])%MOD)%MOD;
    ans=(ans*2)%MOD;
    ll mul1=0,mul2=0;
    for(int i=0;i<=n/2*9;i++) mul1=(mul1+(f[n/2][i]*f[n/2][i])%MOD)%MOD;
    for(int i=0;i<=(n+1)/2*9;i++) mul2=(mul2+(f[(n+1)/2][i]*f[(n+1)/2][i])%MOD)%MOD;
    ans-=(mul1*mul2)%MOD;
	printf("%lld",ans>=0?ans:ans+MOD);
    return 0;
}