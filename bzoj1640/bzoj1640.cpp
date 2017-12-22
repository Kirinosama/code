#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 2010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,len;
char a[MAXN],ans[MAXN];

int main(){
    freopen("bzoj1640.in","r",stdin);
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++)
    	scanf("%c\n",&a[i]);
    int l=1,r=n;
    while(l<=r){
    	if(a[l]<a[r]) ans[++len]=a[l++];
    	else if(a[l]>a[r]) ans[++len]=a[r--];
    	else{
    		int cur=len;
    		for(int i=1;l+i<=r-i;i++){
    			if(a[l+i]<a[r-i]){
    				ans[++len]=a[l++];
    				break;
    			}
    			else if(a[l+i]>a[r-i]){
    				ans[++len]=a[r--];
    				break;
    			}
    		} 
    		if(len==cur) ans[++len]=a[l++];
    	}
    }
    for(int i=1;i<=len;i++){
    	printf("%c",ans[i]);
    	if(i%80==0) printf("\n");
    }
    return 0;
}