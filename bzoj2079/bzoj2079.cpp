#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n,m,u,v,size[200010];

int main(){
	freopen("input","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&u,&v);
		size[u]++,size[v]++;
	}
	for(int i=1;i<=n;i++)
		if(!size[i]){
			printf("NIE");
			return 0;
		}
	printf("TAK");
	return 0;
}