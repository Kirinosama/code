#include<bits/stdc++.h>
using namespace std;
#define pc(x) putchar(x)
namespace ib{char b[100];}
inline void pi(long long x){
	if(x==0){pc(48); return;}
	if(x<0){pc('-'); x=-x;}
	char *s=ib::b;
	while(x) *(++s)=x%10,x/=10;
	while(s!=ib::b) pc(*(s--)+48);
}
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
inline string ch(long long x){
	string a="";
	char *s=ib::b;
	while(x) *(++s)=x%10,x/=10;
	while(s!=ib::b) a+=(char)(*(s--)+48);
	return a;
}
inline long long nu(string x){
	long long a=0; int i;
	for(i=0;i<x.size();++i) a=a*10+(x[i]&15);
	return a;
}
int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int i,j,k,T; ri(T); long long n;
	while(T--){
		ri(n); string a=ch(n);
		long long ans=n; int l=a.size();
		for(j=1;j<l;++j)
		for(i=0;i<j&&i+j<=l;++i){
			string st=a.substr(i,j);
			long long rec=nu(st); //cout<<rec<<endl;
			if(rec>=ans) continue;
			if(i)
			if(rec>1){
				--rec; if(st[st.size()-1]!='0') st[st.size()-1]--; else st=ch(rec); ++rec;
				int ll=st.size();
				for(k=1;k<=i;++k) if(a[i-k]!=st[ll-k]) break;
				if(k<=i) continue;
			}
			else continue;
			st=a.substr(i,j);
			for(k=i+j;k<l;){
				++rec; if(st[st.size()-1]!='9') st[st.size()-1]++; else st=ch(rec);
				int ll=st.size(),ij;
				for(ij=0;ij<min(l-k,ll);++ij) if(a[k+ij]!=st[ij]) break;
				if(ij<min(l-k,ll)) break;
				k+=ll;
			}
			if(k<l) continue;
			ans=min(ans,rec);
		}
		for(i=1;i<l;++i)
		if(a[i]!='0'){
			string st=a.substr(0,i);
			long long rec=nu(st);
			if(rec>=ans) continue;
			++rec; if(st[st.size()-1]!='9') st[st.size()-1]++; else st=ch(rec);
			int ll=st.size();
			for(j=i;j<l;++j)
			if(j+ll>=l){
				for(k=j;k<l;++k)
				if(a[k]!=st[k-j]) break;
				if(k==l) break;
			}
			//cout<<i<<' '<<j<<endl;
			st=a.substr(i,j-i)+st;
			ans=min(ans,nu(st));
		}
		pi(ans),pc('\n');
	}
	return 0;
}
