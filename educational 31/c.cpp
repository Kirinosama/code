#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

#define MAXN 100010

typedef long long ll;

stack <int> S;
int fam[MAXN],fam_cnt,dfn[MAXN],low[MAXN],ti;
int n,to[MAXN];
ll ans,cnt[MAXN];

void tarjan(int x){
	dfn[x]=low[x]=++ti;
	S.push(x);
	int y=to[x];
	if(!dfn[y]){
		tarjan(y);
		low[x]=min(low[x],low[y]);
	}
	else if(!fam[y])
		low[x]=min(low[x],dfn[y]);
	if(dfn[x]==low[x]){
		fam_cnt++;
		while(S.top()!=x){
			fam[S.top()]=fam_cnt;
			S.pop();cnt[fam_cnt]++;
		}
		fam[S.top()]=fam_cnt;
			S.pop();cnt[fam_cnt]++;
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&to[i]);
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	if(fam_cnt==1) cout<<cnt[1]*cnt[1];
	else{
		sort(cnt+1,cnt+1+fam_cnt);
		for(int i=1;i<=fam_cnt-2;i++) ans+=cnt[i]*cnt[i];
		ans+=(cnt[fam_cnt-1]+cnt[fam_cnt])*(cnt[fam_cnt-1]+cnt[fam_cnt]);
		cout<<ans;
	}
	return 0;
}