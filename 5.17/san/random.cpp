#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

#define ii pair<int,int>

int a[30],s[30],edge_cnt;
ii E[100000];

int main(){
	freopen("san.in","w",stdout);
	srand(time(0));
	int n=20;
	for(int i=1;i<=n;i++)s[i]=i;
	random_shuffle(s+1,s+1+n);
	for(int i=1;i<n;i++){
		int cnt=rand()%(n-i)+1;
		for(int j=1;j<=n-i;j++) a[j]=i+j;
		random_shuffle(a+1,a+n-i+1);
		for(int j=1;j<=cnt;j++)
			E[++edge_cnt]=ii(i,a[j]);
	}
	printf("%d %d\n",n,edge_cnt);
	for(int i=1;i<=n;i++)printf("%d ",rand()%201-100);
	cout<<endl;
	for(int i=1;i<=edge_cnt;i++)printf("%d %d\n",E[i].first,E[i].second);
	return 0;
}
