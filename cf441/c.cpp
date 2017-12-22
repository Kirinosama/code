#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int v[100],n;

bool judge(int x){
	int k=x;
	int sum=0;
	while(k){
		sum+=k%10;
		k/=10;
	}
	if(x+sum==n) return true;
	return false;
}

void solve(){
	int cnt=0;
	int r=n;
	int l=max(0,n-90);
	for(int i=l;i<=r;i++)
		if(judge(i))
			v[++cnt]=i;
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++) cout<<v[i]<<endl;
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	solve();
	return 0;
}