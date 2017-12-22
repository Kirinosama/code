#include<cstdio>
#include<cstring>
int m,n;
bool g[30][30];
int P (char x){return x-'a'+1;}
void solve ()
{
    char s1[55],s2[55];
    scanf("%s%s",s1,s2);
    int len1=strlen(s1),len2=strlen(s2);
    if (len1!=len2) {puts("no");return ;}
    for (int u=0;u<len1;u++)
        if (!g[P(s1[u])][P(s2[u])]) {puts("no");return ;}
    puts("yes");return ;
}
int main()
{
    memset(g,false,sizeof(g));
    scanf("%d%d",&m,&n);
    for (int u=1;u<=m;u++)
    {
        char a=getchar();
        while (a<'a'||a>'z') a=getchar();
        char b=getchar();
        while (b<'a'||b>'z') b=getchar();
        g[P(a)][P(b)]=true;
    }
    for (int u=1;u<=26;u++) g[u][u]=true;
    for (int u=1;u<=26;u++)
        for (int i=1;i<=26;i++)
            for (int j=1;j<=26;j++)
                if (g[i][u]&&g[u][j])
                    g[i][j]=true;

    for (int u=1;u<=n;u++)
        solve();
    return 0;
}