#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 3000010
typedef long long ll;

ll inv[MAXN],p,q;

void get_inv(){
	inv[1]=1;
	for(int i=2;i<=p;i++)
		inv[i]=((q-q/i)*inv[q%i])%q;
	for(int i=1;i<=p;i++) cout<<inv[i]<<endl;
}

int main(){
	freopen("input","r",stdin);
	cin>>p>>q;
	get_inv();
	return 0;
}