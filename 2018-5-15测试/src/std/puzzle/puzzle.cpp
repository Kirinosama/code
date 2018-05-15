//详细题解见http://hzwer.com/4868.html
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char a[25];
int len,t,deep,v[25][25];
bool flag,b[25];
void pre(){
    for(int i=len;i;i--)
        if(a[i]=='0'){
            while(i--)b[i]=0;
            break;
        }
        else b[i]=1;
    for(int i=1;i<=len;i++)
        for(int j=i;j<=len;j++){
            v[i][j]=v[i][j-1]*10+a[j]-'0';
            v[i][j]=min(v[i][j],t+1);
        }
}
void dfs(int x,int k,int last,int mul,int sum){
    if(sum>t||flag||k>deep)return;
    if(x==len){
        if(sum+mul*v[last+1][len]==t)flag=1;
        return;
    }
    if(b[x-1]&&sum+mul>t)return;
    dfs(x+1,k+1,x,1,sum+mul*(v[last+1][x]));
    dfs(x+1,k+1,x,mul*(v[last+1][x]),sum);
    dfs(x+1,k,last,mul,sum);
}
void solve(){
    pre();
    int ans=-1;
    int l=0,r=len-1;
    while(l<=r){
        deep=(l+r)>>1;
        flag=0;
        dfs(1,0,0,1,0);
        if(flag)ans=deep,r=deep-1;
        else l=deep+1;
    }
    printf("%d\n",ans);
}
int main(){
    freopen("puzzle.in","r",stdin);
    freopen("puzzle.out","w",stdout);
    while(scanf("%s%d",a+1,&t)){
        if(t==-1)return 0;
        len=strlen(a+1);
        solve();
    }
    return 0;
}