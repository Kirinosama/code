#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define LL long long
const int maxn=100010,p=100003;
vector<int> v[maxn];
vector<int>::iterator it;
int a[maxn],f[maxn],g[maxn],inv[maxn],prm[maxn],
n,m,k,tot;
int pow(int base,int k)
{
    int ret=1;
    for (;k;k>>=1,base=(LL)base*base%p)
        if (k&1) ret=(LL)ret*base%p;
    return ret;
}
int main()
{
    int ans;
    scanf("%d%d",&n,&k);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    for (int i=1;i<=n;i++)
    {
        if (!inv[i])
        {
            inv[i]=pow(i,p-2);
            prm[++tot]=i;
        }
        for (int j=1;j<=tot&&(LL)i*prm[j]<=n;j++)
        {
            inv[i*prm[j]]=inv[i]*inv[prm[j]];
            if (i%prm[j]==0) break;
        }
    }
    for (int i=1;i<=n;i++)
        for (int j=i;j<=n;j+=i)
            v[j].push_back(i);
    for (int i=n;i;i--)
        if (a[i])
        {
            m++;
            for (it=v[i].begin();it!=v[i].end();++it) a[*it]^=1;
        }
    g[n]=1;
    for (int i=1;i<=k;i++) g[i]=1;
    for (int i=n-1;i>k;i--) g[i]=((LL)g[i+1]*(n-i)%p*inv[i]+(LL)n*inv[i])%p;
    for (int i=1;i<=k;i++) f[i]=i;
    for (int i=k+1;i<=m;i++) f[i]=f[i-1]+g[i];
    ans=f[m];
    for (int i=1;i<=n;i++) ans=(LL)ans*i%p;
    printf("%d\n",ans);
}