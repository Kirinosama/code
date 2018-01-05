#include<iostream>  
#include<cstdio>  
#include<cstring>  
#include<queue>  
#include<algorithm>  
#include<vector>  
using namespace std;  
typedef long long ll;  
const ll inf=1LL<<50;  
#define rep(i,l,r) for(int i=l;i<=r;i++)  
#define per(i,r,l) for(int i=r;i>=l;i--)  
#define mmt(a,v) memset(a,v,sizeof(a))  
#define tra(i,u) for(int i=head[u];i;i=e[i].next)  
const int N=1000+5;  
const int M=12000+5;  
struct Edge{int to,next,v;}e[N*N];  
int head[M],cnt;  
void ins(int u,int v,int w){e[++cnt]=(Edge){v,head[u],w};head[u]=cnt;}  
void insert(int u,int v,int w){ins(u,v,w);ins(v,u,w);}  
ll d[M];  
bool inq[M];  
void spfa(int s){  
    memset(d,0x3f,sizeof(d));queue<int>q;q.push(s);d[s]=0;  
    while(!q.empty()){  
        int u=q.front();q.pop();inq[u]=0;  
        tra(i,u){  
            int v=e[i].to;  
            if(d[v]>d[u]+e[i].v){  
                d[v]=d[u]+e[i].v;  
                if(!inq[v])inq[v]=1,q.push(v);  
            }  
        }  
    }  
}  
struct point{  
    int x,y;  
    point(){}  
    point(int x,int y):x(x),y(y){}  
    void print(){printf("%d %d\n",x,y);}  
    bool operator == (const point &p)const{  
        return x==p.x&&y==p.y;  
    }  
}p[M];  
struct col{  
    int d,u,x;  
    vector<int>s;  
    col(){}  
    col(int d,int u,int x):d(d),u(u),x(x){s.clear();}  
    bool operator < (const col &c)const{  
        return x<c.x;  
    }  
}c[N<<1];  
struct row{  
    int l,r,y;  
    vector<int>s;  
    row(){}  
    row(int l,int r,int y):l(l),r(r),y(y){s.clear();}  
    bool operator < (const row &x)const{  
        return y<x.y;  
    }  
}r[N<<1];  
bool cmp(int i,int j){  
    return p[i].x==p[j].x?p[i].y<p[j].y:p[i].x<p[j].x;  
}  
int iabs(int x){return max(x,-x);}  
int dist(point p1,point p2){return iabs(p1.x-p2.x)+iabs(p1.y-p2.y);}  
int main(){  
    //freopen("a.in","r",stdin);  
    //freopen("a.out","w",stdout);  
    int T;scanf("%d",&T);  
    while(T--){  
        scanf("%d%d%d%d",&p[1].x,&p[1].y,&p[2].x,&p[2].y);  
        int n;scanf("%d",&n);  
        mmt(head,0);cnt=0;  
        int pn=2,sn=0;  
        c[++sn]=col(1,1,p[1].x);r[sn]=row(1,1,p[1].y);  
        c[++sn]=col(2,2,p[2].x);r[sn]=row(2,2,p[2].y);  
        rep(i,1,n){  
            static int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);  
            if(x1>x2)swap(x1,x2);if(y1>y2)swap(y1,y2);  
            p[++pn]=point(x1,y1);p[++pn]=point(x1,y2);  
            p[++pn]=point(x2,y1);p[++pn]=point(x2,y2);  
            c[++sn]=col(pn-3,pn-2,x1);r[sn]=row(pn-3,pn-1,y1);  
            c[++sn]=col(pn-1,pn,x2);r[sn]=row(pn-2,pn,y2);  
        }  
        sort(c+1,c+1+sn);sort(r+1,r+1+sn);  
        int sz=pn;  
        rep(i,1,sz){  
            static int j,id;  
            static point np;  
            j=upper_bound(c+1,c+1+sn,col(0,0,p[i].x))-c;  
            while(j<=sn){  
                if(p[c[j].d].y<=p[i].y&&p[i].y<=p[c[j].u].y){  
                    np=point(c[j].x,p[i].y);  
                    if(np==p[c[j].d])id=c[j].d;  
                    else if(np==p[c[j].u])id=c[j].u;  
                    else id=++pn,p[pn]=np;  
                    insert(i,id,dist(np,p[i]));  
                    c[j].s.push_back(id);  
                    break;  
                }  
                j++;  
            }  
            j=lower_bound(c+1,c+1+sn,col(0,0,p[i].x))-c-1;  
            while(j>=1){  
                if(p[c[j].d].y<=p[i].y&&p[i].y<=p[c[j].u].y){  
                    np=point(c[j].x,p[i].y);  
                    if(np==p[c[j].d])id=c[j].d;  
                    else if(np==p[c[j].u])id=c[j].u;  
                    else id=++pn,p[pn]=np;  
                    insert(i,id,dist(np,p[i]));  
                    c[j].s.push_back(id);  
                    break;  
                }  
                j--;  
            }  
            j=upper_bound(r+1,r+1+sn,row(0,0,p[i].y))-r;  
            while(j<=sn){  
                if(p[r[j].l].x<=p[i].x&&p[i].x<=p[r[j].r].x){  
                    np=point(p[i].x,r[j].y);  
                    if(np==p[r[j].l])id=r[j].l;  
                    else if(np==p[r[j].r])id=r[j].r;  
                    else id=++pn,p[pn]=np;  
                    insert(i,id,dist(np,p[i]));  
                    r[j].s.push_back(id);  
                    break;  
                }  
                j++;  
            }  
            j=lower_bound(r+1,r+1+sn,row(0,0,p[i].y))-r-1;  
            while(j>=1){  
                if(p[r[j].l].x<=p[i].x&&p[i].x<=p[r[j].r].x){  
                    np=point(p[i].x,r[j].y);  
                    if(np==p[r[j].l])id=r[j].l;  
                    else if(np==p[r[j].r])id=r[j].r;  
                    else id=++pn,p[pn]=np;  
                    insert(i,id,dist(np,p[i]));  
                    r[j].s.push_back(id);  
                    break;  
                }  
                j--;  
            }  
        }  
        rep(i,1,sn){  
            sort(c[i].s.begin(),c[i].s.end(),cmp);  
            sort(r[i].s.begin(),r[i].s.end(),cmp);  
            rep(j,1,(int)c[i].s.size()-1)  
            insert(c[i].s[j-1],c[i].s[j],dist(p[c[i].s[j-1]],p[c[i].s[j]]));  
            rep(j,1,(int)r[i].s.size()-1)  
            insert(r[i].s[j-1],r[i].s[j],dist(p[r[i].s[j-1]],p[r[i].s[j]]));  
        }  
        spfa(1);  
        if(d[2]>=inf)puts("No Path");  
        else printf("%lld\n",d[2]);  
    }  
    return 0;  
}  