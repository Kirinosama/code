#include <bits/stdc++.h>
using namespace std;

int T,n,a,b;
int s[2000010],s1[2000010],fail[2000010];
int ans1,ans2;

void make_fail(){
	fail[1]=0;
	for(int i=1;i<=2*n;i++){
		int cur=fail[i];
		while(cur && s[i+1]!=s[cur+1]) cur=fail[cur];
		fail[i+1]=s[cur+1]==s[i+1]?cur+1:0;
	}
}

int solve(int x){
	for(int i=1;i<=n;i++){
		s[i]=s1[i]%x;
		s[i+n]=s[i];
	}
	make_fail();
	int res=1;
	for(int i=fail[2*n];i>=n+1;i=fail[i])
		res++;
	return res;
}

int main(){
	freopen("input","r",stdin);
	cin>>T;
	while(T--){
		cin>>n>>a>>b;
		for(int i=1;i<=n;i++)scanf("%d",&s1[i]);
		int ans1=solve(a);
		ans1=max(ans1,solve(b));
		printf("%d\n",ans1==1?0:ans1);
	}
	return 0;
}
