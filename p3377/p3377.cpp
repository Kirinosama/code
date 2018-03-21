#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010 
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m;

struct node{
	node *ch[2],*fa;
	int val;
	node(){ch[0]=ch[1]=fa=NULL,val=0;}
	node(int x){ch[0]=ch[1]=fa=NULL,val=x;}
}*root[MAXN];

int main(){
    freopen("p3377.in","r",stdin);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	int x;scanf("%d",&x);
    	root[i]=new node(x);
    }
    for(int i=1;i<=n;i++){
    	for(int j=1;)
    }
    return 0;
}