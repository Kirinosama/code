#include<bits/stdc++.h>
using namespace std;
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
#define pc(x) putchar(x)
using io::ri;
int a[100000]; int gs=1;
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int i,n,T; ri(T);
	for(i=2;i*(i-1)/2<=1e9;++i) a[++gs]=i*(i-1)/2;
	while(T--){
		ri(n);
		for(i=1;i<=gs;++i) if(a[i]>=n) break;
		int c=i*i-2*n,len=i; char rec='0';
		while(len>0){
			if(c==len*len){
				for(i=1;i<=len;++i) pc(rec);
				break;
			}
			for(i=1;c-i*i>=len-i&&c-i*i<=(len-i)*(len-i);++i);
			--i; len-=i; c-=i*i; for(;i;--i) pc(rec);
			if(rec=='0') rec='1'; else rec='0';
		}
		pc('\n');
	}
	return 0;
}
