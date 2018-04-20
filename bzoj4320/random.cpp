#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int main(){
    freopen("bzoj4320.in","w",stdout);
    srand(time(0));
    int n=100;cout<<n<<endl;
    for(int i=1;i<=n;i++){
        char c=rand()%2?'A':'B';
        if(i==1) c='A';
        int x=rand()%300000+1;
        printf("%c %d\n",c,x);
    }
    return 0;
}
