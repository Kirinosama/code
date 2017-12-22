#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 510

queue <int> Q;
int a[MAXN],Maxx,x,cur,cnt[MAXN],n,k;

int main(){
	freopen("input","r",stdin);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		Q.push(a[i]);Maxx=max(Maxx,a[i]);
	}
	bool flag=false;
	cur=a[1];Q.pop();
	while(1){
		if(cur==Maxx){
			cout<<Maxx;
			return 0;
		}
		int x=Q.front();
		if(cur>x){
			cnt[cur]++;
			Q.pop();Q.push(x);
			if(cnt[cur]==k){
				cout<<cur;
				return 0;
			}
		}
		else{
			cnt[x]++;
			Q.pop();cur=x;
			if(cnt[x]==k){
				cout<<x;
				return 0;
			}
		}
	}
	return 0;
}