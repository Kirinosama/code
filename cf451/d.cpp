#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 2000010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int c[MAXN],a[MAXN],ans;
int n,m,k,book[MAXN];

int lowbit(int x){
	return x&-x;
}

void add(int x,int p){
	for(int i=x;i<=2000000;i+=lowbit(i))
		c[i]+=p;
}

int query(int x){
	int sum=0;
	for(int i=x;i;i-=lowbit(i))
		sum+=c[i];
	return sum;
}

int main(){
    freopen("cf451.in","r",stdin);
    scanf("%d %d %d",&n,&m,&k);k--;
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    	add(a[i],1);
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
    	if(book[i]) continue;
    	int r=a[i]+m-1;
    	int sum=query(r)-query(a[i]-1);
    	int pos_r=upper_bound(a+1,a+n+1,r)-a-1;
    	for(int j=pos_r;j>=pos_r+1+k-sum;j--)
    		book[j]=1,ans++,add(a[j],-1);
    }
    cout<<ans;
    return 0;
}