#include<bits/stdc++.h>
#define L long long
using namespace std;

FILE *fscore,*freport,*fstd,*fin,*fout;

int t,n,m,p;
char s[100000];
inline int ran()
{
    return (rand()<<15)+rand();
}
int main(int argc,char *argv[])
{
	fscore=fopen(argv[5],"w");//得分文件
	freport=fopen(argv[6],"w");//报告文件
	fstd=fopen(argv[3],"r");//标准输出
	int score=atoi(argv[4]);
	
	fin=fopen(argv[1],"r");//标准输入
	fout=fopen(argv[2],"r");//用户输出
    
	int i,j,k,len;
	fscanf(fin,"%d",&t);
	while(t--)
	  {
	   fscanf(fin,"%d",&n);
	   fscanf(fstd,"%d",&m);
       fscanf(fout,"%s",s);
       len=strlen(s);
       if(len!=m)
         p=1;
       for(i=0,j=0,k=0;i<len;i++)
         if(!i || s[i]==s[i-1])
           j++;
         else
           k+=(len-i)*j,j=1;
       if(k!=n)
         p=2;
      }
    if(p==0)
      {fprintf(fscore,"%d",score);	fprintf(freport,"Accepted");}
    else if(p==1)
      {fprintf(fscore,"%d",0);	fprintf(freport,"Wrong Length");}
    else
 	  {fprintf(fscore,"%d",0);	fprintf(freport,"Wrong Answer");}
	return 0;
}

