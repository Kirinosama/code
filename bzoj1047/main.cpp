#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <algorithm>

using namespace std;
const int maxn = 1100;
const int INF = 0x3f3f3f3f;

inline  int re() { int n; scanf("%d",&n); return n; }
int a , b , n;
int g[maxn][maxn];
int Min[maxn] , Max[maxn];

int qmin[maxn] , l1 , r1;
int qmax[maxn] , l2 , r2;

int main(int argc, char *argv[]) {

    a = re(); b = re(); n = re();

    for(int i=1;i<=a;i++) for(int j=1;j<=b;j++) g[i][j] = re();

    int res = INF*2;
    for(int i=1;i+n-1<=a;i++)
    {
        l1 = r1 = 0;
        l2 = r2 = 0;        
        for(int j=1;j<=b;j++)
        {
            Min[j] = INF; Max[j] = -INF;
            for(int k=0;k<n;k++) 
                Min[j] = min(Min[j] , g[i+k][j]) , Max[j] = max(Max[j] , g[i+k][j]);

            if(l1<r1 && qmin[l1]==j-n) l1++;
            if(l2<r2 && qmax[l2]==j-n) l2++;
            while(l1<r1 && Min[qmin[r1-1]] >= Min[j]) r1--; qmin[r1++] = j;
            while(l2<r2 && Max[qmax[r2-1]] <= Max[j]) r2--; qmax[r2++] = j;

            if(j>=n) res = min(res , Max[qmax[l2]] - Min[qmin[l1]]);
        }
    }
    printf("%d\n",res);

    return 0;
}