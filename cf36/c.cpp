#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,cnt[20],tot[20];
char a[30],b[30];
ll ans,res;

void dfs(int x){
	if(x==n){
		ans=max(ans,res);
		return;
	}
	if(cnt[b[x]-'0']){
		cnt[b[x]-'0']--;
		res=res*10+b[x]-'0';
		dfs(x+1);
		cnt[b[x]-'0']++;
		res/=10;
	}
	for(int i=b[x]-'0'-1;i>=0;i--){
		if(cnt[i]){
			ll cur=res;
			res=res*10+i;cnt[i]--;
			for(int j=9;j>=0;j--)
				for(int k=1;k<=cnt[j];k++)
					res=res*10+j;
			ans=max(ans,res);
			res=cur;cnt[i]++;
			break;
		} 
	}
}

int main(){
    freopen("cf36.in","r",stdin);
    scanf("%s\n%s",a,b);
    for(int i=0;i<strlen(a);i++)
    	cnt[a[i]-'0']++;
    n=strlen(a);
    if(strlen(a)<strlen(b)){
    	for(int i=9;i>=0;i--)
    		while(cnt[i]){
    			printf("%d",i);
    			cnt[i]--;
    		}
    	return 0;
    }
    dfs(0);
    cout<<ans;
    return 0;
}