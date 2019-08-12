#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
        {
            f = -1;
        }
        c = getchar();
    }
    while (isdigit(c))
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}
struct node
{
    int fx = -1, zdl = -1;
    int fx2 = -1, zdl2 = -1;
    int bh = -1;
    int bh2 = -1;
}a[101][101];
struct Node
{
    int x, y;
}pl[1001];
int n, m, k;
bool jd[1001];
inline void yd()
{
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= m;j++)
        {
            if (a[i][j].fx != -1)
            {
                if (a[i][j].fx == 0)
                {
                    if (i - 1 < 1)
                    {
                        if (a[i][j].zdl > a[i][j].zdl2)
                        {
                            if (a[i][j].bh2 = -1)
                            {
                                a[i][j].fx2 = 1;
                                a[i][j].zdl2 = a[i][j].zdl;
                                a[i][j].bh2 = a[i][j].bh;
                            }
                            else
                            {
                                a[i][j].fx2 = 1;
                                a[i][j].zdl2 = a[i][j].zdl;
                                jd[a[i][j].bh2] = false;
                                pl[a[i][j].bh2].x = i;
                                pl[a[i][j].bh2].y = j;
                                a[i][j].bh2 = a[i][j].bh;
                            }
                        }
                        else
                        {
                            jd[a[i][j].bh] = false;
                            pl[a[i][j].bh].x = i;
                            pl[a[i][j].bh].y = j;
                        }
                    }
                    else
                    {
                        if (a[i][j].zdl > a[i - 1][j].zdl2)
                        {
                            if (a[i - 1][j].bh2 == -1)
                            {
                                a[i - 1][j].zdl2 = a[i][j].zdl;
                                a[i - 1][j].fx2 = a[i][j].fx;
                                a[i - 1][j].bh2 = a[i][j].bh;
                            }
                            else
                            {
                                a[i - 1][j].zdl2 = a[i][j].zdl;
                                a[i - 1][j].fx2 = a[i][j].fx;
                                a[i - 1][j].bh2 = a[i][j].bh;
                                jd[a[i - 1][j].bh2] = false;
                                pl[a[i - 1][j].bh2].x = i - 1;
                                pl[a[i - 1][j].bh2].y = j;
                                a[i - 1][j].bh2 = a[i][j].bh;
                            }
                        }
                        else
                        {
                            jd[a[i][j].bh] = false;
                            pl[a[i][j].bh].x = i - 1;
                            pl[a[i][j].bh].y = j;
                        }
                    }
                }
                if (a[i][j].fx == 1)
                {
                    if (i + 1 > n)
                    {
                        if (a[i][j].zdl > a[i][j].zdl2)
                        {
                            if (a[i][j].bh2 = -1)
                            {
                                a[i][j].fx2 = 0;
                                a[i][j].zdl2 = a[i][j].zdl;
                                a[i][j].bh2 = a[i][j].bh;
                            }
                            else
                            {
                                a[i][j].fx2 = 0;
                                a[i][j].zdl2 = a[i][j].zdl;
                                jd[a[i][j].bh2] = false;
                                pl[a[i][j].bh2].x = i;
                                pl[a[i][j].bh2].y = j;
                                a[i][j].bh2 = a[i][j].bh;
                            }
                        }
                        else
                        {
                            jd[a[i][j].bh] = false;
                            pl[a[i][j].bh].x = i;
                            pl[a[i][j].bh].y = j;
                        }
                    }
                    else
                    {
                        if (a[i][j].zdl > a[i + 1][j].zdl2)
                        {
                            if (a[i + 1][j].bh2 == -1)
                            {
                                a[i + 1][j].zdl2 = a[i][j].zdl;
                                a[i + 1][j].fx2 = a[i][j].fx;
                                a[i + 1][j].bh2 = a[i][j].bh;
                            }
                            else
                            {
                                a[i + 1][j].zdl2 = a[i][j].zdl;
                                a[i + 1][j].fx2 = a[i][j].fx;
                                jd[a[i + 1][j].bh2] = false;
                                pl[a[i + 1][j].bh2].x = i + 1;
                                pl[a[i + 1][j].bh2].y = j;
                                a[i - 1][j].bh2 = a[i][j].bh;
                            }
                        }
                        else
                        {
                            jd[a[i][j].bh] = false;
                            pl[a[i][j].bh].x = i + 1;
                            pl[a[i][j].bh].y = j;
                        }
                    }
                }
                if (a[i][j].fx == 2)
                {
                    if (j - 1 < 1)
                    {
                        if (a[i][j].zdl > a[i][j].zdl2)
                        {
                            if (a[i][j].bh2 = -1)
                            {
                                a[i][j].fx2 = 3;
                                a[i][j].zdl2 = a[i][j].zdl;
                                a[i][j].bh2 = a[i][j].bh;
                            }
                            else
                            {
                                a[i][j].fx2 = 3;
                                a[i][j].zdl2 = a[i][j].zdl;
                                jd[a[i][j].bh2] = false;
                                pl[a[i][j].bh2].x = i;
                                pl[a[i][j].bh2].y = j;
                                a[i][j].bh2 = a[i][j].bh;
                            }
                        }
                        else
                        {
                            jd[a[i][j].bh] = false;
                            pl[a[i][j].bh].x = i;
                            pl[a[i][j].bh].y = j;
                        }
                    }
                    else
                    {
                        if (a[i][j].zdl > a[i][j - 1].zdl2)
                        {
                            if (a[i][j - 1].bh2 == -1)
                            {
                                a[i][j - 1].zdl2 = a[i][j].zdl;
                                a[i][j - 1].fx2 = a[i][j].fx;
                                a[i][j - 1].bh2 = a[i][j].bh;
                            }
                            else
                            {
                                a[i][j - 1].zdl2 = a[i][j].zdl;
                                a[i][j - 1].fx2 = a[i][j].fx;
                                jd[a[i][j - 1].bh2] = false;
                                pl[a[i][j - 1].bh2].x = i;
                                pl[a[i][j - 1].bh2].y = j - 1;
                                a[i][j - 1].bh2 = a[i][j].bh;
                            }
                        }
                        else
                        {
                            jd[a[i][j].bh] = false;
                            pl[a[i][j].bh].x = i;
                            pl[a[i][j].bh].y = j - 1;
                        }
                    }
                }
                if (a[i][j].fx == 3)
                {
                    if (j + 1 > m)
                    {
                        if (a[i][j].zdl > a[i][j].zdl2)
                        {
                            if (a[i][j].bh2 = -1)
                            {
                                a[i][j].fx2 = 2;
                                a[i][j].zdl2 = a[i][j].zdl;
                                a[i][j].bh2 = a[i][j].bh;
                            }
                            else
                            {
                                a[i][j].fx2 = 2;
                                a[i][j].zdl2 = a[i][j].zdl;
                                jd[a[i][j].bh2] = false;
                                pl[a[i][j].bh2].x = i;
                                pl[a[i][j].bh2].y = j;
                                a[i][j].bh2 = a[i][j].bh;
                            }
                        }
                        else
                        {
                            jd[a[i][j].bh] = false;
                            pl[a[i][j].bh].x = i;
                            pl[a[i][j].bh].y = j;
                        }
                    }
                    else
                    {
                        if (a[i][j].zdl > a[i][j + 1].zdl2)
                        {
                            if (a[i][j + 1].bh2 == -1)
                            {
                                a[i][j + 1].zdl2 = a[i][j].zdl;
                                a[i][j + 1].fx2 = a[i][j].fx;
                                a[i][j + 1].bh2 = a[i][j].bh;
                            }
                            else
                            {
                                a[i][j + 1].zdl2 = a[i][j].zdl;
                                a[i][j + 1].fx2 = a[i][j].fx;
                                jd[a[i][j + 1].bh2] = false;
                                pl[a[i][j + 1].bh2].x = i;
                                pl[a[i][j + 1].bh2].y = j + 1;
                                a[i][j + 1].bh2 = a[i][j].bh;
                            }
                        }
                        else
                        {
                            jd[a[i][j].bh] = false;
                            pl[a[i][j].bh].x = i;
                            pl[a[i][j].bh].y = j + 1;
                        }
                    }
                }
            }
        }
    }
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= m;j++)
        {
            a[i][j].zdl = a[i][j].zdl2;
            a[i][j].fx = a[i][j].fx2;
            a[i][j].bh = a[i][j].bh2;
            a[i][j].zdl2 = -1;
            a[i][j].fx2 = -1;
            a[i][j].bh2 = -1;
        }
    }
}
signed main()
{
    memset(jd, true, sizeof(jd));
    n = read(), m = read(), k = read();
    for (int i = 1;i <= k;i++)
    {
        int x = read(), y = read(), fx = read(), zdl = read();
        a[x][y].fx = fx;
        a[x][y].zdl = zdl;
        a[x][y].bh = i;
    }
    int t = read();
    while (t--)
    {
        yd();
    }
    for (int i = 1;i <= n;i++)
    {
        for (int j = 1;j <= m;j++)
        {
            if (a[i][j].bh != -1)
            {       
              //  if (!jd[a[i][j].bh])
              //  {
              //      continue;
               // }
                pl[a[i][j].bh].x = i;
                pl[a[i][j].bh].y = j;
            }
        }
    }
    for (int i = 1;i <= k;i++)
    {
        printf("%lld %lld\n", pl[i].x, pl[i].y);
    }
   // system("pause");
    return 0;
}
