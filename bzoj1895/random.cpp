#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("input","w",stdout);
	srand(time(0));
	int n=100000,m=100000;
	cout<<n<<endl;
	for(int i=1;i<=n;i++)printf("%d\n",rand()%1000+1);
	cout<<m<<endl;
	for(int i=1;i<=m;i++){
		int opt=rand()%6;
		int l=rand()%n+1,r=rand()%n+1;
		if(l>r) swap(l,r);
		if(opt==0){
			printf("ADD %d %d %d\n",l,r,rand()%1000);
		}else if(opt==1){
			printf("REVERSE %d %d\n",l,r);
		}else if(opt==2){
			printf("REVOLVE %d %d %d\n",l,r,rand()%1000+1);
		}else if(opt==3){
			printf("INSERT %d %d\n",l,rand()%1000+1),n++;
		}else if(opt==4){
			printf("DELETE %d\n",l),n--;
		}else{
			printf("MIN %d %d\n",l,r);
		}
	}
	return 0;
}
