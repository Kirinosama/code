#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll f[110][4],ans;
int n;
string s;

int main(){
	freopen("input","r",stdin);
	f[0][0]=1;cin>>s;n=s.length();s=" "+s;
	for(int i=1;i<=n;i++){
		f[i][0]=f[i-1][0];
		f[i][1]=f[i-1][1];
		f[i][2]=f[i-1][2];
		if(s[i]=='Q'){
			f[i][1]+=f[i-1][0];
			f[i][3]+=f[i-1][2];
		}
		if(s[i]=='A')
			f[i][2]+=f[i-1][1];
		ans+=f[i][3];
	}
	cout<<ans;
	return 0;
}