#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1010
#define MAXM 1000010

#define ii pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;


int ans[MAXN],cnt,a[MAXN],book[MAXM],book1[MAXM],n;

int gcd(int x,int y){
	if(!x) return y;
	if(!y) return x;
	return gcd(y,x%y);
}

int main(){
	freopen("input","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		book1[a[i]]=1;
	}
	if(n==1){
		cout<<a[1];
		return 0;
	}
	book[a[n]]=1,book[a[n-1]]=1,book[gcd(a[n-1],a[n])]=1;
	ans[++cnt]=a[n],ans[++cnt]=a[n-1];
	for(int i=n-2;i>=1;i--){
		if(!book[a[i]]){
			int G=a[i];
			for(int j=1;j<=cnt;j++){
				G=gcd(G,ans[j]);
				book[G]=1;
			}
			ans[++cnt]=a[i],book[a[i]]=1;
		}
		else{
			bool flag=true;
			int G=a[i];
			for(int j=1;j<=cnt;j++){
				G=gcd(G,ans[j]);
				if(!book1[G]){
					flag=false;break;
				}
			}
			if(flag){
				int G=a[i];
				for(int j=1;j<=cnt;j++){
					G=gcd(G,ans[j]);
					book[G]=1;
				}
				ans[++cnt]=a[i],book[a[i]]=1;
			}
		}
	}
	for(int i=1;i<=1e6;i++)
		if(book[i]!=book1[i]){
			cout<<-1;
			return 0;
		}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
		cout<<ans[i]<<' ';
	return 0;
}