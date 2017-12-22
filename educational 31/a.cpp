#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int a[210],res,n,t;

int main(){
	freopen("input","r",stdin);
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i]=86400-a[i];
	}
	for(int i=1;i<=n;i++){
		res=res+a[i];
		if(res>=t){
			cout<<i;
			return 0;
		}
	}
	return 0;
}