#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int t,n,W,p,q,w[MAXN],ans;
int a[MAXN],b[MAXN],c[MAXN],d[MAXN],e[MAXN],f[MAXN],x[MAXN],y[MAXN],z[MAXN];

struct yaoqiu{
	int x,y,r;
	void in(){
		scanf("%d %d %d",&x,&y,&r);
	}
	bool judge(){
		if(r==0) return w[x]<=w[y];
		else if(r==1) return w[x]==w[y];
		else return w[x]<w[y];
	}
}task[MAXN];

void make(int mask){
	int sum=0;
	for(int i=1;i<=n;i++){
		if(mask&1) w[i]=W;
		else w[i]=-W; 
		sum+=w[i];
		mask>>=1;
	}
	for(int i=1;i<=q;i++)
		if(!task[i].judge())
			return;
	for(int i=1;i<=p;i++){
		sum+=a[i]*abs(w[x[i]]-w[y[i]]);
		sum+=b[i]*abs(w[y[i]]-w[z[i]]);
		sum+=c[i]*abs(w[z[i]]-w[x[i]]);
		sum+=d[i]*(w[x[i]]-w[y[i]]);
		sum+=e[i]*(w[y[i]]-w[z[i]]);
		sum+=f[i]*(w[z[i]]-w[x[i]]);
	}
	ans=min(ans,sum);
}

void solve(){
	ans=INF;
	for(int i=0;i<(1<<n);i++)
		make(i);
	printf("%d\n",ans);
}

int main(){
    freopen("variable.in","r",stdin);
    scanf("%d",&t);
    while(t--){
   		scanf("%d %d %d %d",&n,&W,&p,&q);
   		for(int i=1;i<=p;i++)
   			scanf("%d %d %d %d %d %d %d %d %d",&x[i],&y[i],&z[i],&a[i],&b[i],&c[i],&d[i],&e[i],&f[i]);
   		for(int i=1;i<=q;i++)
   			task[i].in();
   		if(n<=15) solve();
   	}
    return 0;
}