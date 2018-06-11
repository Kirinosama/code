#include <bits/stdc++.h>
using namespace std;

long long n,m,a,b;

int main(){
	freopen("input","r",stdin);
	cin>>n>>m>>a>>b;
	long long k=n/m;
	if(n%m==0) cout<<0;
	else cout<<min((n-k*m)*b,((k+1)*m-n)*a);
	return 0;
}
