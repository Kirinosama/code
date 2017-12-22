#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

map <char,int> mp; 
char c;int num;
int s[9000];
int s1[9000];

void premake(){
	mp['0']=0;
	mp['1']=1;
	mp['2']=2;
	mp['3']=3;
	mp['4']=4;
	mp['5']=5;
	mp['6']=6;
	mp['7']=7;
	mp['8']=8;
	mp['9']=9;
	mp['A']=10;
	mp['B']=11;
	mp['C']=12;
	mp['D']=13;
	mp['E']=14;
	mp['F']=15;
}

int main(){
	freopen("input","r",stdin);
	premake();
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("\n");
		for(int j=1;j<=m;j++){
			scanf("%c",&c);
			num=mp[c];
			s1[j*2-1]=num>>2;
			s1[j*2]=num&3;
		}
	}
	return 0;
}