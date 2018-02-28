#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 15010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int hash1[MAXN],hash2[MAXN],mul1[MAXN],mul2[MAXN],k,n;
char str[MAXN];

bool judge(int l,int r,int L,int R){
	int res1=hash1[r]-((ll)hash1[l-1]*(ll)mul1[r-l+1])%1923717;
	int res2=hash2[r]-((ll)hash2[l-1]*(ll)mul2[r-l+1])%2142147;
	int Res1=hash1[R]-((ll)hash1[L-1]*(ll)mul1[R-L+1])%1923717;
	int Res2=hash2[R]-((ll)hash2[L-1]*(ll)mul2[R-L+1])%2142147;
	if(res1<0) res1+=1923717;if(res2<0) res2+=2142147;
	if(Res1<0) Res1+=1923717;if(Res2<0) Res2+=2142147;
	return res1==Res1 && res2==Res2;
}

int solve(int l,int r){
	if(r-l+1<3) return 0;
	for(int i=k;i<=(r-l)/2;i++)
		if(judge(l,l+i-1,r-i+1,r))
			return 1;
	return 0;
}

int main(){
    freopen("bzoj3620.in","r",stdin);
    scanf("%s %d",str,&k);n=strlen(str);
    int res1=0,res2=0;
    for(int i=0;i<n;i++){
    	res1=(res1*59+str[i])%1923717;
    	res2=(res2*61+str[i])%2142147;
    	hash1[i]=res1,hash2[i]=res2;
    }
    mul1[0]=mul2[0]=1;
    for(int i=1;i<=n;i++){
    	mul1[i]=(mul1[i-1]*59)%1923717;
    	mul2[i]=(mul2[i-1]*61)%2142147;
    }
    int ans=0;
    for(int i=0;i<n;i++)
    	for(int j=i+1;j<n;j++)
    		ans+=solve(i,j);
    printf("%d",ans);
    return 0;
}