#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

void premake(int x){
	for(int i=1;i<=20;i++) anc[x][i]=anc[anc[x][i-1]][i-1];
	f[x][0]=a[anc[x][0]];
	for(int i=1;i<=20;i++) f[x][i]=max(f[x][i-1],f[anc[x][i-1]][i-1]);
	
}

void solve(){
	int opt,x,y;
	scanf("%d%d%d",&opt,&x,&y);
	x^=lastans,y^=lastans;
	if(opt==1){
		a[++n]=y;anc[n][0]=x;
		premake(n);
	}else{

	}
}

int main(){
    freopen("cf463.in","r",stdin);
    cin>>Q;
    while(Q--)
    	solve();
    return 0;
}