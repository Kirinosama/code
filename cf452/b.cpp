#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,x[50],p[50],book[20][2];

bool judge(int a,int b,int c){
	for(int i=1;i<=12;i++)
		p[i]=book[i][a];
	for(int i=13;i<=24;i++)
		p[i]=book[i-12][b];
	for(int i=25;i<=36;i++)
		p[i]=book[i-24][c];
	for(int i=1;i<=36-n+1;i++){
		bool flag=true;
		for(int j=i;j<=i+n-1;j++)
			if(x[j-i+1]!=p[j]){
				flag=false;
				break;
			}
		if(flag) return true;
	}
	return false;
}

void init(){
	book[1][0]=book[1][1]=31;
	book[2][0]=28,book[2][1]=29;
	book[3][0]=book[3][1]=31;
	book[4][0]=book[4][1]=30;
	book[5][0]=book[5][1]=31;
	book[6][0]=book[6][1]=30;
	book[7][0]=book[7][1]=31;
	book[8][0]=book[8][1]=31;
	book[9][0]=book[9][1]=30;
	book[10][0]=book[10][1]=31;
	book[11][0]=book[11][1]=30;
	book[12][0]=book[12][1]=31;
}

int main(){
    freopen("cf452.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&x[i]);
    init();
    if(judge(0,0,0) || judge(1,0,0) || judge(0,1,0) || judge(0,0,1))
    	printf("YES");
    else printf("NO");
    return 0;
}