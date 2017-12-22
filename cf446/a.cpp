#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
ll max1,max2,x,sum;
int n;

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		sum+=x;
	}
	for(int i=1;i<=n;i++){
		cin>>x;
		max2=max(max2,x);
		if(max2>max1) swap(max2,max1);
	}
	if(sum<=max1+max2) cout<<"YES";
	else cout<<"NO";
	return 0;
}