#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define MAXN 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll ans,f[MAXN],len[MAXN];
int n,last,cur,cnt,fa[MAXN];
map <int,int> ch[MAXN];
string s;

ll cal(int x){
	return len[x]-len[fa[x]]	;
}

void insert(int c){
	last=cur;cur=++cnt;len[cur]=len[last]+1;
	int p=last;
	for(;p && !ch[p][c];p=fa[p])
		ch[p][c]=cur;
	if(!p){
		fa[cur]=1;ans+=cal(cur);
		return;
	}
	else{
		int q=ch[p][c];
		if(len[q]==len[p]+1){
			fa[cur]=q;ans+=cal(cur);
		}
		else{
			int tmp=++cnt;
			len[tmp]=len[p]+1;
			ch[tmp]=ch[q];fa[tmp]=fa[q];ans+=cal(tmp)-cal(q);
			fa[q]=fa[cur]=tmp;ans+=cal(cur)+cal(q);
			for(;p && ch[p][c]==q;p=fa[p]) ch[p][c]=tmp;
		}
	}
}

void solve(){
	int x;
	scanf("%d",&x);	
	insert(x);
	printf("%lld\n",ans);
}

void dfs(int x){
	cout<<s<<endl;
	map <int,int> :: iterator it;
	for(it=ch[x].begin();it!=ch[x].end();it++){
		s=s+(char)(48+it->first);
		dfs(it->second);
		s=s.substr(0,s.length()-1);
	}
}

int main(){
    freopen("bzoj4516.in","r",stdin);
    scanf("%d",&n);cur=++cnt;f[1]=1;
    for(int i=1;i<=n;i++)
    	solve();	
    return 0;
}