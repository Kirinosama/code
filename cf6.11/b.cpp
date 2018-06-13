#include <bits/stdc++.h>
using namespace std;

int n,m;
bool flag;
char a[2010];

int main(){
	freopen("input","r",stdin);
	scanf("%d %d\n",&n,&m);
	for(int i=1;i<=n;i++)scanf("%c",&a[i]);
	for(int i=1;i<=n;i++){
		if(i-m>=1){
			if(a[i]+a[i-m]==('1'+'0')){
				flag=true;break;
			}
			if(a[i]=='.' || a[i-m]=='.'){
				if(a[i]=='.'){
					if(a[i-m]=='.') a[i]='1',a[i-m]='0';
					else a[i]='1'+'0'-a[i-m];
					flag=true;
				}else{
					a[i-m]='0'+'1'-a[i];
					flag=true;
				}
				break;
			}
		}
	}
	if(flag){
		for(int i=1;i<=n;i++){
			printf("%c",a[i]=='.'?'1':a[i]);
		}
	}else cout<<"No";
	return 0;
}

