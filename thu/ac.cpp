#include <bits/stdc++.h>
using namespace std;

int fail[1010];
int n,cnt[1010],to[1010][26],nodecnt,rt;
string str,s;

void add(string s){
	int now=rt;
	for(int i=0;i<s.length();i++){
		int tmp=s[i]-'a';
		if(!to[now][tmp]) to[now][tmp]=++nodecnt;
		now=to[now][tmp];
	}
	cnt[now]++;
}

void makefail(){
	queue<int>Q;
	for(int i=0;i<26;i++)if(to[rt][i])
		Q.push(to[rt][i]),fail[to[rt][i]]=0;
	while(!Q.empty()){
		int tp=Q.front();Q.pop();
		for(int i=0;i<26;i++){
			if(to[tp][i]) fail[to[tp][i]]=to[fail[tp]][i],Q.push(to[tp][i]);
			else to[tp][i]=to[fail[tp]][i];
		}
	}
}

void comp(){
	cin>>s;int now=rt;
	int ans=0;
	for(int i=0;i<s.length();i++){
		int k=s[i]-'a';
		now=to[now][k];
		while(now && cnt[now])ans+=cnt[now],cnt[now]=0,now=fail[now];
	}
	cout<<ans;
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>str,add(str);
	makefail();
	comp();
	return 0;
}
