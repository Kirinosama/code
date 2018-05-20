#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t[21],d[21],o[35];
int cot=0,cnt=0;
ll ans,n,mi[19];
bool ok[19];
inline void chk(ll o,int st)
{while (st<=cnt)
{ll tp=o;cot=0;
while (tp) d[++cot]=tp%10,tp/=10;
reverse(d+1,d+cot+1);
for (int i=1;st+i-1<=cnt&&i<=cot;i++)
{if (d[i]!=t[st+i-1]) return;
}
st+=cot;
o++;
}
if (o-1<ans) ans=o-1;
}
int main (){
	freopen ("number.in","r",stdin);
	freopen ("number.out","w",stdout);
	int T,i,j,k;mi[0]=1ll;
	for (i=1;i<=18;i++) mi[i]=mi[i-1]*10ll;
	scanf ("%d",&T);
	while (T--)
	{scanf ("%lld",&n);
	ll tp=n;ans=n;cnt=0;
	while (tp) t[++cnt]=tp%10,tp/=10;
	reverse(t+1,t+cnt+1);
	for (i=0;i<=cnt;i++) ok[i]=1;
	for (i=1;i<=cnt;i++)
	{if (t[i]!=9) ok[i]=0;
	ok[i]&=ok[i-1];
	}
	for (i=1;i<=cnt;i++)
	{for (j=1;j<=i;j++)
	{ll p1=0,p2=0,res;
	for (k=1;k<=j;k++) p1=p1*10ll+t[k];
	for (k=j+1;k<=i;k++) p2=p2*10ll+t[k];
	res=p2*mi[j]+p1;
	if (res<ans) chk(res+1,j+1);
	if (p2!=0&&ok[j])
	{res=(p2-1)*mi[j]+p1;
	if (res<ans) chk(res+1,j+1);
	}
	}
	}
	printf ("%lld\n",ans);
	}
	return 0;
}
	
	
	
