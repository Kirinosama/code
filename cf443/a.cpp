#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010

int n,x,s[MAXN],d[MAXN];

int find(int cur,int x){
	if(s[cur]>x) return s[cur];
	else return s[cur]+((x-s[cur]+1)+d[cur]-1)/d[cur]*d[cur];
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d %d",&s[i],&d[i]);
	}
	x=0;
	for(int i=1;i<=n;i++){
		x=find(i,x);
	}
	cout<<x;
	return 0;
}