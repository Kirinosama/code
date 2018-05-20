#include<stdio.h>
#include<iostream>
using namespace std;
typedef long long LL;
namespace INPUT{
	const int L=1<<20;
	char _buf[L],*S,*T,c;int len;
	char _gc(){
		if(S==T){
			T=(S=_buf)+fread(_buf,1,L,stdin);
			if(S==T)return EOF;
		}return *S++;
	}
	void Readi(int&x){
		for(c=_gc();c<'0'||c>'9';c=_gc());
		for(x=0;c>='0'&&c<='9';c=_gc())x=x*10+(c&15);
	}
	int Reads(char s[]){
		for(c=_gc();c<'0'||c>'9';c=_gc());
		for(len=0;c>='0'&&c<='9';c=_gc())s[len++]=c;
		s[len]='\0';return len;
	}
}
using INPUT::Readi;
using INPUT::Reads;
int Case;char s[20];
int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	Readi(Case);
	while(Case--){
		int len=Reads(s);LL Ans=0;
		for(int i=0;i<len;i++)Ans=Ans*10+s[i]-'0';
		for(int l=1;l<=len;l++)
			for(int pre=0;pre<l;pre++)
				for(int suf=0;suf<l;suf++){
					if(len-pre-suf<l)break;
					if(s[pre]=='0'||s[len-suf]=='0')continue;
					LL L,R,ln=0,rn=0;bool tag=1;bool haveAns=0;
					for(int i=0;i<pre;i++)ln=ln*10+s[i]-'0';
					for(int i=0;i<suf;i++)rn=rn*10+s[len-suf+i]-'0';
					if(l>1){
						LL fafa=0;for(int i=1;i<l;i++)fafa=fafa*10+9;
						LL p=0,n;int i;
						for(i=pre;i<len-suf;i+=l-tag){
							for(int j=n=0;j<l-tag&&i+j<len-suf;j++)n=n*10+s[i+j]-'0';
							if(p!=0){
								if(p!=n-1)break;
								if(n==fafa){i--;tag=0;}
							}
							else L=n;
							p=n;
						}
						R=n;
						if(i==len-suf){
							bool tag1=0,tag2=0;
							if(pre==0)tag1=1;
							else{
								LL tmp=ln,tmp1=L-1;bool qwq=1;
								for(int i=0;i<pre;i++){
									if(tmp%10!=tmp1%10)qwq=0;
									tmp/=10;tmp1/=10;
								}
								if(qwq)tag1=1;
							}
							if(suf==0)tag2=1;
							else{
								LL tmp1=R+1;
								for(int i=1;i<=l-suf;i++)tmp1/=10;
								if(tmp1==rn)tag2=1;
							}
							if(tag1&&tag2)haveAns=1;
						}
					}
					if(haveAns)
						if(suf)Ans=min(Ans,R+1);
						else Ans=min(Ans,R);
					else if((len-pre-suf)%l==0){
						LL p=0,n;int i;
						for(i=pre;i<len-suf;i+=l){
							for(int j=n=0;j<l;j++)n=n*10+s[i+j]-'0';
							if(p!=0){if(p!=n-1)break;}
							else L=n;
							p=n;
						}
						R=n;
						if(i==len-suf){
							bool tag1=0,tag2=0;
							if(pre==0)tag1=1;
							else{
								LL tmp=ln,tmp1=L-1;bool qwq=1;
								for(int i=0;i<pre;i++){
									if(tmp%10!=tmp1%10)qwq=0;
									tmp/=10;tmp1/=10;
								}
								if(qwq)tag1=1;
							}
							if(suf==0)tag2=1;
							else{
								LL tmp1=R+1;
								for(int i=1;i<=l-suf;i++)tmp1/=10;
								if(tmp1==rn)tag2=1;
							}
							if(tag1&&tag2)haveAns=1;
						}
						if(haveAns)
							if(suf)Ans=min(Ans,R+1);
							else Ans=min(Ans,R);
					}
				}
		for(int i=1;i<len;i++){
			if(s[i]=='0')continue;
			LL tmp=0,m=0,b=1,B=1;
			for(int j=i;j<len;j++)m=m*10+s[j]-'0';
			for(int j=0;j<i;j++)tmp=tmp*10+s[j]-'0';
			for(int j=0;j<i;j++)B=B*10;
			tmp=(tmp+1)%B;
			for(LL i=10;i<=B;i*=10)if(m&&m%i==tmp/(B/i))b=i;
			Ans=min(Ans,(m/b)*B+tmp);
		}
		printf("%lld\n",Ans);
	}
	return 0;
}
