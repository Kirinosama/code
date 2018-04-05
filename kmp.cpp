#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10010

string s,s1;
int fail[MAXN];

void kmp(string s1,string s){
	int pos=-1;
	for(int i=0;i<s1.length();i++){
		while(pos!=-1 && s[pos+1]!=s1[i]) pos=fail[pos];
		if(s[pos+1]==s1[i]) pos++;
		if(pos==s.length()-1) printf("YES");
	}
}

void getfail(string s){
	fail[0]=-1;
	for(int i=0;i<s.length();i++){
		int cur=fail[i];
		while(cur!=-1 && s[cur+1]!=s[i+1]) cur=fail[cur];
		if(s[i+1]==s[cur+1]) fail[i+1]=cur+1;
		else fail[i+1]=-1;
	}
	for(int i=0;i<s.length();i++)printf("%d ",fail[i]);
}

int main(){
	freopen("kmp.in","r",stdin);
	cin>>s;
	getfail(s);
	cin>>s1;
	kmp(s1,s);
	return 0;
}
