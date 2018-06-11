#include <bits/stdc++.h>
using namespace std;

#define MAXN 300010

long long numl[MAXN],numr[MAXN],l[MAXN],r[MAXN];
int n;
string str;
long long ans;

void solve(int x){
	cin>>str;
	int cnt=0;
	for(int i=0;i<str.length();i++){
		int k=(str[i]==')');
		if(k==1 && cnt==0) l[x]++;
		else if(k==1 && cnt>0) cnt--;
		else cnt++;
	}
	cnt=0;
	for(int i=str.length()-1;i>=0;i--){
		int k=(str[i]==')');
		if(k==0 && cnt==0) r[x]++;
		else if(k==0 && cnt>0) cnt--;
		else cnt++;
	}
	if(!l[x]) numl[r[x]]++;
	if(!r[x]) numr[l[x]]++;
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)
		solve(i);
	for(int i=1;i<=n;i++){
		if(!l[i]) ans+=numr[r[i]];
	}
	cout<<ans;
	return 0;
}
