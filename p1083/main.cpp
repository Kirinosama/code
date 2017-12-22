#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXN 1000010
#define MAXM 1000010

int a[MAXN],b[MAXN],n,m;

struct data{
	int l,r,k;
	void in(){
		scanf("%d %d %d",&k,&l,&r);
	}
}p[MAXM];

bool judge(int mid){
	int sum=0;
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++)
		b[i]+=a[i],b[i+1]-=a[i];
	for(int i=1;i<=mid;i++){
		b[p[i].l]-=p[i].k;b[p[i].r+1]+=p[i].k;
	}
	for(int i=1;i<=n;i++){
		sum=sum+b[i];
		if(sum<0) return false;
	}
	return true;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) p[i].in();
	int l=1,r=m;int ans=1e9;
	while(l<=r){
		int mid=(l+r)>>1;
		if(judge(mid)) l=mid+1;
		else{
			ans=min(ans,mid);
			r=mid-1;
		}
	}
	if(ans==1e9) cout<<0;
	else cout<<-1<<endl<<ans;
	return 0;
}