#include<stdio.h>
#include<iostream>
using namespace std;
int Ans[50000],L;
char buf[23000000];
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int Case,n;scanf("%d",&Case);
	while(Case--){
		scanf("%d",&n);
		int len=0;for(;len*(len-1)/2<n;Ans[++len]=0);
		Ans[1]=len;int s=len*(len-1)/2-n;
		while(s){
			int l=0;for(;l*(l-1)/2<=s;l++);l--;
			s-=l*(l-1)/2;Ans[1]-=l;Ans[l]++;
		}
		int now=0;
		for(int i=1;i<=len;i++)
			for(int j=1;j<=Ans[i];j++){
				for(int k=1;k<=i;k++)buf[L++]=now+'0';
				now^=1;
			}
		buf[L++]='\n';
	}
	fwrite(buf,1,L,stdout);
	return 0;
}
