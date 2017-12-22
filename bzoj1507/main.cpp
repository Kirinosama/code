#include<iostream>      
#include<cstdio>      
#include<cstring>      
#include<algorithm>      
#include<queue>      
using namespace std;    
const int N=1<<25;    
const int blocksize=20000;    
const int blocknum=N/blocksize*3;      
int n,m;      
int cur;      
char str[N+110],s[100];      
queue<int> q;      
struct node       
{      
    char data[blocksize+111];      
    int len,next;  
}; node a[blocknum+1000];      
int newnode()    
{    
    int temp=q.front(); q.pop(); return temp;    
}    
void delnode(int t)
{    
    q.push(t);    
}    
void find(int &pos,int &now)
{    
    for (now=0;a[now].next!=-1&&pos>a[now].len;now=a[now].next)  pos-=a[now].len;    
}    
void fillnode(int pos,int n,char data[],int next)    
{    
    a[pos].next=next;   a[pos].len=n;    
    memcpy(a[pos].data,data,n);   
}    
void split(int pos,int p) 
{    
    if (a[pos].len==p) return;    
    int t=newnode(); 
    fillnode(t,a[pos].len-p,a[pos].data+p,a[pos].next);    
    a[pos].next=t;    a[pos].len=p;    
}    
void maintain(int pos) 
{    
    int t;    
    for (;pos!=-1;pos=a[pos].next){    
      for(t=a[pos].next;t!=-1&&a[pos].len+a[t].len<blocksize;t=a[t].next)    
      {    
        memcpy(a[pos].data+a[pos].len,a[t].data,a[t].len);    
        a[pos].len+=a[t].len; a[pos].next=a[t].next; delnode(t);    
      }     
    }    
}    
void insert(int pos,int n)    
{    
    int now,i,t;    
    find(pos,now); split(now,pos);
    for (i=0;i+blocksize<=n;i+=blocksize){    
        t=newnode();    
        fillnode(t,blocksize,str+i,a[now].next);    
        a[now].next=t;    
        now=t;    
    }    
    if (i<n)   
    {    
        t=newnode();    
        fillnode(t,n-i,str+i,a[now].next);    
        a[now].next=t;    
    }    
    maintain(now);    
}    
void del(int pos,int n)    
{    
    int i,now,t;    
    find(pos,now); split(now,pos); 
    for (i=a[now].next;i!=-1&&n>a[i].len;i=a[i].next)  n-=a[i].len;    
    split(i,n); i=a[i].next;    
    for(t=a[now].next;t!=i;t=a[now].next) a[now].next=a[t].next,delnode(t);    
    maintain(now);    
}    
void get(int pos,int n)  
{    
    int i,now,t;    
    find(pos,now); i=min(n,a[now].len-pos);    
    memcpy(str,a[now].data+pos,i);    
    for (t=a[now].next;t!=-1&&i+a[t].len<=n;t=a[t].next)    
     {    
        memcpy(str+i,a[t].data,a[t].len);    
        i+=a[t].len;    
     }    
     if (i<n&&t!=-1)  memcpy(str+i,a[t].data,n-i);    
     str[n]=0;    
}    
void init()    
{      
    for (int i=1;i<=blocknum;i++)  q.push(i);      
    a[0].len=0; a[0].next=-1;      
}     
void read(int m)
{    
    int i=-1;    
    while (i<m-1)    
    {    
        i++;    
        char c=getchar();    
        str[i]=c;    
        if (c<32||c>126) i--;    
    }    
}     
int main()      
{        
    init();      
    scanf("%d",&n);      
    for (int i=1;i<=n;i++)      
    {      
        scanf("%s",s);      
        if (s[0]=='M')  scanf("%d",&cur); 
        if (s[0]=='I') {  
            scanf("%d",&m);      
            read(m);     
            insert(cur,m);      
        }      
        if (s[0]=='P') cur--;    
        if (s[0]=='N') cur++;    
        if (s[0]=='D'){    
            scanf("%d",&m);      
            del(cur,m);      
        }      
        if (s[0]=='G'){       
            scanf("%d",&m);      
            get(cur,m);     
            puts(str);     
        }      
    }      
}      