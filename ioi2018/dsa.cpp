#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;

//f[k][d]表示从k开始长度为d的最早结束位置
//popback时反向更新（可在结尾用set存）

int n,m,q,a[MAXN],s[MAXN];
int f[MAXN],maxlen,cnt;

void update(int x){
	if(x>=maxlen){
		if(x==maxlen) cnt++;
		else maxlen=x,cnt=1;
	}
}

void premake(){
	for(int i=n;i>=1;i--){
		f[i]=1;
		for(int j=i+1;j<=n;j++)
			if(!(a[j]%a[i]))
				f[i]=max(f[i],f[j]+1);
	}
	for(int i=1;i<=n;i++)
		update(f[i]);
	cout<<maxlen<<' '<<cnt<<endl;
}

void addleft(int x){
	for(int i=n;i>1;i--)
		f[i]=f[i-1],a[i]=a[i-1];
	a[1]=x,f[1]=1;
	for(int i=2;i<=n;i++)
		if(!(a[i]%a[1]))
			f[1]=max(f[1],f[i]+1);
	update(f[1]);
	cout<<maxlen<<' '<<cnt<<endl;
}

void addright(int x){
	int top=0;
	f[n]=1,a[n]=x;
	s[++top]=n;
	for(int i=n-1;i>=1;i--)
		for(int j=top;j;j--)
			if(!(a[s[j]]%a[i])){
				f[i]=max(f[i],f[s[j]]+1);
				break;
			}
	maxlen=0,cnt=0;
	for(int i=1;i<=n;i++)
		update(f[i]);
	cout<<maxlen<<' '<<cnt<<endl;
}

void delleft(){
	int p=f[1];n--;
	for(int i=1;i<=n;i++)
		f[i]=f[i+1],a[i]=a[i+1];
	if(p==maxlen){
		cnt--;
		if(!cnt){
			maxlen=0;
			for(int i=1;i<=n;i++)
				update(f[i]);
		}
	}
	cout<<maxlen<<' '<<cnt<<endl;
}
void delright(){
	n--;maxlen=0,cnt=0;
	premake();
}

void solve(){
	int type,x;
	scanf("%d",&type);
	switch (type){
		case 0:
			scanf("%d",&x),n++;
			addleft(x);
			break;
		case 1:
			scanf("%d",&x),n++;
			addright(x);
			break;
		case 2:
			delleft();
			break;
		case 3:
			delright();
	}
}

int main(){
    freopen("dsa.in","r",stdin);
    freopen("dsa.out","w",stdout);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
    	scanf("%d",&a[i]);
    premake();
    while(q--)
    	solve();
    return 0;
}