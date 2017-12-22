#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

#define MAX_skill_cnt 100010

struct sk
{
	int dps[20];
	double wai_addtion;
	double nei_addtion;
	void in(){
		for(int i=1;i<=12;i++) scanf("%d",&dps[i]);
		scanf("%lf %lf",&wai_addtion,&nei_addtion);
	}
}Skill[MAX_skill_cnt];

map <string,int> skill_num;
string s;
int x,skill_cnt;

void init()
{
	freopen("name_to_number.in","r",stdin);
	while(cin>>s)
		skill_num.insert(make_pair(s,++x));
	fclose(stdin);
	
	freopen("addtion.in","r",stdin);
	scanf("%d",&skill_cnt);
	for(int i=1;i<=skill_cnt;i++) Skill[i].in();
	fclose(stdin);
}

void solve()
{
	char skill_name[100];
	int Lev,Jswl,Ngwl,Baowu,Jcsh,Binglu,Waifang,Pofang,Neifang,jian;
	double Ngjc,Wgjc,Baoshang,Neigong,Pizhu,Jianmian,Baomian;
	freopen("input","r",stdin);
	//freopen("CON", "r", stdin);
	//freopen("/dev/console", "r", stdin);
	cout<<"您想要计算的技能是:";
	scanf("%s",skill_name);
	cout<<skill_name<<endl<<endl;
	
	sk cur=Skill[skill_num[skill_name]];
	Ngjc=cur.nei_addtion;Wgjc=cur.wai_addtion;

	cout<<"您的招式等级是:";
	scanf("%d",&Lev);cout<<Lev<<endl<<endl;
	
	Jcsh=cur.dps[Lev];

	cout<<"您的近身威力是:";
	scanf("%d",&Jswl);cout<<Jswl<<endl<<endl;

	cout<<"您的内功威力是:";
	scanf("%d",&Ngwl);cout<<Ngwl<<endl<<endl;

	cout<<"您的宝物技能伤害加成是:";
	scanf("%d",&Baowu);cout<<Baowu<<endl<<endl;

	cout<<"您的宝物暴击伤害加成(XX％)是:";
	scanf("%lf",&Baoshang);cout<<Baoshang<<endl<<endl;

	cout<<"您的对手的暴击减免(xx％)是:";
	scanf("%lf",&Baomian);cout<<Baomian<<endl<<endl;

	cout<<"您的内功属性对于套路加成(0.16/0.2/0)是:";
	scanf("%lf",&Neigong);cout<<Neigong<<endl<<endl;

	cout<<"您的装备及批注书加成(0.1/0.2/0.3/0.4)是:";
	scanf("%lf",&Pizhu);cout<<Pizhu<<endl<<endl;

	cout<<"您的兵录加成是:";
	scanf("%d",&Binglu);cout<<Binglu<<endl<<endl;

	cout<<"您的招式是外功还是内功:";
	char str[100];scanf("%s",str);cout<<str<<endl<<endl;
	if(!strcmp(str,"外功"))
	{
		cout<<"对手的外功防御值是:";
		scanf("%d",&Waifang);
		cout<<Waifang<<endl<<endl;

		cout<<"您的武器和飞爪破防共计是:";
		scanf("%d",&jian);
		cout<<jian<<endl<<endl;

		Waifang=max(Waifang-jian*10,0);Waifang/=100;
		Jianmian=-43.8927+19.6447*log(Waifang);Jianmian/=100;Jianmian=max(Jianmian,0.0);
	}

	else
	{
		cout<<"对手的对应内功伤害减免是(xx％):";
		scanf("%lf",&Jianmian);
		cout<<Jianmian<<endl<<endl;
	}

	double putong_sh=(Jcsh+(Ngwl*Ngjc)+(Wgjc*Jswl))*(1+Pizhu)*(1+Neigong)+Baowu+Binglu;
	double baoji_sh=(Jcsh+(Ngwl*Ngjc)+(Wgjc*Jswl))*(1+Pizhu)*(1+Neigong)*(Baoshang+2-Baomian)+Baowu*(Baoshang+2-Baomian)+Binglu;
	putong_sh*=(1-Jianmian);
	baoji_sh*=(1-Jianmian);
	printf("不暴击伤害为:%.2f\n",putong_sh);
	printf("全暴击伤害为:%.2f\n",baoji_sh);
}

int main()
{
	init();
	solve();
	return 0;
}