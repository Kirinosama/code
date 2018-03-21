#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define eps 1e-10
#define MAXN 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;


int n,m,sqr;
int cnt[400];

struct Fraction{
	int up,down;
	double val;
	bool operator > (const Fraction &a)const{
		if(fabs(val-a.val)>eps)return val>a.val;
		else return (ll)up*(ll)a.down>(ll)down*(ll)a.up;
	}
	bool operator < (const Fraction &a)const{
		if(fabs(val-a.val)>eps)return val<a.val;
		else return (ll)up*(ll)a.down<(ll)down*(ll)a.up;
	}
	Fraction(){up=0,down=1;val=0.0;}
	Fraction(int x,int y){up=y,down=x;val=(double)y/(double)x;}
}d[MAXN],v[400][400];

void change(Fraction *A,int &cnt,int l,int r){
	cnt=0;
	for(int i=l;i<=r;i++){
		if(!cnt && d[i]>Fraction()) A[++cnt]=d[i];
		else if(cnt && d[i]>A[cnt]) A[++cnt]=d[i];
	}
}

void solve(){
	static int x,y;int ans=0;
	scanf("%d %d",&x,&y);
	d[x-1]=Fraction(x,y);
	change(v[(x-1)/sqr],cnt[(x-1)/sqr],(x-1)/sqr*sqr,((x-1)/sqr+1)*sqr-1);
	Fraction now;
	for(int i=0;i<=(n-1)/sqr;i++){
		if(!cnt[i]) continue;
		int L=1,R=cnt[i],res=-1;
		while(L<=R){
			int mid=(L+R)>>1;
			if(v[i][mid]>now) res=mid,R=mid-1;
			else L=mid+1;
		}
		if(res!=-1) ans+=cnt[i]-res+1,now=v[i][cnt[i]];
	}
	printf("%d\n",ans);
}

int main(){
    freopen("bzoj2957.in","r",stdin);
    cin>>n>>m;sqr=(int)sqrt(n);
    while(m--)
    	solve();
    return 0;
}