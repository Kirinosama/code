#include <bits/stdc++.h>
using namespace std;

string s;

int cnt[1010];

bool judge(char a,char b,char c){
	cnt[0]=cnt[1]=cnt[2]=0;
	if(a=='.' || b=='.' || c=='.') return false;
	cnt[a-'A']++;
	cnt[b-'A']++;
	cnt[c-'A']++;
	if(cnt[0]==1 && cnt[1]==1 && cnt[2]==1) return true;
	return false;
}

int main(){
	freopen("input","r",stdin);
	cin>>s;
	for(int i=0;i<s.length();i++){
		if(i+2<s.length()){
			if(judge(s[i],s[i+1],s[i+2])){
				cout<<"Yes";return 0;
			}
		}
	}
	cout<<"No";
	return 0;
}
