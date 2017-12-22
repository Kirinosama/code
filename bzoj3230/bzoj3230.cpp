#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

char s[MAXN];
int n,m,k,Rank1[MAXN],Rank2[MAXN],sa1[MAXN],sa2[MAXN],height1[MAXN],height2[MAXN],tmp[MAXN];
ll sum[MAXN],rmq1[MAXN][25],rmq2[MAXN][25];

inline ll read(){
	ll x=0;int w=0;char ch;
	while(ch<'0' || ch>'9')
		w|=(ch=='-'),ch=getchar();
	while(ch>'0' && ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

bool cmp1(const int &x,const int &y){
	if(Rank1[x]!=Rank1[y])
		return Rank1[x]<Rank1[y];
	int l=(x+k<=n)?Rank1[x+k]:-1;
	int r=(y+k<=n)?Rank1[y+k]:-1;
	return l<r;
}

bool cmp2(const int &x,const int &y){
	if(Rank2[x]!=Rank2[y])
		return Rank2[x]<Rank2[y];
	int l=(x+k<=n)?Rank2[x+k]:-1;
	int r=(y+k<=n)?Rank2[y+k]:-1;
	return l<r;
}

inline void make_sa(char *s,int Rank[],int sa[]){
	for(register int i=1;i<=n;i++) Rank[i]=s[i],sa[i]=i;
	for(k=1;k<=n;k=k<<1){
		if(Rank==Rank1) sort(sa+1,sa+1+n,cmp1);
		else sort(sa+1,sa+1+n,cmp2);
		tmp[1]=0;
		for(register int i=2;i<=n;i++){
			if(Rank==Rank1)
				tmp[i]=tmp[i-1]+(cmp1(sa[i-1],sa[i])?1:0);
			else 
				tmp[i]=tmp[i-1]+(cmp2(sa[i-1],sa[i])?1:0);
		}
		for(register int i=1;i<=n;i++) Rank[sa[i]]=tmp[i];
	}
}

inline void make_lcp(char *s,int Rank[],int sa[],int height[]){
	for(register int i=1;i<=n;i++) Rank[sa[i]]=i;
	int h=0;
	for(register int i=1;i<=n;i++){
		if(h) h--;
		int j=sa[Rank[i]-1];
		if(!j){
			height[Rank[i]]=0;
			continue;
		}
		for(;i+h<=n && j+h<=n;h++)
			if(s[i+h]!=s[j+h]) break;
		height[Rank[i]]=h;
	}
}

inline void make_rmq(){
	for(register int i=1;i<=n;i++){
		rmq1[i][0]=(i==1?1e18:height1[i]);
		rmq2[i][0]=(i==1?1e18:height2[i]);
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=20;j++){
			rmq1[i][j]=min(rmq1[i][j-1],rmq1[max(1,i-(1<<(j-1)))][j-1]);
			rmq2[i][j]=min(rmq2[i][j-1],rmq2[max(1,i-(1<<(j-1)))][j-1]);
		}
	}
}

inline void premake(){
	make_sa(s,Rank1,sa1);
	make_lcp(s,Rank1,sa1,height1);
	reverse(s+1,s+1+n);
	make_sa(s,Rank2,sa2);
	make_lcp(s,Rank2,sa2,height2);
	make_rmq();
}

inline void make(int x,ll &l,ll &r){
	if(x>sum[n]){
		l=-1;return;
	}
	l=sa1[lower_bound(sum+1,sum+1+n,x)-sum];
	r=l-1+x-sum[Rank1[l]-1]+height1[Rank1[l]];
}

inline ll rmq(int l,int r,int type){
	if(l>r) swap(l,r);
	ll res=1e18;
	if(l==r) return res;
	int i;
	for(i=0;(1<<(i+1))<r-l;i++);
	if(type==1) return min(rmq1[r][i],rmq1[l+(1<<i)][i]);
	else return min(rmq2[r][i],rmq2[l+(1<<i)][i]);
}

inline ll query(ll x,ll y){
	ll la,lb,ra,rb;
	for(register int i=1;i<=n;i++)
		sum[i]=sum[i-1]+n+1-sa1[i]-height1[i];
	make(x,la,lb);
	make(y,ra,rb);
	if(la==-1 || ra==-1) return -1;
	ll MIN=min(lb-la+1,rb-ra+1);
	ll ans1=min(MIN,rmq(Rank1[la],Rank1[ra],1));
	ll ans2=min(MIN,rmq(Rank2[n-lb+1],Rank2[n-rb+1],2));
	return ans1*ans1+ans2*ans2;
}

int main(){
    freopen("bzoj3230.in","r",stdin);
   // freopen("out1","w",stdout);
    scanf("%d %d\n",&n,&m);
    for(register int i=1;i<=n;i++) scanf("%c",&s[i]);
    premake();ll x,y;
    for(register int i=1;i<=m;i++){
    	x=read(),y=read();
    	printf("%lld\n",query(x,y));
    }
    return 0;
}