#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

#define Mod 1004535809
#define MAXM 8010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int main(){
	for(ll i=2;i<Mod;i++){
		printf("%lld\n", i);
		fflush(stdout);
		ll cur=i,cnt=0;
		while(cur!=1){
			cnt++;
			cur=(cur*i)%Mod;
		}
		if(cnt==Mod-2){
			cout<<i;
			break;
		}
	}
}