#include <bits/stdc++.h>
using namespace std;

#define eps 1e-8
#define ii pair<int,int>

int n,sx,sy,a[1010],b[1010];
int last[1010],ne[2010],edge_cnt;
int du[1010],f[1010][2010];
double Min[1010][2010];

struct edge{
	int x,y;
}E[2010];

void add_edge(int x,int y){
	E[++edge_cnt]=(edge){x,y};
	ne[edge_cnt]=last[x];
	last[x]=edge_cnt;
}

double sqr(double x){
	return x*x;
}

bool dis(int x,int y,double v){
	return Min[x][y]<=sqr(v);
}

int t(int x){return x-1+(x&1);}

void premake(int x,int y){
	int p=E[y].x,q=E[y].y;
	double res=min(sqr(a[x]-a[p])+sqr(b[x]-b[p]),sqr(a[x]-a[q])+sqr(b[x]-b[q]));
	if(a[p]==a[q] && b[x]>=min(b[p],b[q]) && b[x]<=max(b[p],b[q]))
		res=min(res,sqr(a[x]-a[p]));
	else{
		double K=(double)(b[q]-b[p])/(double)(a[q]-a[p]);
		double B=(double)b[p]-(double)a[p]*K;
		double K1=-1.0/K,B1=(double)b[x]-(double)a[x]*K1;
		double newx=(B-B1)/(K1-K),newy=K*newx+B;
		if(newx>=min(a[p],a[q])-eps && newx<=max(a[p],a[q])+eps)
			res=min(res,sqr(a[x]-newx)+sqr(b[x]-newy));
	}
	Min[x][y]=res;
}

bool judge(double v){
	if(sqr(a[sx]-a[sy])+sqr(b[sx]-b[sy])>sqr(v)) return false;
	queue<ii>Q;
	memset(f,0,sizeof(f));
	for(int i=last[sx];i;i=ne[i]){
		int cur=t(i);
		if(dis(sy,cur,v) && !f[sy][cur])
			f[sy][cur]=1,Q.push(ii(sy,cur));
	}
	for(int i=last[sy];i;i=ne[i]){
		int cur=t(i);
		if(dis(sx,cur,v) && !f[sx][cur])
			f[sx][cur]=1,Q.push(ii(sx,cur));
	}
	while(!Q.empty()){
		ii tp=Q.front();Q.pop();
		int x=tp.first,y=tp.second;
		int n1=E[y].x,n2=E[y].y;
		if(du[x]==1 && du[n1]==1)
			if(sqr(a[x]-a[n1])+sqr(b[x]-b[n1])<=sqr(v))
				return true;
		if(du[x]==1 && du[n2]==1)
			if(sqr(a[x]-a[n2])+sqr(b[x]-b[n2])<=sqr(v))
				return true;
		for(int i=last[x];i;i=ne[i]){
			if(dis(E[i].y,y,v) && !f[E[i].y][y])
				f[E[i].y][y]=1,Q.push(ii(E[i].y,y));
		}
		for(int i=last[x];i;i=ne[i]){
			int cur=t(i);
			if(dis(n1,cur,v) && !f[n1][cur])
				f[n1][cur]=1,Q.push(ii(n1,cur));
			if(dis(n2,cur,v) && !f[n2][cur])
				f[n2][cur]=1,Q.push(ii(n2,cur));
		}
	}
	return false;
}

int main(){
	freopen("input","r",stdin);
	cin>>n>>sx>>sy;
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		du[x]++,du[y]++;
		add_edge(x,y);add_edge(y,x);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=edge_cnt;j+=2)
			premake(i,j);
	double l=0.0,r=2e6,mid,res;
	while(r-l>eps){
		mid=(l+r)/2.0;
		if(judge(mid)) res=mid,r=mid;
		else l=mid;
	}
	printf("%.7f",res);
	return 0;
}
