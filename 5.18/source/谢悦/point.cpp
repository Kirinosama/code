#include<bits/stdc++.h>
using namespace std;
namespace io{
	const int L=(1<<19)+1;
	char ibuf[L],*iS,*iT,c;int f;
	char gc(){
		if(iS==iT){
			iT=(iS=ibuf)+fread(ibuf,1,L,stdin);
			return iS==iT?EOF:*iS++; 
		}
		return*iS++;
	}
	template<class I>void gi(I&x){
		for(f=1,c=gc();c<'0'||c>'9';c=gc())if(c=='-')f=-1;
		for(x=0;c<='9'&&c>='0';c=gc())x=x*10+(c&15);x*=f;
	}
};
using io::gi;
using io::gc;
const int N=205;
int n,d,a,b;
int x[N],cx[N];
int vis[N];
int ans=2000000000;
void dfs(int k){
	if(k==n+1){
		for(int i=1;i<=n;i++)cx[i]=x[i]+vis[i]*d;
		sort(cx+1,cx+n+1);
		int as=a;
		for(int i=2;i<=n;i++){
			as+=min((cx[i]-cx[i-1])*b,a);
		}
		//if(cx[1]==2&&cx[2]==3&&cx[3]==6)cerr<<ans<<endl;
		ans=min(as,ans);
		return ;
	}
	vis[k]=1;
	dfs(k+1);
	vis[k]=-1;
	dfs(k+1);
	vis[k]==0;
}

int main(){
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
	gi(n);gi(d);gi(a);gi(b);
	for(int i=1;i<=n;i++)gi(x[i]);
	dfs(1);
	printf("%d",ans);
	return 0;
}

