#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define MAXN 50100

map <int,int> mp;

int c[MAXN],a[MAXN],b[MAXN],ans,n;

int lowbit(int x){
	return x&-x;
}

int get_sum(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=c[i];
	return res;
}

void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i))
		c[i]+=k;
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	mp[b[1]]=1;
	for(int i=2;i<=n;i++)
		if(!mp[b[i]])
			mp[b[i]]=mp[b[i-1]]+1;
	for(int i=1;i<=n;i++){
		int tmp=mp[a[i]];
		ans+=get_sum(n)-get_sum(tmp);
		add(tmp,1);
	}
	cout<<ans;
	return 0;
}