#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define kind(x) (x>='0' && x<='9' ? 2 : 1)

int p1,p2,p3;
string s;

void print(int x){
	if(s[x]!='-') cout<<s[x];
	else if(x-1>=0 && x+1<s.length()){
		if(kind(s[x-1])!=kind(s[x+1]) || s[x-1]=='-' || s[x+1]=='-' ||  s[x-1]>=s[x+1]){
			cout<<'-';return;
		}
		if(kind(s[x-1])==1){
			if(p3==2){
				for(char i=s[x+1]-1;i>s[x-1];i--)
					for(int j=1;j<=p2;j++){
						if(p1==1) cout<<i;
						if(p1==2) cout<<(char)(i+'A'-'a');
						if(p1==3) cout<<'*';
					}
			}
			else{
				for(char i=s[x-1]+1;i<s[x+1];i++)
					for(int j=1;j<=p2;j++){
						if(p1==1) cout<<i;
						if(p1==2) cout<<(char)(i+'A'-'a');
						if(p1==3) cout<<'*';
					}
			}
		}
		else{
			if(p3==2){
				for(char i=s[x+1]-1;i>s[x-1];i--)
					for(int j=1;j<=p2;j++){
						if(p1==1 || p1==2) cout<<i;
						if(p1==3) cout<<'*';
					}
			}
			else{
				for(char i=s[x-1]+1;i<s[x+1];i++)
					for(int j=1;j<=p2;j++){
						if(p1==1 || p1==2) cout<<i;
						if(p1==3) cout<<'*';
					}
			}
		}
	}	
	else cout<<'-';
}

int main(){
	freopen("input","r",stdin);
	scanf("%d %d %d\n",&p1,&p2,&p3);
	cin>>s;
	for(int i=0;i<s.length();i++) print(i);
	return 0;
}