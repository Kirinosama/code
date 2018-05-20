#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int a[1010],f[100010],pre[100010];
int sqr[100010],gap[100010],gapcnt;

void make(int x){
	int cnt=0,INF=0x3f3f3f3f;
	for(int i=1;i*(i+1)/2<=x;i++){
		a[++cnt]=(i+1)*i/2;
		sqr[(i+1)*i/2]=i;
	}
	memset(f,0x3f,sizeof(f));f[0]=0;
	for(int t=1;t<=20;t++){
		for(int i=1;i<=x;i++){
			for(int j=1;j<=cnt && i>=a[j];j++)if(f[i-a[j]]!=INF)
				if(f[i-a[j]]+1<=f[i]) f[i]=f[i-a[j]]+1,pre[i]=i-a[j];
		}
	}
	gapcnt=0;
	for(int i=x;i;i=pre[i])gap[++gapcnt]=sqr[i-pre[i]]+1;
}
	
vector<char>STRING(int n)
{
	vector<char>ans;
	if(!n){
		ans.push_back('0');
		return ans;
	}
	int len=0;
	while(len*(len+1)<2*n) len++;
	int minus=len*(len+1)/2-n;
	make(minus);
	int now=0;
	for(int i=1;i<=gapcnt;i++){
		for(int j=1;j<=gap[i];j++)ans.push_back('0'+now);
		now^=1;
	}
	int curlen=ans.size();
	for(int i=1;i<=len+1-curlen;i++,now^=1)
		ans.push_back(now+'0');
	return ans;
}
