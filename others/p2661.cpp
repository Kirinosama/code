#include <bits/stdc++.h>
using namespace std;

#define MAXN 1010
#define m(x) ((x)*(x))
typedef long long ll;

struct ball{
	ll x,y,z;
	void read(){scanf("%lld%lld%lld",&x,&y,&z);}
	ll dis(ball q){
		return m(x-q.x)+m(y-q.y)+m(z-q.z);
	}
}p[MAXN];

int n,h,r,T,fa[MAXN];

int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

void merge(int x,int y){
	int fx=find(x);
	int fy=find(y);
	fa[fx]=fy;
}

void solve(){
	for(int i=1;i<=n+2;i++)
		fa[i]=i;
	for(int i=1;i<=n;i++){
		if(abs(p[i].z)<=r) merge(i,n+1);
		if(abs(p[i].z-h)<=r) merge(i,n+2);
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(p[i].dis(p[j])<=4ll*r*r) 
				merge(i,j);
	if(find(n+1)==find(n+2)) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
}

int main(){
	freopen("input","r",stdin);
	cin>>T;
	while(T--){
		cin>>n>>h>>r;
		for(int i=1;i<=n;i++)
			p[i].read();
		solve();
	}
	return 0;
}
