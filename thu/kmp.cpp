#include <bits/stdc++.h>
using namespace std;

string s1,s2;
int fail[100010];

void premake(string s){
	fail[0]=-1;
	for(int i=0;i<s.length();i++){
		int tmp=fail[i];
		while(tmp>=0 && s[tmp+1]!=s[i+1])tmp=fail[tmp];
		if(s[tmp+1]==s[i+1]) fail[i+1]=tmp+1;
		else fail[i+1]=-1;
	}
}

void comp(string s1,string s2){
	int now=0;
	for(int i=0;i<s2.length();i++){
		while(now>=0 && s1[now]!=s2[i]) now=fail[now];
		now++;
		if(now==s1.length()) printf("%d ",i),now=0;
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>s1>>s2;
	premake(s1);
	comp(s1,s2);
	return 0;
}
