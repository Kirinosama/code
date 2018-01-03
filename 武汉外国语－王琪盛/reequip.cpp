#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define MAXN 260
#define MAXM 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

vector <int> v[2010];
int n,m,a[MAXN],b[MAXM],q,sqr;
int type,opt,l1,r1,l2,r2,k,pos;

void init(){
	sqr=sqrt(m);
	for(int i=1;i<=m;i++)
		v[i/sqr].push_back(b[i]);
	for(int i=1/sqr;i<=m/sqr;i++)
		sort(v[i].begin(),v[i].end());
}

void change(){
	if(!type) a[pos]=k;
	else{
		v[pos/sqr].erase(lower_bound(v[pos/sqr].begin(),v[pos/sqr].end(),b[pos]));
		b[pos]=k;
		v[pos/sqr].insert(lower_bound(v[pos/sqr].begin(),v[pos/sqr].end(),b[pos]),b[pos]);
	}
}

int cnt(int power){
	int sum=0;
	for(int i=l1;i<=r1;i++){
		int L=l2/sqr,R=r2/sqr;
		if(L==R){
			for(int j=l2;j<=r2;j++)
				if(b[j]*a[i]>=power) sum++;
		}
		else{
			for(int j=l2;j<(L+1)*sqr;j++)
				if(b[j]*a[i]>=power) sum++;
			for(int j=R*sqr;j<=r2;j++)
				if(b[j]*a[i]>=power) sum++;
			int cur=(power+a[i]-1)/a[i];
			for(int j=L+1;j<R;j++){
				sum+=v[j].end()-lower_bound(v[j].begin(),v[j].end(),cur);
			}
		}
	}
	return sum;
}

void query(){
	int l=1,r=2000000000,ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(cnt(mid)>=k) ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<endl;
}

void solve(){
	scanf("%d",&opt);
	switch(opt){
		case 0:
			scanf("%d %d %d",&type,&pos,&k);
			change();
			break;
		case 1:
			scanf("%d %d %d %d %d",&l1,&r1,&l2,&r2,&k);
			query();
	}
}

int main(){
    freopen("reequip.in","r",stdin);
    freopen("reequip.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    	scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)
    	scanf("%d",&b[i]);
    init();
    cin>>q;
    while(q--)
    	solve();
    return 0;
}