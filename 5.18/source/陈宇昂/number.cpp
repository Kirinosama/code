#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

int T;
LL N,Ans;
int S[20];
LL P[20];

int Calc(LL x){
	int cnt=0;
	while(x)
		cnt++,x/=10;
	return cnt;
}

bool Check(LL x,int l,int r){
	if(!S[l])
		return false;
	int now=0;
	while(x){
		now++;
		if(x%10!=S[r-now+1])
			return false;
		x/=10;
	}
	return true;
}

void Work(){
	int i,j,l=0,k;
	LL t;
	Ans=(1ll<<60);
	for(t=N;t;t/=10)
		S[++l]=t%10;
	for(i=1;i<=l-i+1;i++)
		swap(S[i],S[l-i+1]);
	for(i=1;i<=l;i++)
		if(S[i]){
			LL now=0;
			for(j=i;j<=l;j++){
				now=now*10+S[j];
				if((now>1&&Calc(now-1)<=i-1)||(now==1&&i>1))
					continue;
				if(i>1&&!Check((now-1)%P[i-1],1,i-1))
					continue;
				t=now,k=j+1;
				bool f=true;
				while(1){
					t++;
					int a=Calc(t);
					if(l-k+1<a)
						break;
					if(!Check(t,k,k+a-1)){
						f=false;
						break;
					}
					k+=a;
				}
				if(!f)
					continue;
				if(k==l+1)
					Ans=min(Ans,t-1);
				else{
					int a=Calc(t);
					if(Check(t/P[a-(l-k+1)],k,l))
						Ans=min(Ans,t);
				}
				//if(t-1==99998027366400ll)
				//	printf("%d %d\n",i,j);
			}
		}
	printf("%lld\n",Ans);
}

int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int i;
	for(P[0]=i=1;i<19;i++)
		P[i]=P[i-1]*10;
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&N);
		Work();
	}
	return 0;
}
