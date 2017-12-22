#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int cnt,n,a[2010];

int gcd(int x,int y){
	if(!x) return y;
	if(!y) return x;
	return gcd(y,x%y);
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]==1) cnt++;
	}
	if(n==1){
		if(a[1]==1) cout<<0;
		else cout<<-1;
		return 0;
	} 
	if(cnt>0) cout<<n-cnt;
	else{
		int dis=1e9;
		for(int i=1;i<n;i++){
			int cur=a[i];
			for(int j=i+1;j<=n;j++){
				cur=gcd(cur,a[j]);
				if(cur==1){
					dis=min(dis,j-i);
					break;
				}
			}
		}
		if(dis==1e9) cout<<-1;
		else cout<<dis+(n-1);
	}
	return 0;
}