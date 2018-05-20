#include<bits/stdc++.h>
#define L long long
using namespace std;
const int m=150,K=18;
int n,d,a,b,x[160],y[610],f[1050000],g[1050000],p=1e9;
int main()
{
	//freopen("point.in","r",stdin);
	//freopen("point.out","w",stdout);
	int i,j,k;
	scanf("%d%d%d%d",&n,&d,&a,&b);
	d*=2;
	b=min(a,b);
	for(i=1;i<=n;i++)
	  {
	   scanf("%d",&x[i]);
	   y[x[i]+d]=1;
	  }
	if(d<=K)
	  {
	   for(i=1;i<(1<<d);i++)
	     f[i]=1e9;
	   for(i=1;i<=m+2*d;i++)
	     {
		  for(j=0;j<(1<<d);j++)
		    if(y[i] && !(j&1))
		      g[j]=f[(j>>1)|(1<<d-1)];
		    else
		      g[j]=min(f[j>>1],f[(j>>1)|(1<<d-1)])+((j&1)?(((j&2)?b:a)):0);
		  for(j=0;j<(1<<d);j++)
		    f[j]=g[j];
		 }
	   for(i=0;i<(1<<d);i++)
	     p=min(p,f[i]);
	   printf("%d\n",p);
	  }
	else
	  {
	   int w=(m+d-1)/d+1;
	   for(k=0;k<(1<<w);k++)
	     {
		  for(i=d;i<=w*d;i+=d)
		    if(y[i] && !(k&(1<<i/d-1)) && !(k&(1<<i/d-2)))
		      break;
		  if(i<=w*d)
		    continue;
		  for(i=1;i<(1<<w);i++)
		    f[i]=1e9;
		  f[0]=0;
		  for(i=1;;i+=d)
		    {
			 if(i>w*d)
			   {
				i=i%d+1;
				if(i==d)
				  break;
			   }
			 for(j=0;j<(1<<w);j++)
		       if(y[i] && !(j&1) && !(j&2))
		         g[j]=1e9;
		       else
		         g[j]=min(f[j>>1]+(j&1)*a,f[(j>>1)|(1<<w-1)]+(j&1)*b)+((i%d==d-1 && k&(1<<i/d) && j&1)?(b-a):0)+((i%d==1 && i>1 && k&(1<<i/d-1) && j&1)?(b-a):0);
		     for(j=0;j<(1<<w);j++)
		       f[j]=g[j];
		    }
		  for(i=0,j=0;i<w;i++)
		    if(k&(1<<i))
		      j+=a;
	      for(i=0;i<(1<<w);i++)
		    p=min(p,f[i]+j);
		 }
	   printf("%d\n",p);
	  }
	return 0;
}
