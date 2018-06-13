#include <bits/stdc++.h>
using namespace std;

#define ii pair<int,int>

ii num[5];

int main(){
	freopen("input","r",stdin);
	for(int i=1;i<=4;i++){
		scanf("%d",&num[i].first);
		num[i].second=i;
		sum+=num[i].first;
	}
	sort(num+1,num+5);
	int minus=abs(num[1].first+num[4].first-num[2].first-num[3].first);
	if(minus){
		if(num[1].first)
	}
	return 0;
}

