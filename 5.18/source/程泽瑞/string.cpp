#include <bits/stdc++.h>
using namespace std;
const int MAXL=44800;
const int MAXBUF=1<<25;
int p[MAXL+5],t[MAXL+5];
char Buff[MAXBUF],*sti=Buff;
int main (){
	freopen ("string.in","r",stdin);
	freopen ("string.out","w",stdout);
	int T,n,len,ro,i,j,k,o;
	scanf ("%d",&T);
	for (i=1;i<=MAXL;i++) p[i]=p[i-1]+(i-1);
	for (i=0;i<=MAXL;i++)
	{while (p[t[i]+1]<=i) t[i]++;
	}
	while (T--)
	{scanf ("%d",&n);len=1;
	while (p[len]<n) len++;
	ro=p[len]-n;o=1;
	while (len)
	{int l=t[ro];len-=l;ro-=p[l];o^=1;
	for (i=1;i<=l;i++) *sti++=('0'+o);
	}
	*sti++='\n';
	}
	fwrite(Buff,1,sti-Buff,stdout);
	return 0;
}
	
