 #include <cstdio>
 
using namespace std;
const int N = 1000005;
int n, m, C, a[N];
int q1[N], q2[N], h1, h2, t1, t2;
bool f;
 
inline int read(){
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}
 
int pr[10], NUM = 0;
inline int print(int x){
    while (x)
        pr[++NUM] = (x % 10) + '0', x /= 10;
    while (NUM)
        putchar(pr[NUM--]);
    putchar('\n');
}
 
inline bool check(int i){
    return a[q1[h1]] - a[q2[h2]] <= C && i >= m;
}
 
int main(){
    n = read(), m = read(), C = read();
    int i;
    for (i = 1; i <= n; ++i)
        a[i] = read();
    f = 0;
    q1[1] = q2[1] = 1, h1 = t1 = h2 = t2 = 1;
    if (check(1)){
        print(1);
        f = 1;
    }
    for (i = 2; i <= n; ++i){
        while (q1[h1] + m <= i) ++h1;
        while (h1 <= t1 && a[q1[t1]] <= a[i]) --t1;
        q1[++t1] = i;
        while (q2[h2] + m <= i) ++h2;
        while (h2 <= t2 && a[q2[t2]] >= a[i]) --t2;
        q2[++t2] = i;
        if (check(i)){
            print(i - m + 1);
            f = 1;
        }
    }
    if (!f) puts("NONE");
    return 0;
}