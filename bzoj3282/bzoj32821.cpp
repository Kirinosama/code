#include<cstdio>  
#include<cstring>  
#include<algorithm>  
#define ls c[x][0]  
#define rs c[x][1]  
using namespace std;  
const int maxn=300010;  
int n,m;  
   
struct LCT{  
    int c[maxn][2],fa[maxn],rev[maxn],sum[maxn],val[maxn];  
    bool isroot(int x){return (c[fa[x]][0]!=x)&&(c[fa[x]][1]!=x);}  
    int which(int x){return c[fa[x]][1]==x;}  
    void update(int x){sum[x]=sum[c[x][0]]^sum[c[x][1]]^val[x];}  
    void flip(int x){swap(c[x][0],c[x][1]),rev[x]^=1;}  
    void down(int x){if (rev[x]) flip(c[x][0]),flip(c[x][1]),rev[x]=0;}  
    void relax(int x){if (!isroot(x)) relax(fa[x]);down(x);}  
    void rotate(int x){  
        int y=fa[x],z=fa[y],nx=which(x),ny=which(y);  
        fa[c[x][!nx]]=y,c[y][nx]=c[x][!nx];  
        fa[x]=z;if (!isroot(y)) c[z][ny]=x;  
        fa[y]=x,c[x][!nx]=y;update(y);  
    }  
    void splay(int x){  
        relax(x);  
        while (!isroot(x)){  
            if (isroot(fa[x])) rotate(x);  
            else if (which(x)==which(fa[x])) rotate(fa[x]),rotate(x);  
            else rotate(x),rotate(x);  
        }  
        update(x);  
    }  
    void access(int x){for (int p=0;x;x=fa[x]) splay(x),fa[c[x][1]=p]=x,update(x),p=x;}  
    void makeroot(int x){access(x),splay(x),flip(x);}  
    void modify(int x,int v){val[x]=v,splay(x);}  
    int findroot(int x){access(x),splay(x);for (;c[x][0];x=c[x][0]);return x;}  
    void link(int a,int b){makeroot(a),fa[a]=b;}  
    void cut(int a,int b){makeroot(a),access(b),splay(b);if (c[b][0]==a) c[b][0]=fa[a]=0;}  
    int query(int a,int b){makeroot(a),access(b),splay(b);return sum[b];}  
}T;  
   
int main(){
	freopen("bzoj3282.in","r",stdin);  
    scanf("%d%d",&n,&m);  
    for (int i=1,a;i<=n;i++) scanf("%d",&a),T.modify(i,a);  
    for (int i=1,op,a,b;i<=m;i++){  
        scanf("%d%d%d",&op,&a,&b);  
        if (op==0) printf("%d\n",T.query(a,b));  
        else if (op==1){if (!(T.findroot(a)==T.findroot(b))) T.link(a,b);}  
        else if (op==2) T.cut(a,b);  
        else T.modify(a,b);  
    }  
    return 0;  
}  