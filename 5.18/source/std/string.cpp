#include<bits/stdc++.h>
#define L long long
using namespace std;
int t,n;
char s[100000];
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int i,j,k,l,u;
	scanf("%d",&t);
	while(t--)
	  {
       scanf("%d",&n);
       for(i=1;i*(i-1)<2*n;i++);
       k=(i*(i-1)-2*n)/2;
       for(j=0,l=0,u=0;j<i;j++)
         {
          if(l<=k)
            k-=l++;
          else
            l=1,u^=1;
          s[j]=u+'0';
         }
       s[j]=0;
       puts(s);
      }
	return 0;
}
