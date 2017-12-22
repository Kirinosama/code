for(int i=1;i<=m;i++)//时间
{
	for(int j=0;j<=10;j++)//combo 
	{
		for(int o=1;o<=n;o++)//课程
		{
			for(int t=0;t<=k;t++)//上次的阴影
			{
				if(!dis[t][o]) //课程可选
				{
					if(s[i]==task[o]) //可以继续combo
					{
						if(j!=0) f[i][j][shadow[o]]=max(f[i][j][shadow[o]],f[i-1][j-1][t]+cal(s[i],task[o]));
						else f[i][j][shadow[o]]=max(f[i][j][shadow[o]],f[i-1][10][t]+cal(s[i],task[o])+55);
					}
					else if(j==0)
					{
						for(int p=0;p<=10;p++) //上次combo
							f[i][j][shadow[o]]=max(f[i][j][shadow[o]],f[i-1][p][t]+cal(s[i],task[o])+p*(p+1)/2);
					}
				}
			}
		}
	}
}