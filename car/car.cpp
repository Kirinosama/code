#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MOD 12015858
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

ll f[30][100010],ans;
int l[30],r[30],vis[30],n;
char s1[20],s2[20];
vector <int> to[30];

void dfs(int x){
	for(int i=0;i<to[x].size();i++)
		dfs(to[x][i]);
	for(int i=1;i<=100000;i++){
		f[x][i]=1;
		for(int j=0;j<to[x].size();j++){
			int y=to[x][j];
			if((!l[y] && r[y]<i) || (!r[y] && l[y]>i)){
				f[x][i]=0;
				break;
			}
			if(!l[y]) f[x][i]=f[x][i]*(f[y][r[y]]-f[y][i-1])%MOD;
			else f[x][i]=f[x][i]*(f[y][i]-f[y][l[y]-1])%MOD;
		}
	}
	for(int i=1;i<=100000;i++)
		f[x][i]=(f[x][i-1]+f[x][i])%MOD;
}

int make(char *s){
	int res=0;
	for(int i=0;i<strlen(s);i++)
		res=res*10+s[i]-'0';
	return res;
}

int main(){
    freopen("car.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%s %s",s1,s2);
    	if(s1[0]>='a' && s1[0]<='z'){
    		vis[i]=1;to[s1[0]-'a'+1].push_back(i);
    		r[i]=make(s2);
    	}
    	else if(s2[0]>='a' && s2[0]<='z'){
    		vis[i]=1;to[s2[0]-'a'+1].push_back(i);
    		l[i]=make(s1);
    	}
    	else
    		l[i]=make(s1),r[i]=make(s2);
    }
    ans=1;
    for(int i=1;i<=n;i++){
    	if(!vis[i]){
    		dfs(i);
    		ans=ans*(f[i][r[i]]-f[i][l[i]-1])%MOD;
    	}
    }
    cout<<ans;
    return 0;
}