#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;
#define ii pair<int,int>
#define INF 0x3f3f3f3f

string str;
int n,Min,ans;

bool judge(int x){
	if(x>=1){
		int sqr=sqrt(x);
		if(sqr*sqr==x) return true;
	}
	return false;
}

void dfs(int x,int k){
	if(x==n){
		if(judge(ans)) Min=min(Min,k);
		return;
	}
	if(k==n && str[x]=='0') dfs(x+1,k);
	else{
		dfs(x+1,k);
		ans=ans*10+str[x]-'0';
		dfs(x+1,k-1);
		ans/=10;
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>str;n=str.length();
	Min=INF;dfs(0,n);
	printf("%d",Min==INF?-1:Min);
	return 0;
}
