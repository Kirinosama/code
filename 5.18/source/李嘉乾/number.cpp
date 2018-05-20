#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxlen=20;

int T,n=0;
ll val_in;
int len_suf,len_prf;
char str[20],str_mat[200];
char str_suf[20],str_prf[20];

void turn(ll w){
	n=0;
	while(w){
		str[++n]=w%10+'0';
		w/=10;
	}
	for(int i=1;i<=n/2;i++)
		swap(str[i],str[n-i+1]);
}

ll get_digit(int p,int d){
	ll w=0;
	for(int i=p;i<=p+d-1;i++)
		w=w*10+str[i]-'0';
	return w;
}

bool make_string(ll L,ll R){
	int p=0,n0=0;
	for(ll tmp,i=L;i<=R;i++){
		n0=0,tmp=i;
		while(tmp){
			str_mat[p+n0+1]=tmp%10+'0';
			tmp/=10;
			++n0;
		}
		for(int i=1;i<=n0/2;i++)
			swap(str_mat[p+i],str_mat[p+n0-i+1]);
		p+=n0;
	}
	//cerr<<p<<endl;
	for(int i=1;i+n-1<=p;i++){
		bool tag=true;
		for(int j=1;j<=n;j++)
			if(str_mat[i+j-1]!=str[j]){
				tag=false;
				break;
			}
		if(tag)
			return true;
	}
	return false;
}

ll chk(int d0,int d1){
	int p=1;
	if(d0+d1<=n){
		//cerr<<d0<<" "<<d1<<"gg"<<endl;
		if(str[n-d0-d1+1]=='0')
			return val_in;
		ll w=get_digit(n-d0-d1+1,d1);
		//cerr<<w<<"???"<<endl;
		if(n-d0-d1>w-1)
			return val_in;
		bool tag;
		if(d0==0)
			tag=(make_string(max(w-n/d1-1,1ll),w));
		else tag=make_string(max(w-n/d1-1,1ll),w+1);
		if(tag){
			if(d0==0)
				return w;
			else return w+1;
		}
	}
	return val_in;
}

void get_nxt(){
	for(int i=len_suf;i>=1;i--){
		if(str_suf[i]!='9'){
			++str_suf[i];
			break;
		}
		else str_suf[i]='0';
	}
}

ll get_suf_prf(){
	ll ans=val_in,res;
	//for(int i=1;i<=n;i++)
	//	cerr<<str[i];
	//cerr<<"gg"<<endl;
	for(int i=1;i<n;i++){
		len_suf=i,len_prf=n-i;
		if(str[i+1]=='0')
			continue;
		for(int j=1;j<=i;j++)
			str_suf[j]=str[j];
		for(int j=i+1;j<=n;j++)
			str_prf[j-i]=str[j];
		get_nxt();
		
		for(int j=min(len_prf,len_suf);j>=0;j--){
			bool tag=true;
			for(int k=1;k<=j;k++)
				if(str_prf[len_prf-j+k]!=str_suf[k]){
					tag=false;
					break;
				}
			if(tag){
				//if(i==2)
				//	cerr<<"ok";
				res=0;
				for(int k=1;k<=len_prf;k++)
					res=res*10+str_prf[k]-'0';
				for(int k=j+1;k<=len_suf;k++)
					res=res*10+str_suf[k]-'0';
				ans=min(ans,res);
				break;
			}
		}
	}
	return ans;
}

int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	
	scanf("%d",&T);
	
	while(T--){
		//if(T%10000==0)
		//	cerr<<T<<endl;
		scanf("%lld",&val_in);
		turn(val_in);
		
		//for(int i=1;i<=n;i++)
		//cerr<<str[i];
		ll ansc=val_in;
		for(int i=1;i<=n;i++)
			for(int j=0;i+j<=n&&j<=i;j++)
				ansc=min(ansc,chk(j,i));
		//cerr<<ansc<<endl;
		ansc=min(ansc,get_suf_prf());
		printf("%lld\n",ansc);
	}
	
	return 0;
}
