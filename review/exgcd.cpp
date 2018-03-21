#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int p,q;

void exgcd(int a,int b,int &d,int &x,int &y){
	if(!b){
		d=a,x=1,y=0;
	}
	else{
		exgcd(b,a%b,d,y,x);
		y-=(a/b)*x;
	}
}

int inv(int p,int q){
	int d,x,y;
	exgcd(p,q,d,x,y);
	return d==1 ?  (x+q)%q : -1;
}

int main(){
	freopen("input","r",stdin);
	cin>>p>>q;
	cout<<inv(p,q);
	return 0;
}