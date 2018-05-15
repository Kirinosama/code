#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

int main(){
    freopen("bzoj4514.in","w",stdout);
    srand(time(0));
    int n=200;cout<<n<<endl;
    for(int i=1;i<=n;i++)
        printf("%d ",rand()%1000+1);
    cout<<endl;
    for(int i=1;i<=n;i++)
        printf("%d ",rand()%10000+1);
    cout<<endl;
    for(int i=1;i<=n;i++)
        printf("%d ",rand()%2001-1000);
    cout<<endl;
    return 0;
}
