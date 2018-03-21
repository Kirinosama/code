#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

string s1,s2;
int fail[100010];

void premake(string s){
	fail[0]=0;
	for(int i=1;i<s.length();i++){
		int cur=fail[i-1];
		while(cur && s[cur]!=s[i]) cur=fail[cur];
		if(s[cur]==s[i]) fail[i]=cur+1;
	}
	for(int i=0;i<s.length();i++) printf("%d ",fail[i]);
}

int main(){
    freopen("p3375.in","r",stdin);
    cin>>s1>>s2;
    premake(s2);
    return 0;
}