#include<bits/stdc++.h>
#define L long long
using namespace std;
int t,m;
L n,x[20],p;
inline int orz(L n)
{
	int i;
	for(i=17;i>=0;i--)
	  if(n>=x[i])
	    return i;
	return -1;
}
inline L orz(L n,int l,int r)
{
	return n%x[l+1]/x[r];
}
inline bool chk(int l,int r,L w)
{
	if(r>l)
	  return 1;
	L u=orz(n,l,r);
	int i;
	for(i=orz(w)+1;i>=0;i--)
	  if(w%x[i]==u)
	    return 1;
	return 0;
}
inline bool chk2(int l,int r,L w)
{
	if(r>=0)
	  return w==orz(n,l,r);
	else
	  return w/x[-r]==orz(n,l,0);
}
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int i,j,k;
	L w,u,v;
	x[0]=1;
	for(i=1;i<=18;i++)
	  x[i]=x[i-1]*10;
	scanf("%d",&t);
	while(t--)
	  {
	   scanf("%lld",&n);
	   m=orz(n);
	   p=n;
	   for(i=m;i>=0;i--)
	     for(j=i;j>=0;j--)
	       {
	       	w=orz(n,i,j);
	       	if(orz(w)==i-j && chk(m,i+1,w-1))
	       	  {
	       	   for(k=j-1,w++;k>=0;k-=orz(w)+1,w++)
	       	     if(!chk2(k,k-orz(w),w))
	       	       break;
	       	   if(k<0)
	       	     p=min(p,w-1);
	       	  }
	       }
	   for(i=m-1;i>=0;i--)
	     for(j=0;j<=m-i && j<=i+1;j++)
	       {
	       	w=orz(n,m,i+1)+1;
	       	u=orz(n,i,0);
	       	if(orz(u)==i && w/x[m-i-j]%x[j]==u%x[j])
	       	  p=min(p,w%x[m-i]+u/x[j]*x[m-i]);
	       }
	   printf("%lld\n",p);
	  }
	return 0;
}
