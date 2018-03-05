#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 4000010
#define ls (x<<1)
#define rs (x<<1|1)
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,cnt[MAXN],size,a[MAXN],b[MAXN];

inline int read(){
	int x=0,w=0;char ch;
	while(ch<'0' || ch>'9') w|=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return w?-x:x;
}

void add(int x,int k){
	for(int i=x;i;i>>=1) cnt[i]+=k;
}

void query_min(int x){
	if(!cnt[1]){printf("-1\n");return;}
	if(x>=size){printf("%d\n",x-size);return;}
	if(cnt[ls]) query_min(ls);
	else query_min(rs);
 }

void query_max(int x){
	if(!cnt[1]){printf("-1\n");return;}
	if(x>=size){printf("%d\n",x-size);return;}
	if(cnt[rs]) query_max(rs);
	else query_max(ls);	
}

void query_pre(int x){
	int s=size-1,t=size-1+x;
	int cnt1=0,cnt2=0;
	for(;s^t^1;s>>=1,t>>=1){
		if(~s&1) a[++cnt1]=s^1;
		if(t&1) b[++cnt2]=t^1;
	}
	for(int i=1;i<=cnt2;i++)if(cnt[b[i]]){
		query_max(b[i]);return;
	}
	for(int i=cnt1;i>=1;i--)if(cnt[a[i]]){
		query_max(a[i]);return;
	}
	printf("-1\n");
}

void query_suc(int x){
	int s=size-1+x,t=size+n;
	int cnt1=0,cnt2=0;
	for(;s^t^1;s>>=1,t>>=1){
		if(~s&1) a[++cnt1]=s^1;
		if(t&1) b[++cnt2]=t^1;
	}
	for(int i=1;i<=cnt1;i++)if(cnt[a[i]]){
		query_min(a[i]);return;
	}
	for(int i=cnt2;i>=1;i--)if(cnt[b[i]]){
		query_min(b[i]);return;
	}
	printf("-1\n");
}

void solve(){
	int opt=read(),x;
	if(opt!=3 && opt!=4) x=read()+1;
	switch(opt){
		case 1:
			if(!cnt[size+x-1]) add(size+x-1,1);
			break;
		case 2:
			if(cnt[size+x-1]) add(size+x-1,-1);
			break;
		case 3:
			query_min(1);break;
		case 4:
			query_max(1);break;
		case 5:
			query_pre(x);break;
		case 6:
			query_suc(x);break;
		case 7:
			printf("%d\n",cnt[size+x-1]?1:-1);
	}
}

int main(){
    freopen("zkw_seg.in","r",stdin);
    n=read(),m=read();
	size=1;
    while(size<n) size<<=1;
    while(m--)
    	solve();
    return 0;
}