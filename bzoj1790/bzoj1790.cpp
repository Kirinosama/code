#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

#define MAXN 200010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

struct square{
	int a,b,c,d;
	bool ok;
}s[MAXN];

vector <int> v;
map <int,int> mp;
int n,c[200010],ans,cnt;

inline bool cmp1(const square &a,const square &b){
	return a.a<b.a;
}

inline bool cmp2(const square &a,const square &b){
	return a.b<b.b;
}

inline int lowbit(int x){
	return x&-x;
}

inline void update(int x,int y){
	for(int i=x;i;i-=lowbit(i))
		c[i]=max(c[i],y);
}

inline int query(int x,int y){
	int sum=-1e9;
	for(int i=x;i<=200000;i+=lowbit(i))
		sum=max(sum,c[i]);
	return sum>=y;
}

inline void cdq(int l,int r){
	if(l==r){
		if(s[l].ok) ans++;
		return;
	}
	int mid=(l+r)>>1;
	sort(s+l,s+mid+1,cmp2);	sort(s+mid+1,s+r+1,cmp2);
	int p=l,q=mid+1;
	while(p<=mid && q<=r){
		if(s[p].b<=s[q].b){
			update(s[p].c,s[p].d);
			p++;
		}
		else{
			if(query(s[q].c,s[q].d)) s[q].ok=true;
			q++;
		}
	}
	while(p<=mid){
		update(s[p].c,s[p].d);
		p++;
	}
	while(q<=r){
		if(query(s[q].c,s[q].d)) s[q].ok=true;
		q++;
	}
	for(int i=l;i<=mid;i++)
		for(int j=s[i].c;j;j-=lowbit(j))
			c[j]=0;
	sort(s+l,s+mid+1,cmp1);	sort(s+mid+1,s+r+1,cmp1);
	cdq(l,mid),cdq(mid+1,r);
}

int main(){
    freopen("bzoj1790.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d %d %d %d",&s[i].a,&s[i].b,&s[i].c,&s[i].d);
    	v.push_back(s[i].c);
    }
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++)
    	if(!mp[v[i]]) mp[v[i]]=++cnt;
    for(int i=1;i<=n;i++) s[i].c=mp[s[i].c];
    sort(s+1,s+n+1,cmp1);
    cdq(1,n);
    printf("%d",ans);
    return 0;
}