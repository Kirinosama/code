#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int make(int x){
	int res=1;
	for(int i=x;i;i/=10){
		if(i%10) res*=i%10;
	}
	return res;
}

int f[MAXN];
int cnt[10][MAXN],Q;

int main(){
    freopen("cf463.in","r",stdin);
    cin>>Q;
    for(int i=1;i<=1000000;i++){
    	if(i<10) f[i]=i;
    	else f[i]=f[make(i)];
    	cnt[f[i]][i]++;
    }
    for(int i=1;i<=1000000;i++)
    	for(int j=1;j<=9;j++)
    		cnt[j][i]+=cnt[j][i-1];
    while(Q--){
    	int x,y,z;
    	scanf("%d %d %d",&x,&y,&z);
    	printf("%d\n",cnt[z][y]-cnt[z][x-1]);
    }
    return 0;
}