#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10010

int n,mark[MAXN],prime[MAXN],phi[MAXN];

void get_phi(){
	phi[1]=1;int tot=0;
	for(int i=2;i<=n;i++){
		if(!mark[i]){
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=tot;j++){
			int p=prime[j];
			mark[i*p]=1;
			if(i%p==0){
				phi[i*p]=phi[i]*p;
			}
			else phi[i*p]=phi[i]*phi[p];
		}
	}
	for(int i=1;i<=n;i++){
		printf("phi[%d]=%d\n",i,phi[i]);
	}
}

int main(){
	cin>>n;
	get_phi();
	return 0;
}