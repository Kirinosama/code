#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 500010
#define INF 0x3f3f3f3f
#define ii pair<int,int>
typedef long long ll;

vector <int> v;
int n,a[MAXN];

int cal(){
	int now=0;
	for(int i=0;i<v.size();i++){
		if(v[i]<now) now--;
		else if(v[i]>now) now++;
	}
	return now;
}

int main(){
	//freopen("ni.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		v.insert(lower_bound(v.begin(),v.end(),a[i]),a[i]);
		printf("%d\n",cal());
	}
	return 0;
}
