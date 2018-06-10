#include <bits/stdc++.h>
using namespace std;

#define MAXN 300010

bitset <32> all,cur;

int cnt[MAXN*32],n,m;
int nodecnt,rt[MAXN],to[MAXN*32][2];

void make(int &x,int y,int z){
	if(z<0) return;
	int k=all[z];
	to[x][!k]=to[y][!k];
	to[x][k]=++nodecnt;
	cnt[to[x][k]]=cnt[to[y][k]]+1;
	make(to[x][k],to[y][k],z-1);
}

int query(int x,int y,int z){
	if(z<0) return 0;
	int k=cur[z];
	if(cnt[to[x][!k]]-cnt[to[y][!k]]>0){
		return (1<<z)+query(to[x][!k],to[y][!k],z-1);
	}else{
		return query(to[x][k],to[y][k],z-1);
	}
}

void solve(){
	char opt[5];
	int l,r,x;
	scanf("%s",opt);
	if(opt[0]=='A'){
		scanf("%d",&x);
		all^=x;n++;rt[n]=++nodecnt;
		make(rt[n],rt[n-1],31);
	}else{
		scanf("%d%d%d",&l,&r,&x);
		l--,r--;
		cur=all^bitset<32>(x);
		printf("%d\n",query(rt[r],l>=1?rt[l-1]:0,31));
	}
}

void build(int x,int y){
	if(y<0) return;
	to[x][0]=++nodecnt;
	build(to[x][0],y-1);
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>m;all.reset();
	rt[0]=++nodecnt;
	build(rt[0],31);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		all^=x;rt[i]=++nodecnt;
		make(rt[i],rt[i-1],31);
	}	
	while(m--)
		solve();
	return 0;
}
