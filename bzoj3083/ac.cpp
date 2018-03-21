#include <cstdio>  
#include <cstring>  
#include <iostream>  
#include <algorithm>  
#define MAX 100010  
#define INF 0x3f3f3f3f  
#define LEFT (pos << 1)  
#define RIGHT (pos << 1|1)  
using namespace std;  
  
struct SegmentTree{  
    int _min;  
    bool v;  
}tree[MAX << 2];  
  
int points,asks;  
int head[MAX],total;  
int ne[MAX << 1],aim[MAX << 1];  
  
int deep[MAX],father[MAX],size[MAX],son[MAX];  
int pos[MAX],top[MAX],cnt;  
  
int capital;  
  
inline void Add(int x,int y)  
{  
    ne[++total] = head[x];  
    aim[total] = y;  
    head[x] = total;  
}  
  
void PreDFS(int x,int last)  
{  
    deep[x] = deep[last] + 1;  
    father[x] = last;  
    size[x] = 1;  
    for(int i = head[x]; i; i = ne[i]) {  
        if(aim[i] == last)  continue;  
        PreDFS(aim[i],x);  
        size[x] += size[aim[i]];  
        if(size[aim[i]] > size[son[x]])  
            son[x] = aim[i];  
    }  
}  
  
void DFS(int x,int last,int _top)  
{  
    pos[x] = ++cnt;  
    top[x] = _top;  
    if(son[x])  DFS(son[x],x,_top);  
    for(int i = head[x]; i; i = ne[i]) {  
        if(aim[i] == last || aim[i] == son[x])  continue;  
        DFS(aim[i],x,aim[i]);  
    }  
}  
  
inline bool InSonTree(int x,int f)  
{  
    if(pos[x] < pos[f] || pos[x] > pos[f] + size[f] - 1)  return false;  
    return true;  
}  
  
inline void PushDown(int pos)  
{  
    if(tree[pos].v) {  
        tree[LEFT]._min = tree[pos]._min;  
        tree[RIGHT]._min = tree[pos]._min;  
        tree[LEFT].v = tree[RIGHT].v = true;  
        tree[pos].v = false;  
    }  
}  
  
void Modify(int l,int r,int x,int y,int pos,int c)  
{  
    if(l == x && y == r) {  
        tree[pos]._min = c;  
        tree[pos].v = true;  
        return ;  
    }  
    PushDown(pos);  
    int mid = (l + r) >> 1;  
    if(y <= mid) Modify(l,mid,x,y,LEFT,c);  
    else if(x > mid) Modify(mid + 1,r,x,y,RIGHT,c);  
    else {  
        Modify(l,mid,x,mid,LEFT,c);  
        Modify(mid + 1,r,mid + 1,y,RIGHT,c);  
    }  
    tree[pos]._min = min(tree[LEFT]._min,tree[RIGHT]._min);  
}  
  
inline void Modify(int x,int y,int c)  
{  
    while(top[x] != top[y]) {  
        if(deep[top[x]] < deep[top[y]])  
            swap(x,y);  
        Modify(1,cnt,pos[top[x]],pos[x],1,c);  
        x = father[top[x]];  
    }  
    if(deep[x] < deep[y])    swap(x,y);  
    Modify(1,cnt,pos[y],pos[x],1,c);  
}  
  
int Ask(int l,int r,int x,int y,int pos)  
{  
    if(l == x && y == r)    return tree[pos]._min;  
    PushDown(pos);  
    int mid = (l + r) >> 1;  
    if(y <= mid) return Ask(l,mid,x,y,LEFT);  
    if(x > mid)      return Ask(mid + 1,r,x,y,RIGHT);  
    int left = Ask(l,mid,x,mid,LEFT);  
    int right = Ask(mid + 1,r,mid + 1,y,RIGHT);  
    return min(left,right);  
}  
  
int main()  
{  
    cin >> points >> asks;  
    for(int x,y,i = 1; i < points; ++i) {  
        scanf("%d%d",&x,&y);  
        Add(x,y),Add(y,x);  
    }  
    PreDFS(1,0);  
    DFS(1,0,1);  
    for(int x,i = 1; i <= cnt; ++i) {  
        scanf("%d",&x);  
        Modify(1,cnt,pos[i],pos[i],1,x);  
    }  
    cin >> capital;  
    for(int flag,i = 1; i <= asks; ++i) {  
        scanf("%d",&flag);  
        int x,y,z;  
        if(flag == 1)   scanf("%d",&capital);  
        if(flag == 2) {  
            scanf("%d%d%d",&x,&y,&z);  
            Modify(x,y,z);  
        }  
        if(flag == 3) {  
            scanf("%d",&x);  
            if(x == capital)  
                printf("%d\n",tree[1]._min);  
            else {  
                int son = 0;  
                for(int j = head[x]; j && !son; j = ne[j]) {  
                    if(aim[j] == father[x]) continue;  
                    if(InSonTree(capital,aim[j]))  
                        son = aim[j];  
                }  
                if(son) {  
                    int left = Ask(1,cnt,1,pos[son] - 1,1);  
                    int right = INF;  
                    if(pos[son] + size[son] <= cnt)  
                        right = Ask(1,cnt,pos[son] + size[son],cnt,1);  
                    printf("%d\n",min(min(left,right),Ask(1,cnt,pos[x],pos[x],1)));  
                }  
                else    printf("%d\n",Ask(1,cnt,pos[x],pos[x] + size[x] - 1,1));  
            }  
        }  
    }  
    return 0;  
}  