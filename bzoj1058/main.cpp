#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <map>
#include <queue>
using namespace std;

#define inf 1000000000
int n,m;
int st[600006],ed[600006];
multiset<int> a,b;
map<int,int> mp;
priority_queue<int,vector<int>,greater<int> > q;

void insert(int x)
{
    mp[x]++;
    if(mp[x]==1)a.insert(x);
}
void push(int x)
{
    int l=*--b.lower_bound(x),r=*b.lower_bound(x);
    q.push(min(x-l,r-x));
    b.insert(x);
}
int main()
{
   	scanf("%d %d",&n,&m);

    b.insert(inf);
    b.insert(-inf);
    
    for(int i=1;i<=n;i++)
    {
    	int x;
        scanf("%d",&x);
        ed[i]=st[i]=x;
        push(x);
    }

    for(int i=2;i<=n;i++)
    	insert(abs(st[i]-st[i-1]));
    
    char ch[12];
    int p,x,t;
    
    for(int i=1;i<=m;i++)
    {
        scanf("%s",ch);
        if(ch[0]=='I')
        {
            scanf("%d %d",&p,&x);
            if(p!=n)
			{
				t=abs(ed[p]-st[p+1]);
				mp[t]--;
				if(!mp[t])a.erase(t);
			}
            insert(abs(ed[p]-x));
            insert(abs(x-st[p+1]));
            ed[p]=x;
            push(x);
        }
        else if(ch[4]=='S')
        	printf("%d\n",q.top());
        else 
        	printf("%d\n",*a.begin());
    }
    return 0;
}