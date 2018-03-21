#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define MAXN 510
#define MAXM 60010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

vector <int> v;
vector <ii> pos[MAXN*MAXN];
map <int,int> mp,mp1;

struct query{
	int lx,ly,rx,ry,k,id;
	void in(){
		scanf("%d%d%d%d%d",&lx,&ly,&rx,&ry,&k);
	}
}Q[MAXM],p1[MAXM],p2[MAXM];

int a[MAXN][MAXN],n,m,cnt;
int ans[MAXM],c[MAXN][MAXN];

int lowbit(int x){
	return x&-x;
}

void add(int x,int y,int k){
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=n;j+=lowbit(j))
			c[i][j]+=k;
}

int getsum(int x,int y){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			res+=c[i][j];
	return res;
}

int cal(query cur){
	return getsum(cur.rx,cur.ry)+getsum(cur.lx-1,cur.ly-1)-getsum(cur.lx-1,cur.ry)-getsum(cur.rx,cur.ly-1);
}

void solve(int l,int r,int L,int R){
	if(L==R){
		for(int i=l;i<=r;i++) ans[Q[i].id]=mp1[L];
		return;
	}
	int mid=(L+R)>>1;
	for(int i=L;i<=mid;i++)
		for(int j=0;j<pos[i].size();j++)
			add(pos[i][j].first,pos[i][j].second,1);
	int cnt1=0,cnt2=0;
	for(int i=l;i<=r;i++){
		if(cal(Q[i])<Q[i].k)
			p2[++cnt2]=Q[i];
		else p1[++cnt1]=Q[i];
	}	
	for(int i=1;i<=cnt1;i++)
		Q[l+i-1]=p1[i];
	for(int i=1;i<=cnt2;i++)
		Q[l+cnt1-1+i]=p2[i];
	solve(l+cnt1,r,mid+1,R);
	for(int i=L;i<=mid;i++)
		for(int j=0;j<pos[i].size();j++)
			add(pos[i][j].first,pos[i][j].second,-1);
	solve(l,l+cnt1-1,L,mid);
}

int main(){
    freopen("bzoj2738.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++){
    		scanf("%d",&a[i][j]);
    		v.push_back(a[i][j]);
    	}
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++)
    	if(!mp[v[i]]){
    		mp[v[i]]=++cnt;
    		mp1[cnt]=v[i];
    	}
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++)
    		pos[mp[a[i][j]]].push_back(ii(i,j));
    for(int i=1;i<=m;i++)
    	Q[i].in(),Q[i].id=i;
    solve(1,m,1,cnt);
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}