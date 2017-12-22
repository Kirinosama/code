#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int x,y,book[200010];
queue <ii> Q;

int main(){
    freopen("bzoj1646.in","r",stdin);
    scanf("%d %d",&x,&y);
    Q.push(ii(x,0));
    while(!Q.empty()){
    	ii cur=Q.front();Q.pop();
    	if(cur.first==y){
    		printf("%d",cur.second);
    		break;
    	}
    	if(cur.first+1<=200000 && !book[cur.first+1])
    		book[cur.first+1]=1,Q.push(ii(cur.first+1,cur.second+1));
    	if(cur.first-1>=0 && !book[cur.first-1])
    		book[cur.first-1]=1,Q.push(ii(cur.first-1,cur.second+1));
    	if(cur.first*2<=200000 && !book[cur.first*2])
    		book[cur.first*2]=1,Q.push(ii(cur.first*2,cur.second+1));
    }
    return 0;
}