#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;
const ll MOD=1000000007;

int T,n;
int a[110][110],num[110];
ll f[110][2010];

void read(int ID){
    char ch='_';
    while(ch!='\n'){
        int x=0;ch=getchar();
        while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
        num[x]++;a[x][num[x]]=ID;
    }
}
 
int main(){
    freopen("shirt.in","r",stdin);
    freopen("shirt.out","w",stdout);
    scanf("%d\n",&T);
    while(T--){
        memset(a,0,sizeof(a));
        scanf("%d\n",&n);
        for(int i=1;i<=n;i++)read(i);
        memset(f,0,sizeof(f));f[0][0]=1;
        for(int i=1;i<=100;i++)
            for(int j=0;j<(1<<n);j++){
                f[i][j]=f[i-1][j];
                for(int k=1;k<=num[i];k++)if((1<<(a[i][k]-1))&j)
                    f[i][j]=(f[i][j]+f[i-1][j-(1<<(a[i][k]-1))])%MOD;
            }
        cout<<f[100][(1<<n)-1]<<endl;
    }
    return 0;
}
