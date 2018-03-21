#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define N 100000
using namespace std;
int sg[N+5],mex[N+5],n,x,ty,f,id,ans;
bool bz[N+5];
int get(int x) {
    if (x<f) return 0;
    if (bz[x]==1) return sg[x];bz[x]=1;
    for(int i=2;i<=x;i=x/(x/i)+1) fo(j,i,min(i+1,x)) 
    get(x/j),get(x/j+1);id++;
    for(int i=2;i<=x;i=x/(x/i)+1) fo(j,i,min(i+1,x)) {
        int nim=0;
        if (x%j%2) nim^=sg[x/j+1];
        if ((j-x%j)%2) nim^=sg[x/j];
        mex[nim]=id;
    }
    for(sg[x]=0;mex[sg[x]]==id;sg[x]++);
    return sg[x];
}
int main() {
    scanf("%d%d",&ty,&f);
    while (ty--){ 
        scanf("%d",&n);
        ans=0;
        fo(i,1,n) scanf("%d",&x),ans^=get(x);
        if (ans) printf("1");else printf("0");
        if (ty) printf(" ");
    }
}