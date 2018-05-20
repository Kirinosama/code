#include<bits/stdc++.h>
using namespace std;
int pos[200],np[200]; int f[200];
namespace io{
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],*iS,*iT,c; int f;
	#define gc() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),(iS==iT?EOF:*iS++):*iS++)
	template<class I>
	inline void ri(I &x){
		for(f=1,c=gc();c>'9'||c<'0';c=gc()) if(c=='-') f=-1;
		for(x=0;c>='0'&&c<='9';c=gc()) x=x*10+(c&15); x*=f;
	}
}
using io::ri;
int main(){
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
	int i,j,k,n,d,a,b,ans=1e9; ri(n); ri(d); ri(a); ri(b);
	for(i=1;i<=n;++i) ri(pos[i]);
	for(i=0;i<(1<<n);++i){
		for(j=1;j<=n;++j) if(i&(1<<j-1)) np[j]=pos[j]-d; else np[j]=pos[j]+d;
		sort(np+1,np+n+1);
		
		for(j=1;j<=n;++j){
			f[j]=1e9;
			for(k=0;k<j;++k)
			f[j]=min(f[j],f[k]+a+b*(np[j]-np[k+1]));
		}
		ans=min(ans,f[n]);
	}
	cout<<ans;
	return 0;
}
