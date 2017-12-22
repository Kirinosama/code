#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

bool flag;
int n,res;

int main(){
	cin>>n;
	int res=n;
	for(int i=2;i*i<=n;i++){
		flag=false;
		while(n%i==0){
			n=n/i;
			flag=true;
		}
		if(flag) res=res*(i-1)/i;
	}
	if(n!=1) res=res*(n-1)/n;
	cout<<res;
	return 0;
}