#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int fail[1000010];
string s1,s;

void get_fail(string s){
	fail[0]=fail[1]=0;
	for(int i=1;i<s.length();i++){
		int cur=fail[i];
		while(cur && s[cur]!=s[i]) cur=fail[cur];
		if(s[cur]==s[i]) fail[i+1]=cur+1;
	}
}

void kmp(){
	int pos=0;
	for(int i=0;i<s.length();i++){
		while(pos && s1[pos]!=s[i]) pos=fail[pos];
		if(s1[pos]==s[i]) pos++;
		if(pos==s1.length()) cout<<i-pos+2<<endl;
	}
	for(int i=1;i<=s1.length();i++) cout<<fail[i]<<' '; 
}

int main(){
	freopen("input","r",stdin);
	cin>>s>>s1;
	get_fail(s1);
	kmp();
	return 0;
}