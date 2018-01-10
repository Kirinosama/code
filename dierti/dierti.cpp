#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 55
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,ans,f[MAXN][MAXN][MAXN][2][2];
int book[MAXN],cnt1,cnt2;

struct node{
	int a,b;
}s[MAXN];

int main(){
    freopen("dierti.in","r",stdin);
    cin>>n;
    for(int i=1;i<=n;i++){
    	scanf("%d %d",&s[i].a,&s[i].b);
    	ans+=s[i].a+s[i].b;
    }
    if(s[n].a==10){
    	scanf("%d %d",&s[n+1].a,&s[n+1].b);
    	ans+=s[n+1].a+s[n+1].b;
    }
    for(int i=1;i<=n;i++){
    	if(s[i].a+s[i].b==10){
    		if(s[i].a==10) book[i]=2,cnt2++;
    		else book[i]=1,cnt1++;
    	}
    } 
    memset(f,0xef,sizeof(f));
    f[0][0][0][0][0]=0;
    if(s[n].a!=10){
    	for(int i=1;i<=n;i++)
    		for(int j=1;j<=cnt1;j++)
    			for(int k=1;k<=cnt2;k++){
    				f[i][j][k][1][1]=f[i-1][j][k][1][1];
    				f[i][j][k][1][0]=f[i-1][j][k][1][0];
    				f[i][j][k][0][1]=f[i-1][j][k][0][1];
    				f[i][j][k][0][0]=f[i-1][j][k][0][0];
    				if(book[i]==1){
    					f[i][j][k][1][1]=max(f[i][j][k][1][1],f[i-1][j-1][k][0][1]);
    					f[i][j][k][1][0]=max(f[i][j][k][1][0],f[i-1][j-1][k][0][0]);
    				}
    				if(book[i]==2){
    					f[i][j][k][1][1]=max(f[i][j][k][1][1],f[i-1][j][k-1][1][0]);
    					f[i][j][k][0][1]=max(f[i][j][k][0][1],f[i-1][j][k-1][0][0]);
    				}
    				f[i][j][k][1][1]=max(f[i][j][k][1][1],f[i-1][j-1][k][1][1]+s[i].a);
    				f[i][j][k][1][0]=max(f[i][j][k][1][0],f[i-1][j-1][k][1][0]+s[i].a);
    				f[i][j][k][0][1]=max(f[i][j][k][0][1],f[i-1][j-1][k][0][1]+s[i].a);
    				f[i][j][k][0][0]=max(f[i][j][k][0][0],f[i-1][j-1][k][0][0]+s[i].a);
    				f[i][j][k][1][1]=max(f[i][j][k][1][1],f[i-1][j][k-1][1][1]+s[i].a+s[i].b);
    				f[i][j][k][1][0]=max(f[i][j][k][1][0],f[i-1][j][k-1][1][0]+s[i].a+s[i].b);
    				f[i][j][k][0][1]=max(f[i][j][k][0][1],f[i-1][j][k-1][0][1]+s[i].a+s[i].b);
    				f[i][j][k][0][0]=max(f[i][j][k][0][0],f[i-1][j][k-1][0][0]+s[i].a+s[i].b);
    			}
    	if(cnt1 && cnt2)
    		ans+=f[n][cnt1][cnt2][1][1];
    	else if(cnt1)
    		ans+=f[n][cnt1][0][1][0];
    	else if(cnt2)
    		ans+=f[n][0][cnt2][0][1];
    	printf("%d",ans);
    }
    else{
    	cnt2--;
    	for(int i=1;i<=n;i++)
    		for(int j=1;j<=cnt1;j++)
    			for(int k=1;k<=cnt2;k++){
    				f[i][j][k][1][1]=f[i-1][j][k][1][1];
    				f[i][j][k][1][0]=f[i-1][j][k][1][0];
    				f[i][j][k][0][1]=f[i-1][j][k][0][1];
    				f[i][j][k][0][0]=f[i-1][j][k][0][0];
    				if(book[i]==1){
    					f[i][j][k][1][1]=max(f[i][j][k][1][1],f[i-1][j-1][k][0][1]);
    					f[i][j][k][1][0]=max(f[i][j][k][1][0],f[i-1][j-1][k][0][0]);
    				}
    				if(book[i]==2){
    					f[i][j][k][1][1]=max(f[i][j][k][1][1],f[i-1][j][k-1][1][0]);
    					f[i][j][k][0][1]=max(f[i][j][k][0][1],f[i-1][j][k-1][0][0]);
    				}
    				f[i][j][k][1][1]=max(f[i][j][k][1][1],f[i-1][j-1][k][1][1]+s[i].a);
    				f[i][j][k][1][0]=max(f[i][j][k][1][0],f[i-1][j-1][k][1][0]+s[i].a);
    				f[i][j][k][0][1]=max(f[i][j][k][0][1],f[i-1][j-1][k][0][1]+s[i].a);
    				f[i][j][k][0][0]=max(f[i][j][k][0][0],f[i-1][j-1][k][0][0]+s[i].a);
    				f[i][j][k][1][1]=max(f[i][j][k][1][1],f[i-1][j][k-1][1][1]+s[i].a+s[i].b);
    				f[i][j][k][1][0]=max(f[i][j][k][1][0],f[i-1][j][k-1][1][0]+s[i].a+s[i].b);
    				f[i][j][k][0][1]=max(f[i][j][k][0][1],f[i-1][j][k-1][0][1]+s[i].a+s[i].b);
    				f[i][j][k][0][0]=max(f[i][j][k][0][0],f[i-1][j][k-1][0][0]+s[i].a+s[i].b);
    			}
    	if(cnt1 && cnt2)
    		ans+=f[n][cnt1][cnt2][1][1];
    	else if(cnt1)
    		ans+=f[n][cnt1][0][1][0];
    	else if(cnt2)
    		ans+=f[n][0][cnt2][0][1];
    	ans+=s[n+1].a+s[n+1].b;
    	printf("%d",ans);
    }
    return 0;
}