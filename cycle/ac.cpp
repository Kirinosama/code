#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n,a[30];

bool dfs(int x,int k){
	int &l=a[x];
	int &r=(x==1?a[n]:a[x-1]);
	if(l==0 && r==0) return k?true:false;
	if(!k){
		for(int i=1;i<=l;i++){
			l-=i;
			if(dfs(x==n?1:x+1,k^1)==true){
				l+=i;
				return true;
			}
			l+=i;
		}
		for(int i=1;i<=r;i++){
			r-=i;
			if(dfs(x==1?n:x-1,k^1)==true){
				r+=i;
				return true;
			}
			r+=i;
		}
		return false;
	}else{
		for(int i=1;i<=l;i++){
			l-=i;
			if(dfs(x==n?1:x+1,k^1)==false){
				l+=i;
				return false;
			}
			l+=i;
		}
		for(int i=1;i<=r;i++){
			r-=i;
			if(dfs(x==1?n:x-1,k^1)==false){
				r+=i;
				return false;
			}
			r+=i;
		}
		return true;
	}
}

int main(){
	freopen("cycle.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	if(dfs(1,0)) cout<<"YES";
	else cout<<"NO";
	return 0;
}