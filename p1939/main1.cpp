#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
using namespace std;
string start,end;
map<string,int> mmp;

struct dink
{
	string s;
	int sp;
};

queue<dink> q;
int main()
{
	cin>>start;
	end="123804765";
	mmp[start]=1;//用过了 
	q.push((dink){start,0});
	while(!q.empty())
	{
		string x=q.front().s;
		int step=q.front().sp;
		q.pop();//x代换了pop掉拉倒 
		if(x==end)
		{cout<<step;return 0;}//边界 
		
		for(register int i=0;i<=8;i++)
		{
			
			if(x[i]=='0')
			{
				if(i>=3)//向上
				{
					string temp=x;
					swap(temp[i],temp[i-3]);
					if(!mmp[temp]) 
					{
						mmp[temp]=1;
						q.push((dink){temp,step+1});
					}
				} 
				if(i<6)//向下 
				{
					string temp=x;
					swap(temp[i],temp[i+3]);
					if(!mmp[temp]) 
					{
						mmp[temp]=1;
						q.push((dink){temp,step+1});
					}
				}
				if(i%3!=0)//向左
				{
					string temp=x;
					swap(temp[i],temp[i-1]);
					if(!mmp[temp]) 
					{
						mmp[temp]=1;
						q.push((dink){temp,step+1});
					}
				}
				if(i%3!=2)//向右
				{
					string temp=x;
					swap(temp[i],temp[i+1]);
					if(!mmp[temp]) 
					{
						mmp[temp]=1;
						q.push((dink){temp,step+1});
					}
				} 	
			}
		}
	}
	return 0;
}
