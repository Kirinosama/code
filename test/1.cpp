#include <bits/stdc++.h>
using namespace std;

int n,m;
char N[20];

int char_to_int(char *s){
	int len=strlen(s),res=0;
	for(int i=len-1;i>=0;i--)res=res+s[i]-'0';
	return res;
}

int main(){
	freopen("input","r",stdin);
	while(scanf("%s",N)!=EOF){
		if(N[0]=='#') break;
		n=char_to_int(N);
		scanf("%d",&m);
		for(int i=1;i<=n;i++){
			char p[20],r[20];
			int q;
			scanf("%s %d",p,&q);
			while(1){
				char c=getchar();
				if(c=='\n') break;
				scanf("%s",r);
			}
		}
	} 
	return 0;
}
