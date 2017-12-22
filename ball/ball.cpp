#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

int n;ll s;
char col;

void solve(){
	ll res=0;
	ll mul=(ll)1<<(n-1);
	for(ll i=1;i<=n;i++){
		if(!(s&mul)) res+=(ll)1<<(i-1);
		mul>>=1;
	}
	cout<<res;
}

int main()
{
    freopen("ball.in","r",stdin);
    freopen("ball.out","w",stdout);
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++){
    	scanf("%c",&col);
    	s=s*2+(col=='R');
    }
    solve();
    return 0;
}