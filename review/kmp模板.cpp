#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

string s1,s2;

int fail[1000010];

void get_fail(string s){
	fail[0]=fail[1]=0;
	for(int i=1;i<=s.length();i++){
		int cur=fail[i];
		while(cur && s2[cur]!=s2[i]) cur=fail[cur];
		if(s2[cur]==s2[i]) fail[i+1]=cur+1;
	}
}

void kmp(){
	int pos=0;
	for(int i=0;i<s1.length();i++){
		while(pos && s2[pos]!=s1[i]) pos=fail[pos];
		if(s2[pos]==s1[i]) pos++;
		if(pos==s2.length()) cout<<i-pos+2<<endl;
	}
	for(int i=1;i<=s2.length();i++) cout<<fail[i]<<' ';
}

int main(){
	freopen("input","r",stdin);
	cin>>s1>>s2;
	get_fail(s2);
	kmp();
	return 0;
}