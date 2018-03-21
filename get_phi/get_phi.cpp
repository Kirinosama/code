#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int phi[MAXN],m[MAXN],prime[MAXN],cnt;

void get_phi(int N){
	for(int i=2;i<=N;i++){
		if(!m[i]) prime[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt;j++)if(i*prime[j]<=N){
			m[i*prime[j]]=1;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}

int main(){
    freopen("get_phi.in","r",stdin);
    get_phi(1000);
    for(int i=2;i<=100;i++) printf("%d %d\n",i,phi[i]);
    return 0;
}