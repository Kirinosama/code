#include<iostream>  
#include<algorithm>  
#include<cstdio>  
#include<cstring>  
#include<cstdlib>  
#include<cmath>
#include<queue>
using namespace std;  
       
const int ONE=100005;
   
int n,T;
int x,y;
int ne[ONE*2],first[ONE*2],go[ONE*2],tot,gcnt;
int Dep[ONE],Turnoff[ONE],Light;
int fat[ONE];
int f[ONE][21];
char ch[10];
   
int get()
{ 
        int res,Q=1;    char c;
        while( (c=getchar())<48 || c>57)
        if(c=='-')Q=-1;
        if(Q) res=c-48; 
        while((c=getchar())>=48 && c<=57) 
        res=res*10+c-48; 
        return res*Q; 
}
   
void Add(int u,int v)
{
        ne[++tot]=first[u];   first[u]=tot;   go[tot]=v;
        ne[++tot]=first[v];   first[v]=tot;   go[tot]=u;
}
   
   
struct Heap_deal
{
        priority_queue <int> heap,delet;
           
        void add(int x) {heap.push(x);}
        void del(int x) {delet.push(x);}
        void Pop()
        {
            while(!delet.empty() && heap.top()==delet.top())
            {
                heap.pop();
                delet.pop();
            }
            heap.pop();
        }
           
        int Top()
        {
            while(!delet.empty() && heap.top()==delet.top())
            {
                heap.pop();
                delet.pop();
            }
            return heap.top();
        }
           
        int SecondTop()
        {
            int jilu1=Top(); Pop();
            int jilu2=Top(); add(jilu1);
            return jilu2;
        }
           
        int Size()
        {
            return heap.size()-delet.size();
        }
}A,b[ONE],c[ONE];
   
void ADD(Heap_deal &a)
{
        if(a.Size()>=2)
        {
            int r1=a.Top();
            int r2=a.SecondTop();
            A.add( r1+r2 );
        }
}
   
void DEL(Heap_deal &a)
{
        if(a.Size()>=2)
        {
            int r1=a.Top();
            int r2=a.SecondTop();
            A.del( r1+r2 );
        }
}
  
namespace PartLCA
{
        void Deal_first(int u,int father)
        {
            Dep[u]=Dep[father]+1;
            for(int i=0;i<=19;i++)
            {
                f[u][i+1]=f[f[u][i]][i];
            }
                    
            for(int e=first[u];e;e=ne[e])
            {
                int v=go[e];
                if(v==father) continue;
                f[v][0]=u;
                Deal_first(v,u);
            }
        }
           
        int LCA(int x,int y)
        {
            if(Dep[x]<Dep[y]) swap(x,y);
            for(int i=20;i>=0;i--)
            {
                if(Dep[f[x][i]]>=Dep[y]) x=f[x][i];
                if(x==y) return x;
            }
              
            for(int i=20;i>=0;i--)
            {
                if(f[x][i]!=f[y][i])
                {
                    x=f[x][i];
                    y=f[y][i];
                }
            }
            return f[x][0];
        }
           
        int dist(int x,int y)
        {
            return Dep[x]+Dep[y]-2*Dep[LCA(x,y)];
        }
}
  
  
namespace PointF
{
        int Min,center,vis_center[ONE];
           
        struct power
        {
            int size,maxx;
        }S[ONE];
           
           
        void Getsize(int u,int father)
        {
            S[u].size=1;
            S[u].maxx=0;
            for(int e=first[u];e;e=ne[e])
            {
                int v=go[e];
                if(v==father || vis_center[v]) continue;
                Getsize(v,u);
                S[u].size+=S[v].size;
                S[u].maxx=max(S[u].maxx,S[v].size);
            }
        }
             
        void Getcenter(int u,int father,int total)
        {
            S[u].maxx=max(S[u].maxx,total-S[u].size);
            if(S[u].maxx<Min)
            {
                Min=S[u].maxx;
                center=u;
            }
               
            for(int e=first[u];e;e=ne[e])
            {
                int v=go[e];
                if(v==father || vis_center[v]) continue;
                Getcenter(v,u,total);
            }
        }
           
        void Add_c(int u,int father,int center)
        {
            c[center].add(PartLCA::dist(u,fat[center]));
            for(int e=first[u];e;e=ne[e])
            {
                int v=go[e];
                if(v==father || vis_center[v]) continue;
                Add_c(v,u,center);
            }
        }
           
           
        void New_tree(int u,int Last)
        {
            Min=n;
            Getsize(u,0);
            Getcenter(u,0,S[u].size);
            vis_center[center]=1;
               
            fat[center]=Last;
            if(Last!=0) Add_c(center,0,center);
            if(c[center].Size()) b[Last].add(c[center].Top());
               
            int root=center;
            for(int e=first[center];e;e=ne[e])
            {
                int v=go[e];
                if(vis_center[v]) continue;
                New_tree(v,root);
            }
        }
}
  
namespace Control
{
        void Turn_off(int x)
        {
            for(int i=x;fat[i];i=fat[i])
            {
                DEL(b[fat[i]]);
                if(c[i].Size()) b[fat[i]].del(c[i].Top());
                  
                c[i].del(PartLCA::dist(fat[i],x));
                       
                if(c[i].Size()) b[fat[i]].add(c[i].Top());
                ADD(b[fat[i]]);
            }
        }
           
        void Turn_on(int x)
        {
            for(int i=x;fat[i];i=fat[i])
            {
                DEL(b[fat[i]]);
                if(c[i].Size()) b[fat[i]].del(c[i].Top());
                  
                c[i].add(PartLCA::dist(fat[i],x));
                     
                if(c[i].Size()) b[fat[i]].add(c[i].Top());
                ADD(b[fat[i]]);
            }
        }
}
  
   
int main()
{
        freopen("bzoj1095.in","r",stdin);
        freopen("out2.out","w",stdout);
        n=get();
        Light=n;
        for(int i=1;i<=n;i++) Turnoff[i]=1;
        for(int i=1;i<n;i++)
        {
            x=get();    y=get();
            Add(x,y);
        }
           
        PartLCA::Deal_first(1,0);
        PointF::New_tree(1,0);
           
        for(int i=1;i<=n;i++) ADD(b[i]);
           
        T=get();
        while(T--)
        {
            scanf("%s",ch);
            if(ch[0]=='G')
            {
                if(Light==0) printf("-1");
                else if(Light==1) printf("0");
                else printf("%d",A.Top());
                printf("\n");
            }
               
            if(ch[0]=='C')
            {
                x=get();
                if(Turnoff[x])
                {
                    Turnoff[x]=0;
                    Light--;
                    Control::Turn_off(x);
                }
                else
                {
                    Turnoff[x]=1;
                    Light++;
                    Control::Turn_on(x);
                }
            }
        }
}