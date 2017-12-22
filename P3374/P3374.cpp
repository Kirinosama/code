#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 500010

int c[MAXN],n,m;

int lowbit(int x){
	return x&-x;
}

void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i))
		c[i]+=k;
}

int get_sum(int x){
	int sum=0;
	for(int i=x;i;i-=lowbit(i))
		sum+=c[i];
	return sum;
}

int query(int l,int r){
	if(l>r) return 0;
	return get_sum(r)-get_sum(l-1);
}

void solve(){
	int type,x,y,k;
	scanf("%d",&type);
	if(type==1){
		scanf("%d %d",&x,&k);
		add(x,k);
	}
	else{
		scanf("%d %d",&x,&y);
		cout<<query(x,y)<<endl;
	}
}

int main()
{
    freopen("P3374.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	static int x;
    	scanf("%d",&x);add(i,x);
    }
    while(m--) solve();
    return 0;
}