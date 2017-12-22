#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 200010
#define ii pair<int,int>

int book[MAXN],n,k;

void bfs(){
	queue <ii> Q;
	Q.push(ii(n,0));book[n]=1;
	while(!Q.empty()){
		ii cur=Q.front();Q.pop();
		int x=cur.first,t=cur.second;
		if(x==k){
			printf("%d",t);
			break;
		}
		if(x+1<=200000 && !book[x+1])	Q.push(ii(x+1,t+1)),book[x+1]=1;
		if(x-1>=0 && !book[x-1])	Q.push(ii(x-1,t+1)),book[x-1]=1;
		if(x*2<=200000 && !book[x*2])	Q.push(ii(x*2,t+1)),book[x*2]=1;
	}
}

int main()
{
    freopen("catchcow.in","r",stdin);
    freopen("catchcow.out","w",stdout);
    cin>>n>>k;
    if(n>k) printf("%d",n-k);
    else bfs();
    return 0;
}