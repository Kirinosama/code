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
const int N=20;
int T,tt=0;
long long n,nn;
int ch[N];
long long p10[N],vs[N];
int pos[N];
int bl[N*N],tot=0;
long long ck(int x,int y){
	if(x==tt&&y==1)return n;
	if(y-1>=x){
		if(ch[y-1-x+1]==0||ch[y]==0)return 1000000000000000000ll;
		long long se=vs[y-1]-vs[y-1-x]*p10[x];
		tot=0;
		int ps=0;
		for(long long i=se+1;i>=se-17;i--){
			long long vl=i;
			while(vl){
				bl[++tot]=vl%10;
				vl/=10;
			}
			if(i==se+1)ps=tot;
		}
		for(int i=1;i<=tot;i++)if(i<tot-i+1)swap(bl[i],bl[tot-i+1]);
		ps=tot-ps+1;
		int ju=1;
	    //if(n==123124125126&&se==125)cerr<<"***"<<endl;
		for(int i=1;i<=tt&&ju==1;i++){
			//ps-y+i;
			//if(n==123124125126&&se==125)cerr<<i<<" "<<ps-y+i<<endl;
			if(ps-y+i<=0||ps-y+i>tot)ju=0;
			if(bl[ps-y+i]!=ch[i])ju=0;
		}
		/*if(n==123124125126&&se==125){
			for(int i=1;i<=tot;i++)cerr<<bl[i];cerr<<endl;
			for(int i=1;i<=tt;i++)cerr<<ch[i];cerr<<endl;
			cerr<<ju<<" "<<se<<endl;
		}*/
		//if(n==123124125126&&se==125)cerr<<"****"<<endl;
		if(ju==1)return se+1;
		else return 1000000000000000000ll;
	}
	else{
		if(pos[y]==1)return 1000000000000000000ll;
		pos[y]=1;
		if(ch[y]==0)return 1000000000000000000ll;
		long long vl=(vs[y-1]+1)%p10[y-1];
		long long res=n-p10[tt-y+1]*vs[y-1];
		
		long long tl=0;
		int cc=y-1,dd=tt-(y-1)+1,bl=-1;
		while(dd<y){
			dd++;
			tl+=(vl%10)*p10[++bl];
			vl/=10;
		}
		for(int i=max(y,tt-(y-1)+1);i<=tt;i++){
			long long cl=n-p10[tt-i+1]*vs[i-1];
			if(vl==cl){
				return res*p10[bl+1]+tl;
			}
			tl+=(vl%10)*p10[++bl];
			vl/=10;
	//	if(x==7&&y==7)cerr<<vl<<" "<<tl<<endl;
		}
		return res*p10[y-1]+tl;
	}
}

int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	gi(T);
	p10[0]=1;
	for(int i=1;i<=18;i++)p10[i]=p10[i-1]*10;
	while(T--){
		gi(n);
		nn=n;
		tt=0;
		while(nn){
			ch[++tt]=nn%10;
			nn/=10;
		}
		for(int i=1;i<=tt;i++)if(i<tt-i+1)swap(ch[i],ch[tt-i+1]);
		vs[0]=0;
		for(int i=1;i<=tt;i++)vs[i]=vs[i-1]*10+ch[i];
		
		long long ans=1000000000000000000ll;
		for(int i=1;i<=tt;i++){
			for(int j=1;j<=tt;j++){
				long long fl=ck(i,j);
			//	if(fl==12345000000)cerr<<i<<" "<<j<<endl;
				ans=min(ans,fl);
			}
		}
		printf("%lld\n",ans);
		memset(pos,0,sizeof(pos));
	}
	return 0;
}

