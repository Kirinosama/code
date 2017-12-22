#include <cstdio>  
#include <algorithm>  
   
using namespace std;  
   
const int maxn = 2000005, maxm = 640005, maxq = 10005;  
   
int n, tr[maxn], ans[maxq];  
   
struct _data {  
    int opt, id, qid, x, y, c;  
} c[maxm], tmp[maxm];  
   
inline int iread() {  
    int f = 1, x = 0; char ch = getchar();  
    for(; ch < '0' || ch > '9'; ch = getchar()) f = ch == '-' ? -1 : 1;  
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';  
    return f * x;  
}  
   
inline void add(int x, int c) {  
    for(; x <= n; x += x & -x) tr[x] += c;  
}  
   
inline int sum(int x) {  
    int res = 0;  
    for(; x; x -= x & -x) res += tr[x];  
    return res;  
}  
   
inline int cmp(_data a, _data b) {  
    return a.x != b.x ? a.x < b.x : a.y != b.y ? a.y < b.y : a.opt < b.opt;  
}  
   
inline void cdq(int l, int r) {  
    if(l == r) return;  
    int mid = (l + r) >> 1;  
    for(int i = l; i <= r; i++)  
        if(c[i].opt == 1 && c[i].id <= mid) add(c[i].y, c[i].c);  
        else if(c[i].opt == 2 && c[i].id > mid) ans[c[i].qid] += c[i].c * sum(c[i].y);  
    for(int i = l; i <= r; i++)  
        if(c[i].opt == 1 && c[i].id <= mid) add(c[i].y, -c[i].c);  
    int h1 = l, h2 = mid;  
    for(int i = l; i <= r; i++)  
        if(c[i].id <= mid) tmp[h1++] = c[i];  
        else tmp[++h2] = c[i];  
    for(int i = l; i <= r; i++) c[i] = tmp[i];  
    cdq(l, mid); cdq(mid + 1, r);  
}  
   
int main() {  
    int s = iread(); n = iread(); int tot = 0, id = 0;  
    while(1) {  
        int opt = iread();  
        if(opt == 3) break;  
   
        if(opt == 1) {  
            int x = iread(), y = iread(), w = iread();  
            c[++tot] = (_data){1, tot, 0, x, y, w};  
        } else {  
            int x1 = iread(), y1 = iread(), x2 = iread(), y2 = iread(); id++;  
            c[++tot] = (_data){2, tot, id, x2, y2, 1};  
            c[++tot] = (_data){2, tot, id, x1 - 1, y2, -1};  
            c[++tot] = (_data){2, tot, id, x2, y1 - 1, -1};  
            c[++tot] = (_data){2, tot, id, x1 - 1, y1 - 1, 1};  
        }  
    }  
    sort(c + 1, c + 1 + tot, cmp);  
    cdq(1, tot);  
    for(int i = 1; i <= id; i++) printf("%d\n", ans[i]);  
    return 0;  
}  