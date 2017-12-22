#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n,x;

int solve(int x){
	if(x==1) return -1;
	else if(x==2) return -1;
	else if(x==3) return -1;
	else if(x==4) return 1;
	else if(x==5) return -1;
	else if(x==6) return 1;
	else if(x==7) return -1;
	else if(x==8) return 2;
	else if(x==9) return 1;
	else if(x==10) return 2;
	else if(x==11) return -1;
	else{
		int cnt=0;
		if(x&1) cnt++,x-=9;
		cnt+=x/4;
		return cnt;
	}
}

int main()
{
	freopen("input","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		cout<<solve(x)<<endl;
	}
	return 0;
}