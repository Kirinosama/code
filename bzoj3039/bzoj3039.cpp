#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

#define MAXN 1010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

int n,m,h[MAXN][MAXN],ans;
int l[MAXN][MAXN],r[MAXN][MAXN];
char a[MAXN][MAXN];

void premake(int x){
    int *A=h[x];
    int *L=l[x],*R=r[x];
    stack <int> s;
    for(int i=1;i<=m;i++){
        while(!s.empty() && A[s.top()]>=A[i])s.pop();
        if(s.empty())L[i]=0;
        else L[i]=s.top();
        s.push(i);
    }
    while(!s.empty())s.pop();
    for(int i=m;i>=1;i--){
        while(!s.empty() && A[s.top()]>=A[i])s.pop();
        if(s.empty())R[i]=m+1;
        else R[i]=s.top();
        s.push(i);
    }
    for(int i=1;i<=m;i++)ans=max(ans,3*A[i]*(R[i]-L[i]-1));
}

int main(){
    freopen("bzoj3039.in","r",stdin);
    cin>>n>>m;char ch;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ch=getchar();
            while(ch!='F' && ch!='R') ch=getchar();
            a[i][j]=ch;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            h[i][j]=a[i][j]=='F'?h[i-1][j]+1:0;
    for(int i=1;i<=n;i++)premake(i);
    cout<<ans;
    return 0;
}
