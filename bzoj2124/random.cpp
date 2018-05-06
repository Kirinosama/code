#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <algorithm>
using namespace std;

int a[10010];

int main(){
    freopen("bzoj2124.in","w",stdout);
    srand(time(0));
    cout<<7<<endl;
    for(int j=1;j<=7;j++){
        int n=rand()%10+1;
        cout<<n<<endl;
        for(int i=1;i<=n;i++)a[i]=i;
        random_shuffle(a+1,a+n+1);
        for(int i=1;i<=n;i++)printf("%d ",a[i]);
        cout<<endl;
    }
    return 0;
}
