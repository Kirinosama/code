#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 30010
#define MAXM 60010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct edge{
    int x,y;
}E[MAXM];

struct complex{
    double real,imag;
    complex(){real=imag=0.0;}
    complex(double x,double y){real=x,imag=y;}
    complex operator + (const complex &a)const{
        return complex(real+a.real,imag+a.imag);
    }
    complex operator - (const complex &a)const{
        return complex(real-a.real,imag-a.imag);
    }
    complex operator * (const complex &a)const{
        return complex(real*a.real-imag*a.imag,real*a.imag+imag*a.real);
    }
    void operator /= (double x){
        real/=x,imag/=x;
    }
}A[MAXN*8],B[MAXN*8],u[MAXN*8];

int last[MAXN],ne[MAXM],edge_cnt;
int n,tot,rt;
int cnt[MAXN];
int vis[MAXN],size[MAXN],G[MAXN];
double ans;

void add_edge(int x,int y){
    E[++edge_cnt]=(edge){x,y};
    ne[edge_cnt]=last[x];
    last[x]=edge_cnt;
}

void dfs1(int x,int f){
    tot++;
    for(int i=last[x];i;i=ne[i]){
        if(E[i].y==f || vis[E[i].y])continue;
        dfs1(E[i].y,x);
    }
}

void dfs2(int x,int f){
    size[x]=1;G[x]=0;
    for(int i=last[x];i;i=ne[i]){
        if(E[i].y==f || vis[E[i].y]) continue;
        dfs2(E[i].y,x);size[x]+=size[E[i].y];
        G[x]=max(G[x],size[E[i].y]);
    }
    G[x]=max(G[x],tot-size[x]);
    if(G[x]<G[rt]) rt=x;
}

void getroot(int x,int f){
    tot=0;
    dfs1(x,f);
    dfs2(x,f);
}

void dfs3(int x,int f,int dist,int k){
    A[dist].real+=k;
    for(int i=last[x];i;i=ne[i]){
        if(E[i].y==f || vis[E[i].y])continue;
        dfs3(E[i].y,x,dist+1,k);
    }
}

int lowbit(int x){
    return x&-x;
}

int bit_reverse(int x,int Size){
    int res=0;
    for(int i=x;i;i-=lowbit(i)){
        res|=Size/2/lowbit(i);
    }
    return res;
}

void fft(complex *A,int Size,bool flag){
    for(int i=0;i<Size;i++){
        int j=bit_reverse(i,Size);
        if(i>j)swap(A[i],A[j]);
    }
    for(int i=0;i<Size;i++){
        double ang=(flag?2.0:-2.0)*M_PI*(double)i/(double)Size;
        u[i]=complex(cos(ang),sin(ang));
    }
    for(int step=2;step<=Size;step<<=1){
        int gap=step>>1,add_gap=Size/step;
        for(int i=0;i<Size;i+=step){
            for(int j=i;j<i+gap;j++){
                int k1=(j-i)*add_gap;
                int k2=k1+gap*add_gap;
                complex new1=A[j]+A[j+gap]*u[k1];
                complex new2=A[j]+A[j+gap]*u[k2];
                A[j]=new1,A[j+gap]=new2;
            }
        }
    }
    if(!flag){
        for(int i=0;i<Size;i++)A[i]/=(double)Size;
    }
}

void cal(int k){
    int Size=1;
    while(Size<=2*n)Size<<=1;
    fft(A,Size,true);
    for(int i=0;i<=Size;i++)
        B[i]=A[i]*A[i];
    fft(B,Size,false);fft(A,Size,false);
    for(int i=0;i<=n;i++)cnt[i]+=llround(B[i].real)*k;
}

void work(int x){
    //printf("work on %d\n",x);
    //fflush(stdout);
    dfs3(x,x,0,1);
    cal(1);
    dfs3(x,x,0,-1);
    vis[x]=1;
    for(int i=last[x];i;i=ne[i])if(!vis[E[i].y]){
        dfs3(E[i].y,E[i].y,1,1);
        cal(-1);
        dfs3(E[i].y,E[i].y,1,-1);
    }
    for(int i=last[x];i;i=ne[i])if(!vis[E[i].y]){
        rt=0;getroot(E[i].y,E[i].y);
        work(rt);
    }
}

int main(){
    freopen("bzoj3451.in","r",stdin);
    cin>>n;
    for(int i=1;i<n;i++){
        int x,y;scanf("%d%d",&x,&y);x++,y++;
        add_edge(x,y);add_edge(y,x);
    }
    rt=0;G[0]=INF;
    getroot(1,1);work(rt);
    for(int i=0;i<=n;i++){
        ans+=(double)cnt[i]/(double)(i+1);
    }
    printf("%.4lf\n",ans);
    return 0;
}
