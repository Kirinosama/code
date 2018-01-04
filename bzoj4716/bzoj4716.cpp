#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

#define MAXN 1010
#define ii pair<int,int>
#define iiii pair<ii,ii>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,xmin,ymin,k,cnt;
int sum[MAXN][MAXN],x,ans;
int MAX;
map <iiii,bool> book;
iiii s;

int cal(ii a,ii b){
	return sum[a.first-1][a.second-1]+sum[b.first][b.second]-sum[b.first][a.second-1]-sum[a.first-1][b.second];
}

struct cmp{
	bool operator()(const iiii &a,const iiii &b)const{
		return cal(a.first,a.second)>cal(b.first,b.second);
	}
};

priority_queue <iiii,vector<iiii>,cmp> Q;

int main(){
    freopen("bzoj4716.in","r",stdin);
    scanf("%d %d %d %d %d",&n,&m,&xmin,&ymin,&k);
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++){
    		scanf("%d",&x);
    		sum[i][j]=sum[i][j-1]+x;
    	}
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		sum[i][j]+=sum[i-1][j];
    for(int i=1;i<=n-xmin+1;i++)
    	for(int j=1;j<=m-ymin+1;j++){
    		book[iiii(ii(i,j),ii(i+xmin-1,j+ymin-1))]=true;
    		Q.push(iiii(ii(i,j),ii(i+xmin-1,j+ymin-1)));
    	}
    while(cnt<k){
    	iiii tp=Q.top();Q.pop();
    	ans=cal(tp.first,tp.second);
    	if(tp.second.first<n){
    		iiii tx=iiii(tp.first,ii(tp.second.first+1,tp.second.second));
    		if(!book[tx]){
    			book[tx]=true;
    			Q.push(tx);
    		}
    	}
    	if(tp.second.second<m){
	    	iiii ty=iiii(tp.first,ii(tp.second.first,tp.second.second+1));
	    	if(!book[ty]){
	    		book[ty]=1;
	    		Q.push(ty);
	    	}
	    }
    	cnt++;
    }
    printf("%d",ans+1);
    return 0;
}