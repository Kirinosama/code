#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n,m,a[20],b[20],ans;
int book1[20],book2[20],x;

int main()
{
	freopen("input","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",&x),book1[x]=1;
	for(int i=1;i<=m;i++) scanf("%d",&x),book2[x]=1;
	for(int i=0;i<=99;i++){
		if(i>=10){
			if(book1[i%10] || book1[i/10]){
				if(book2[i%10] || book2[i/10]){
					cout<<i;return 0;
				}
			}
		}
		else if(book1[i] && book2[i]){
			cout<<i;return 0;
		}
	}
	return 0;
}