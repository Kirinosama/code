#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n,book[27],book1[27],rem,ans;
int flag;
char type,str[100010];

void merge(char *s){
	memset(book1,0,sizeof(book1));
	for(int i=0;i<strlen(s);i++){
		int c=s[i]-'a'+1;
		if(book[c]) book1[c]=1;
	}
	rem=0;
	for(int i=1;i<=26;i++){
		book[i]=book1[i];
		if(book[i]) rem++;
	}
	if(rem==1)
		for(int i=1;i<=26;i++)
			if(book[i]) flag=i;
}

void out(char *s){
	for(int i=0;i<strlen(s);i++){
		int c=s[i]-'a'+1;
		if(book[c]){
			book[c]=0;
			rem--;
		}
	}
	if(rem==1)
		for(int i=1;i<=26;i++)
			if(book[i]) flag=i;
}

int main(){
	freopen("input","r",stdin);
	scanf("%d\n",&n);
	for(int i=1;i<=26;i++)
		book[i]=1;rem=26;
	for(int i=1;i<=n;i++){
		scanf("%c %s\n",&type,str);
		switch(type){
			case '.':
				if(!flag) out(str);
				break;
			case '!':
				if(!flag) merge(str);
				else ans++;
				break;
			case '?':
				if(!flag) out(str);
				else if(str[0]-'a'+1!=flag) ans++;
		}
	}
	cout<<ans;
	return 0;
}