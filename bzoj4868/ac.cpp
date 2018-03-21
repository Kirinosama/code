#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 100010

using namespace std;

typedef long long LL;
LL A, B, C, L, R, t[N], b[N];
int n, m;

LL Judge(LL x){
    LL cost = 0;
    if(A < B){//贪心的思想
      LL rest = 0, need = 0;
      for(int i = 1; i <= m; i++)  if(b[i] < x)  rest += x - b[i];
      for(int i = 1; i <= m; i++)  if(b[i] > x)  need += b[i] - x;
      if(rest >= need)  cost += need * A;
      else cost += rest * A + (need - rest) * B; 
    }
    else  for(int i = 1; i <= m; i++)  if(b[i] > x)  cost += (b[i] - x) * B;
    for(int i = 1; i <= n; i++)  if(t[i] < x)  cost += (x - t[i]) * C;
    return cost;
}

int main(){
    freopen("bzoj4868.in","r",stdin);

    scanf("%lld%lld%lld", &A, &B, &C);//视情况选择%lld还是%lld

    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i++)  scanf("%lld", &t[i]);
    for(int i = 1; i <= m; i++)  scanf("%lld", &b[i]);

    if(C == 1e16){//注意这里一定要特判，当C=1e16时，一定会炸，long long都会炸
      LL _min = 1e18;
      for(int i = 1; i <= n; i++)  _min = min(_min, t[i]);
      printf("%lld\n", Judge(_min));//直接不理会等待
      return 0;
    }

    L = 1, R = 1e5;
    while(L + 2 < R){//三分
      LL mid1 = (2 * L + R) / 3, mid2 = (2 * R + L) / 3;
      LL val1 = Judge(mid1), val2 = Judge(mid2);
      if(val1 == val2)  L = mid1,  R = mid2; 
      else if(val1 < val2)  R = mid2;
      else  L = mid1;
    }

    LL val1 = Judge(L), val2 = Judge(R), val3 = Judge((2*L+R)/3), val4 = Judge((2*R+L)/3);//最后算答案
    printf("%lld\n", min(min(val1, val2), min(val3, val4)));

    return 0;
}