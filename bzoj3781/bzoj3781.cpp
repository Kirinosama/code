#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 50010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int sqr,n,m,k,a[MAXN],cnt[MAXN];
ll anss[MAXN];

struct query{
	int l,r,ID;
	bool operator < (const query &a)const{
		if(l/sqr==a.l/sqr) return r<a.r;
		else return l/sqr<a.l/sqr;
	}
}q[MAXN];

int s(int x){
	return x*x;
}

int main(){
    freopen("bzoj3781.in","r",stdin);
    scanf("%d%d%d",&n,&m,&k);sqr=sqrt(n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)scanf("%d%d",&q[i].l,&q[i].r),q[i].ID=i;
    sort(q+1,q+m+1);
	int l=1,r=1;ll ans=1;cnt[a[1]]=1;
	for(int i=1;i<=m;i++){
		while(l>q[i].l){
			l--;
			ans+=s(cnt[a[l]]+1)-s(cnt[a[l]]);
			cnt[a[l]]++;
		}
		while(r<q[i].r){
			r++;
			ans+=s(cnt[a[r]]+1)-s(cnt[a[r]]);
			cnt[a[r]]++;
		}
		while(l<q[i].l){
			ans+=s(cnt[a[l]]-1)-s(cnt[a[l]]);
			cnt[a[l]]--;
			l++;
		}
		while(r>q[i].r){
			ans+=s(cnt[a[r]]-1)-s(cnt[a[r]]);
			cnt[a[r]]--;
			r--;
		}
		anss[q[i].ID]=ans;
	}
	for(int i=1;i<=m;i++) printf("%lld\n",anss[i]);
    return 0;
}