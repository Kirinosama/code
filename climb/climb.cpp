#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010
const int INF=1e9;

int a[MAXN],b[MAXN],c[MAXN];
int n,l,ans,lim[MAXN],up[MAXN];
vector <int> v;

int solve(int x){
	int len=l-a[x];
	int sum=0;
	if(len<=0) return 0;
	v.erase(lower_bound(v.begin(),v.end(),-c[x]));
	if(x>1) v.insert(lower_bound(v.begin(),v.end(),-c[x-1]),-c[x-1]);
	for(int i=0;i<n-1;i++){
		sum+=-v[i];
		if(sum<=lim[i+1]) return INF;
		if(sum>=len) return i+1;
	}
	return INF;
}

int main()
{
    freopen("climb.in","r",stdin);
    scanf("%d %d",&n,&l);
    if(l==0){
    	cout<<0;return 0;
    }
    for(int i=1;i<=n;i++){
    	scanf("%d %d",&a[i],&b[i]);
    	c[i]=a[i]-b[i];v.push_back(-c[i]);
    }
    for(int i=1;i<=n;i++){
    	scanf("%d",&up[i]);
    	lim[i]=lim[i-1]+up[i];
    }
    sort(v.begin(),v.end());ans=INF;	
    for(int i=1;i<=n;i++) ans=min(ans,solve(i)+1);
    if(ans<INF) cout<<ans;
	else cout<<-1;
    return 0;
}