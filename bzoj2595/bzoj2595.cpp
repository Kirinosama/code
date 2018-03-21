#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,a[20][20],line_mask[20];
vector <int> v[20];
int f[20][2048],pre[20][2048],ans,anss;

bool judge(int cur,int last){
	for(int i=1;i<=m;i++){
		if(cur&(1<<(i-1))){
			int flag=last&(1<<(i-1));
			while(i+1<=m && (cur&(1<<i))){
				flag|=last&(1<<i);i++;
			}
			if(!flag) return false;
		}
	}
	return true;
}

int cal(int x,int cur){
	int sum=0;
	for(int i=1;i<=m;i++){
		if(cur&1) sum+=a[x][i];
		cur>>=1;
	}
	return sum;
}

int main(){
    freopen("bzoj2595.in","r",stdin);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++){
    		scanf("%d",&a[i][j]);
    		if(!a[i][j]){
    			line_mask[i]|=1<<(j-1);
    			v[i].push_back(j);
    		}
    	}
    memset(f,0x3f,sizeof(f));
    f[0][line_mask]=0;ans=INF;
    for(int i=1;i<=n;i++)
    	for(int cur=0;cur<1<<m;cur++){
    		if((cur&line_mask[i])!=line_mask[i]) continue;
    		for(int last=0;last<1<<m;last++)
    			if(judge(cur,last)){
    				if(f[i][cur]>f[i-1][last]+cal(i,cur))
    					f[i][cur]=f[i-1][last]+cal(i,cur),pre[i][cur]=last;
    			}
    		if(i==n && f[i][cur]<ans){
    			ans=f[i][cur];
    			anss=cur;
    		}
    	}
    for(int i=n;i>=1;i--){
    	printf("%d\n",anss);
    	anss=pre[i][anss];
    }
    printf("%d",ans);
    return 0;
}