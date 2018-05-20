#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n,m,s,a[110][110];
int ans;

bool judge(){
	int x=1,y=1,sum=0;
	while(x!=n || y!=m){
		if(x==n) sum+=a[x][y+1],y++;
		else if(y==m) sum+=a[x+1][y],x++;
		else if(a[x+1][y]>a[x][y+1]) sum+=a[x+1][y],x++;
		else sum+=a[x][y+1],y++;
		if(sum>s) return false;
	}
	return sum==s;
}

void dfs(int x,int y){
	if(x==n+1){
		if(judge())ans=(ans+1)%10007;
		return;
	}
	if(x==1 && y==1){
		dfs(y==m?x+1:x,y==m?1:y+1);
		return;
	}
	for(int i=0;i<=s;i++){
		a[x][y]=i;
		dfs(y==m?x+1:x,y==m?1:y+1);
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m>>s;
	dfs(1,1);
	cout<<ans;
	return 0;
}
