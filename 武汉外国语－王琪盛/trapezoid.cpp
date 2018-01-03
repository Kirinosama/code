#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

#define MAXN 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

map <int,int> mpx1,mpx2,mpy1,mpy2,mpxy11,mpxy12,mpxy21,mpxy22;
vector <int> xxx1[MAXN],yyy1[MAXN],xxx2[MAXN],yyy2[MAXN];
int p,cntx[MAXN],cnty[MAXN];//cntx表示离散化后x的前缀和
int n,xmax,ymax,x,y,q,cnt,xy1cnt,xy2cnt;
int xx[MAXN],yy[MAXN],xy1[MAXN],xy2[MAXN];
int solve1r,solve1l,solve2l,solve2r;
int opt,l,r,k;

struct point{
	int x,y;
}node[MAXN];

void init(int id,int x,int y){
	xx[id]=x,yy[id]=y;
	xy1[id]=x+y;xy2[id]=x-y;
}

void premake(){
	sort(xx+1,xx+n+1);
	sort(yy+1,yy+n+1);
	sort(xy1+1,xy1+n+1);
	sort(xy2+1,xy2+n+1);
	for(int i=1;i<=n;i++){
		if(!mpx1[xx[i]]){
			cnt++;
			cntx[cnt]+=cntx[cnt-1];
			mpx1[xx[i]]=cnt;
			mpx2[cnt]=xx[i];
		}
		cntx[cnt]++;
	}
	cnt=0;
	for(int i=1;i<=n;i++){
		if(!mpy1[yy[i]]){
			cnt++;
			cnty[cnt]+=cnty[cnt-1];
			mpy1[yy[i]]=cnt;
			mpy2[cnt]=yy[i];
		}
		cnty[cnt]++;
	}
	cnt=0;
	for(int i=1;i<=n;i++){
		if(!mpxy11[xy1[i]]){
			mpxy11[xy1[i]]=++cnt;
			mpxy12[cnt]=xy1[i];
		}
	}
	xy1cnt=cnt;
	cnt=0;
	for(int i=1;i<=n;i++){
		if(!mpxy21[xy2[i]]){
			mpxy21[xy2[i]]=++cnt;
			mpxy22[cnt]=xy2[i];
		}
	}
	xy2cnt=cnt;
	for(int i=1;i<=n;i++){
		xxx1[mpxy11[node[i].x+node[i].y]].push_back(node[i].x);
		yyy1[mpxy11[node[i].x+node[i].y]].push_back(node[i].y);
		xxx2[mpxy21[node[i].x-node[i].y]].push_back(node[i].x);
		yyy2[mpxy21[node[i].x-node[i].y]].push_back(node[i].y);
	}
	for(int i=1;i<=xy1cnt;i++){
		sort(xxx1[i].begin(),xxx1[i].end());
		sort(yyy1[i].begin(),yyy1[i].end());
	}
	for(int i=1;i<=xy2cnt;i++){
		sort(xxx2[i].begin(),xxx2[i].end());
		sort(yyy2[i].begin(),yyy2[i].end());
	}
}

int cal(int x,int y){
	if(x<y) return 0;
	return (x-y+2)*(x-y+1)/2;
}

void solve(){
	int ans=0;
	scanf("%d %d %d %d",&opt,&l,&r,&k);
	if(opt==1){
		int L=mpx1[xx[lower_bound(xx+1,xx+n+1,l)-xx-1]];
		int R=mpx1[xx[upper_bound(xx+1,xx+n+1,r)-xx-1]];
		int num=cntx[R]-cntx[L];
		if(num<4){
			printf("0\n");
			return;
		}
		p=max(4,(num+k-1)/k);
		solve1l=xy1[lower_bound(xy1+1,xy1+1+n,l+1)-xy1];
		if(solve1l) solve1l=mpxy11[solve1l];
		solve1r=xy1[upper_bound(xy1+1,xy1+1+n,r+ymax)-xy1-1];
		if(solve1r) solve1r=mpxy11[solve1r];
		solve2l=xy2[lower_bound(xy2+1,xy2+1+n,l-ymax)-xy2];
		if(solve2l) solve2l=mpxy21[solve2l];
		solve2r=xy2[upper_bound(xy2+1,xy2+1+n,r-1)-xy2-1];
		if(solve2r) solve2r=mpxy21[solve2r];
	}
	else{
		int L=mpx2[yy[lower_bound(yy+1,yy+n+1,l)-yy-1]];
		int R=mpx2[yy[upper_bound(yy+1,yy+n+1,r)-yy-1]];
		int num=cnty[R]-cnty[L];
		if(num<4){
			printf("0\n");
			return;
		}
		p=max(4,(num+k-1)/k);
		solve1l=xy1[lower_bound(xy1+1,xy1+1+n,l+1)-xy1];
		if(solve1l) solve1l=mpxy11[solve1l];
		solve1r=xy1[upper_bound(xy1+1,xy1+1+n,xmax+r)-xy1-1];
		if(solve1r) solve1r=mpxy11[solve1r];
		solve2l=xy2[lower_bound(xy2+1,xy2+1+n,1-r)-xy2];
		if(solve2l) solve2l=mpxy21[solve2l];
		solve2r=xy2[upper_bound(xy2+1,xy2+1+n,xmax-l)-xy2-1];
		if(solve2r) solve2r=mpxy21[solve2r];
	}
	if(solve1l && solve1r){
		for(int i=solve1l;i<=solve1r;i++){
			if(opt==1){
				int L=lower_bound(xxx1[i].begin(),xxx1[i].end(),l)-xxx1[i].begin();
				int R=upper_bound(xxx1[i].begin(),xxx1[i].end(),r)-xxx1[i].begin()-1;
				ans+=cal(R-L+1,p);
			}
			else{
				int L=lower_bound(yyy1[i].begin(),yyy1[i].end(),l)-yyy1[i].begin();
				int R=upper_bound(yyy1[i].begin(),yyy1[i].end(),r)-yyy1[i].begin()-1;
				ans+=cal(R-L+1,p);
			}
		}
		for(int i=solve2l;i<=solve2r;i++){
			if(opt==1){
				int L=lower_bound(xxx2[i].begin(),xxx2[i].end(),l)-xxx2[i].begin();
				int R=upper_bound(xxx2[i].begin(),xxx2[i].end(),r)-xxx2[i].begin()-1;
				ans+=cal(R-L+1,p);
			}
			else{
				int L=lower_bound(yyy2[i].begin(),yyy2[i].end(),l)-yyy2[i].begin();
				int R=upper_bound(yyy2[i].begin(),yyy2[i].end(),r)-yyy2[i].begin()-1;
				ans+=cal(R-L+1,p);
			}
		}
	}
	printf("%d\n",ans);
	//printf("%d %d %d %d\n",solve1l,solve1r,solve2l,solve2r);
}

int main(){
    freopen("trapezoid.in","r",stdin);
    freopen("trapezoid.out","w",stdout);
    scanf("%d %d %d",&n,&xmax,&ymax);
    for(int i=1;i<=n;i++){
    	scanf("%d %d",&x,&y);
    	node[i]=(point){x,y};
    	init(i,x,y);
    }
    premake();
    scanf("%d",&q);
    while(q--)
    	solve();
    return 0;
}