#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100010

int n,k,m,x,cnt[MAXN],maxx;
vector <int> v[MAXN];

int main()
{
	freopen("input","r",stdin);
	scanf("%d %d %d",&n,&k,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		cnt[x%m]++;
		v[x%m].push_back(x);
		maxx=max(maxx,cnt[x%m]);
	}
	if(k>maxx) cout<<"No";
	else{
		cout<<"Yes"<<endl;
		for(int i=0;i<m;i++) 
			if((int)v[i].size()>=k){
				for(int j=0;j<k;j++){
					cout<<v[i][j]<<' ';
				}
				return 0;
			}
	}
	return 0;
}