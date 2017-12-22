#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int a[20][20],b[20][20];
int n,m;

struct data{
	string s;
	int res;
};

struct cmp{
	bool operator()(const data&a,const data&b){
		if(a.res==b.res) return a.s.compare(b.s)>0;
		return a.res>b.res;
	}
};

priority_queue <data,vector<data>,cmp> Q;

int cal(int x,int y){
	return a[x][y]^b[x][y]^b[x-1][y]^b[x][y-1]^b[x][y+1]^b[x+1][y];
}

void solve(int mask){
	string s;int cnt=0;
	for(int i=1;i<=n;i++)
		b[1][i]=mask&1,mask>>=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=m;j++){
			b[i][j]=0;
			if(cal(i-1,j)) b[i][j]=1;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(b[i][j]) cnt++;
			s=s+(char)(b[i][j]+'0');
			if(cal(i,j)) return;
		}

	Q.push((data){s,cnt});
}

int main(){
    freopen("bzoj1647.in","r",stdin);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		scanf("%d",&a[i][j]);
    for(int i=0;i<(1<<m);i++)
    	solve(i);
    if(!Q.size()){
    	printf("IMPOSSIBLE");
    	return 0;
    }
    data ans=Q.top();
    for(int i=0;i<n;i++){
    	for(int j=0;j<m;j++){
    		printf("%c",ans.s[i*m+j]);
    		if(j!=m-1) printf(" ");
    	}
    	if(i!=n-1) printf("\n");
    }
    return 0;
}