#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;

#define MAXN 100010
#define eps 1e-8
#define It set<node>::iterator
typedef long long ll;

double rx,ry;

struct node{
	double x,y,ang;
	node(){}
	node(double a,double b){x=a,y=b,ang=atan2(b-rx,a-ry);}
	bool operator < (const node &a)const{
		if(fabs(ang-a.ang)<eps) return (x-rx)*(x-rx)+(y-ry)*(y-ry)<(a.x-rx)*(a.x-rx)+(a.y-ry)*(a.y-ry);
		return ang<a.ang;
	}
	node operator - (const node &a)const{
		return node(x-a.x,y-a.y);
	}
	double operator ^ (const node &a)const{
		return x*a.y-y*a.x;
	}
};

set <node> S;
int q;

void premake(){
	double a[3],b[3];int x;
	for(int i=0;i<3;i++){
		scanf("%d%lf%lf",&x,&a[i],&b[i]);
		rx+=a[i]/3.0,ry+=b[i]/3.0;
	}
	for(int i=0;i<3;i++)S.insert(node(a[i],b[i]));
}

It L(It x){
	if(x==S.begin())x=S.end();
	x--;return x;
}

It R(It x){
	x++;if(x==S.end())x=S.begin();
	return x;
}

void add_point(double x,double y){
	node cur(x,y);
	It posr=S.lower_bound(cur);
	if(posr==S.end())posr=S.begin();
	It posl=L(posr);
	if(((*posr-*posl)^(cur-*posl))>=0) return;
	S.insert(cur);
	It now,i,j;
	now=S.find(cur);
	i=L(now),j=L(i);
	while(((*now-*j)^(*i-*j))>=0){
		S.erase(i);
		i=j,j=L(j);
	}
	i=R(now),j=R(i);
	while(((*j-*now)^(*i-*now))>=0){
		S.erase(i);
		i=j;j=R(j);
	}
}

void query_point(double x,double y){
	node cur(x,y);
	It posr=S.lower_bound(cur);
	if(posr==S.end())posr=S.begin();
	It posl=L(posr);
	if(((*posr-*posl)^(cur-*posl))>=0) printf("YES\n");
	else printf("NO\n");
}

void solve(){
	int opt;double x,y;
	scanf("%d%lf%lf",&opt,&x,&y);
	if(opt==1)add_point(x,y);
	else query_point(x,y);
}

int main(){
	freopen("cf70d.in","r",stdin);
	cin>>q;q-=3;
	premake();
	while(q--)solve();
	return 0;
}
