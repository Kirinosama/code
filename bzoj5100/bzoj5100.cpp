#include <bits/stdc++.h>
using namespace std;

#define bug(x) cout<<(#x)<<" "<<(x)<<endl
const int N=5e5+5;

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int n,cnt,tot,len=INT_MAX,mp[20000007];

struct Edge{
    int u,v,c;
}e[N];

struct node{
    int s,t,id,sum;
}a[N],tmp[N];

vector<node>b[N];
bool cmp2(node a,node b){
    return a.s<b.s;
}

int main(){
	freopen("bzoj5100.in","r",stdin);
    n=read();
    if(n==2)
        return printf("TAK\n1 2 1"),0;
    for(int i=1;i<=n-2;i++) a[i].s=read(),a[i].id=i+1;
    for(int i=1;i<=n-2;i++) a[i].t=read(),a[i].sum=a[i].s+a[i].t,len=min(len,a[i].sum);
    int zjq=abs(a[1].s-a[1].t),flag=0;
    if(zjq){
        for(int i=2;i<=n-2;i++) if(abs(a[i].t-a[i].s)!=zjq) flag=1;
        if(!flag) {
            printf("TAK\n1 %d %d\n",n,zjq);
            for(int i=1;i<=n-2;i++){
                if(a[i].s<a[i].t)  printf("1 %d %d\n",a[i].id,a[i].s);
                else printf("%d %d %d\n",n,a[i].id,a[i].t);
            } 
            return 0;
        }
    } 
    for(int i=1;i<=n-2;i++) if(a[i].sum==len) tmp[++cnt]=a[i];
    sort(tmp+1,tmp+cnt+1,cmp2);
    tmp[0].id=1,tmp[0].t=tmp[0].sum=len;
    tmp[++cnt].id=n,tmp[cnt].s=tmp[cnt].sum=len;
    for(int i=1;i<=cnt;i++) 
    	if(tmp[i].s==tmp[i-1].s) {
        return printf("NIE\n"),0;
    }
    for(int i=1;i<=cnt;i++)
        e[++tot].u=tmp[i-1].id,e[tot].v=tmp[i].id,e[tot].c=tmp[i].s-tmp[i-1].s;
    for(int i=0;i<=cnt;i++) mp[tmp[i].s]=i+1;
    for(int i=1;i<=n-2;i++){
        if(a[i].sum==len) continue;
        int r=a[i].s,c=r+a[i].t-len;
        r-=c/2;
        if(c&1)
            return printf("NIE\n"),0;
        else if(!mp[r])
            return printf("NIE\n"),0;
        else
            e[++tot].u=tmp[mp[r]-1].id,e[tot].v=a[i].id,e[tot].c=c/2;
    }
    printf("TAK\n");
    for(int i=1;i<=tot;i++) printf("%d %d %d\n",e[i].u,e[i].v,e[i].c);
    return 0;
}