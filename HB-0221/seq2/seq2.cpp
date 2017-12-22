#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010

struct node{
	int l,r,k;
}p[MAXN];

int book[MAXN],n,ans;

bool cmp(const node &a,const node &b){
	if(a.r==b.r)
		return a.l>b.l;
	return a.r<b.r;
}

void solve(int cur){
	int cnt=0;
	int l=p[cur].l,r=p[cur].r;
	for(int i=l;i<=r;i++)
		if(book[i]) cnt++;
	if(cnt>=p[cur].k) return;
	for(int i=r;i>=l && cnt<p[cur].k;i--){
		if(!book[i]){
			book[i]=1,cnt++;
			ans++;
		}
	}
}

int main(){
    freopen("seq2.in","r",stdin);
    freopen("seq2.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
    	scanf("%d %d %d",&p[i].l,&p[i].r,&p[i].k);
    }
    sort(p+1,p+1+n,cmp);
    for(int i=1;i<=n;i++) solve(i);
    cout<<ans;
    return 0;
}