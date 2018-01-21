#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,pos,l,r;

int main(){
    freopen("cf36.in","r",stdin);
    scanf("%d %d %d %d",&n,&pos,&l,&r);
    if(l==1 && r==n){
    	printf("0");
    	return 0;
    }
    else if(l==1){
    	cout<<abs(r-pos)+1;
    	return 0;
    }
    else if(r==n){
    	cout<<abs(l-pos)+1;
    	return 0;
    }
    else{
    	cout<<max(abs(l-pos),abs(r-pos))+abs(l-r)+2;
    }
    return 0;
}