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
#ifdef WIN32   
#define OT "%I64d"
#else
#define OT "%lld"
#endif
using namespace std;
typedef long long LL;
const int MAXN = 1000011;
const int inf = (1<<30);
int n,m;
int nowD;
int root;
int ans;
int ql,qr;

struct node{
    int Min[2],Max[2];
    int d[2];
    int l,r;
}t[MAXN*2];

inline int getint()
{
       int w=0,q=0;
       char c=getchar();
       while((c<'0' || c>'9') && c!='-') c=getchar();
       if (c=='-')  q=1, c=getchar();
       while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
       return q ? -w : w;
}

inline bool cmp(node q,node qq){ 
    if(q.d[nowD]==qq.d[nowD]) return q.d[!nowD]<qq.d[!nowD]; 
    return q.d[nowD]<qq.d[nowD];
}

inline void kd_updata(int now){
    if(t[now].l) {
    if(t[t[now].l].Max[0]>t[now].Max[0]) t[now].Max[0]=t[t[now].l].Max[0];
    if(t[t[now].l].Max[1]>t[now].Max[1]) t[now].Max[1]=t[t[now].l].Max[1];
    if(t[t[now].l].Min[0]<t[now].Min[0]) t[now].Min[0]=t[t[now].l].Min[0];
    if(t[t[now].l].Min[1]<t[now].Min[1]) t[now].Min[1]=t[t[now].l].Min[1];
    }
    if(t[now].r) {
    if(t[t[now].r].Max[0]>t[now].Max[0]) t[now].Max[0]=t[t[now].r].Max[0];
    if(t[t[now].r].Max[1]>t[now].Max[1]) t[now].Max[1]=t[t[now].r].Max[1];
    if(t[t[now].r].Min[0]<t[now].Min[0]) t[now].Min[0]=t[t[now].r].Min[0];
    if(t[t[now].r].Min[1]<t[now].Min[1]) t[now].Min[1]=t[t[now].r].Min[1];
    }
}

inline int kd_build(int l,int r,int D){
    int mid=(l+r)/2;
    nowD=D;
    nth_element(t+l+1,t+mid+1,t+r+1,cmp);

    if(l!=mid) t[mid].l=kd_build(l,mid-1,!D);
    if(r!=mid) t[mid].r=kd_build(mid+1,r,!D);
    t[mid].Max[0]=t[mid].Min[0]=t[mid].d[0];
    t[mid].Max[1]=t[mid].Min[1]=t[mid].d[1];
    kd_updata(mid);
    return mid;
}

inline int dist(int p){
    int dis=0;
    if(ql<t[p].Min[0]) dis+=t[p].Min[0]-ql;
    if(ql>t[p].Max[0]) dis+=ql-t[p].Max[0];
    if(qr<t[p].Min[1]) dis+=t[p].Min[1]-qr;
    if(qr>t[p].Max[1]) dis+=qr-t[p].Max[1];
    return dis;
}

inline void kd_query(int p){
    int dl,dr,d0;
    d0=abs(t[p].d[0]-ql)+abs(t[p].d[1]-qr);
    if(d0<ans) ans=d0;
    if(t[p].l) dl=dist(t[p].l); else dl=inf;
    if(t[p].r) dr=dist(t[p].r); else dr=inf;

    if(dl<dr) {
    if(dl<ans) kd_query(t[p].l);
    if(dr<ans) kd_query(t[p].r);
    }
    else{
    if(dr<ans) kd_query(t[p].r);
    if(dl<ans) kd_query(t[p].l);
    }
}

inline void kd_insert(int now){
    int p=root,D=0;
    while(true){
    if(t[now].Max[0]>t[p].Max[0]) t[p].Max[0]=t[now].Max[0];
    if(t[now].Max[1]>t[p].Max[1]) t[p].Max[1]=t[now].Max[1];
    if(t[now].Min[0]<t[p].Min[0]) t[p].Min[0]=t[now].Min[0];
    if(t[now].Min[1]<t[p].Min[1]) t[p].Min[1]=t[now].Min[1];

    if(t[now].d[D]>=t[p].d[D]) {
        if(!t[p].r){
        t[p].r=now;
        return;
        }
        else p=t[p].r;
    }
    else{
        if(!t[p].l) {
        t[p].l=now;
        return ;
        }
        else p=t[p].l;
    }

    D=!D;
    }
}

int main()
{
  freopen("bzoj2648","r",stdin);
  n=getint();m=getint();
  for(int i=1;i<=n;i++) t[i].d[0]=getint(),t[i].d[1]=getint();
  root=kd_build(1,n,0);
  int x,y,z;
  for(int i=1;i<=m;i++) {
      x=getint(); y=getint(); z=getint();
      if(x==1) {
      n++;
      t[n].Max[0]=t[n].Min[0]=t[n].d[0]=y; t[n].Max[1]=t[n].Min[1]=t[n].d[1]=z;
      kd_insert(n);
      }
      else{
      ans=inf;
      ql=y,qr=z;
      kd_query(root);
      printf("%d\n",ans);
      }
  }
  return 0;
}