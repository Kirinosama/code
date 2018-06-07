#include <bits/stdc++.h>
using namespace std;

set <int> s[4000010];
int pre[1000010];
int t,x;

void premake(){
	s[0].insert(0);
	for(int i=1;i<=1e6;i++){
		pre[i]=pre[i-1]^i;
		s[pre[i]].insert(i);
	}
}

int main(){
	freopen("input","r",stdin);
	cin>>t;
	premake();
	for(int i=1;i<=t;i++){
		scanf("%d",&x);
		for(int i=1;i<=1e6;i++){
			int minus=pre[i]^x;
			if(!s[minus].empty() && *s[minus].begin()<i-1){
				printf("%d %d\n",(*s[minus].begin())+1,i);
				break;
			}
		}
	}
	return 0;
}
