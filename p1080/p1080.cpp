#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define ii pair<int,int>
#define MAXN 1010
typedef long long ll;

ii a[MAXN];
int n;

struct bignum{
	int len,num[100];
	bignum(){len=0;memset(num,0,sizeof(num));}
	bignum(int x){
		memset(num,0,sizeof(num));
		len=1;
		while(x){
			num[++len]=x%10;
			x/=10;
		}
	}
	bignum operator * (const bignum p){
		bignum q;
		for(int i=1;i<=len;i++)
			for(int j=1;j<=p.len;j++){
				q.num[i+j-1]+=num[i]*p.num[j];
			}
		for(int i=1;i<=len+p.len;i++){
			if(q.num[i]>=10){
				q.num[i+1]+=q.num[i]/10;
				q.num[i]%=10;
			}
			if(q.num[i]) q.len=i;
		}
		return q;
	}	
	bool operator / (const bignum p){
		bignum q;
		if(len<p.len) return bignum(0);
		
	}
	void print(){for(int i=len;i>=1;i--)printf("%d",num[i]);}
}cur;

bool operator < (const ii &p,const ii &q){
	return (ll)p.first*(ll)p.second<(ll)q.first*(ll)q.second;
}

int main(){
	freopen("p1080.in","r",stdin);
	cin>>n>>a[0].first>>a[0].second;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].first,&a[i].second);
	sort(a+0,a+n+1);
	cur=bignum(a[0].first);
	for(int i=1;i<n;i++) cur=cur*bignum(a[i].first);
	cur=cur/bignum(a[n].second);
	cur.print();
	return 0;
}
