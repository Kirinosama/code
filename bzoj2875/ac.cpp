#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <complex>
using namespace std;
typedef long long LL;
LL m,a,c,X0,n,g;
struct Matrix{
    LL s[2][2];
}A,B,ini;
 
inline LL cheng(LL x,LL y){
    LL r=0;
    while(y>0) {
        if(y&1) r+=x,r%=m;
        x+=x; x%=m;
        y>>=1;
    }
    return r;
}
 
inline Matrix operator * (Matrix q,Matrix qq){
    Matrix tmp=ini;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int l=0;l<2;l++)
                tmp.s[i][j]+=cheng(q.s[i][l],qq.s[l][j]),tmp.s[i][j]%=m;
    return tmp;
}
 
inline LL getLL(){
    LL w=0,q=0; char c=getchar(); while((c<'0'||c>'9') && c!='-') c=getchar();
    if(c=='-') q=1,c=getchar(); while (c>='0'&&c<='9') w=w*10+c-'0',c=getchar(); return q?-w:w;
}
 
inline void fast_pow(Matrix a,LL y){
    B.s[0][0]=B.s[1][1]=1;
    while(y>0) {
        if(y&1) B=B*a;
        a=a*a;
        y>>=1;
    }
}
 
inline void work(){
    m=getLL(); a=getLL(); c=getLL(); X0=getLL(); n=getLL(); g=getLL();
    A.s[0][0]=a; A.s[0][1]=0; A.s[1][0]=c; A.s[1][1]=1;
    fast_pow(A,n);
    printf("%lld",((cheng(X0,B.s[0][0])+B.s[1][0])%m)%g);
}
 
int main()
{
    freopen("bzoj2875.in","r",stdin);
    work();
    return 0;
}