#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n;
unsigned char s[10000010];

int main(){
    freopen("bzoj2176.in","r",stdin);
    scanf("%d %s",&n,s);
    int i=0,j=1,k=0;
    while(i<n && j<n && k<n){
    	int cmp=s[(i+k)%n]-s[(j+k)%n];
    	if(!cmp) k++;
    	else{
    		if(cmp<0) j=j+k+1;
    		else i=i+k+1;
    		if(i==j) j++;
    		k=0;
    	}
    }
	int pos=i<j?i:j;
    for(int i=0;i<n;i++)
    	printf("%c",s[(i+pos)%n]);
    return 0;
}