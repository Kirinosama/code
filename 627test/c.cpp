#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000010
#define ii pair<int,int>
typedef long long ll;

int n,m,cnt,s[MAXN];
int a[MAXN];
ll ans,sum[MAXN];

struct node{
	ll num;int Id;
	node(){num=Id=0;}
	bool operator < (const node &p)const{return num<p.num;}
}c[MAXN];

int lowbit(int x){return x&-x;}

void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i))
		s[i]+=k;
}

int query(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=s[i];
	return res;
}

void premake(){
	for(int i=1;i<=n;i++){
		c[i].num=sum[i];
		c[i].Id=i;
	}
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++)if(sum[i]>=0)ans++;
	for(int i=1;i<=n;i++){
		if(i==1 || c[i].num!=c[i-1].num)cnt++;
		sum[c[i].Id]=cnt;
	}
	for(int i=1;i<=n;i++){
		ans+=(ll)query(sum[i]);
		add(sum[i],1);
	}
}

int main(){
//	freopen("5.in","r",stdin);
//	freopen("c.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	cin>>m;
	for(int i=1;i<=n;i++){
		a[i]-=m;
		sum[i]=sum[i-1]+(ll)a[i];
	}
	premake();
	cout<<ans;
	return 0;
}
