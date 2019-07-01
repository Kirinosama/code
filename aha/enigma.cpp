#include <bits/stdc++.h>
using namespace std;

int a,b,c;
int tota,totb,totc;
string s;

void solve(){
	tota+=a;
	if(tota>=-25 && tota<=25) return;
	else if(tota<-25) tota+=26;
	else tota-=26;
	totb+=b;
	if(totb>=-25 && totb<=25) return;
	else if(totb<-25) totb+=26;
	else totb-=26;
	totc+=c;
	if(totc>=-25 && totc<=25) return;
	else if(totc<-25) totc+=26;
	else totc-=26;
}

int cal(){
	return (78+tota+totb+totc)%26;
}

int main(){
	//freopen("input","r",stdin);
	cin>>a>>b>>c>>s;	
	for(int i=0;i<s.length();i++){
		solve();
		int k=s[i]+cal();
		if(k>'z') k='a'+k-'z'-1;
		cout<<(char)(k);
	}
	return 0;
}

