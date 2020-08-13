#include "master.h"
#include "global.h"
#include "tools.h"

bool cma(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==1)
	{
		bitset<8> temp(gpr[0]);
		for(int i=0;i<8;i++)
		{
			if(temp.test(i)==1)
			{
				temp[i]=0;
			}
			else
			{
				temp[i]=1;
			}
		}
		int sum=(int)(temp.to_ulong());
		gpr[0]=sum;
		return false;
	}
	else
		return true;
}

bool cmp(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int compare=resister_is(v[1]);
		if(compare == -1)
			return true;
		else if( compare == 7 )
		{
			int compare=check_storage(rpair(5));
			if( compare == -1)
				return true;
			else
			{
				if(compare==gpr[0])
				{
						flag[3]=1;
						flag[0]=0;												//SET ZERO FLAG
				}
				else if(compare>gpr[0])
				{
						flag[0]=1;
						flag[3]=0;													
				}
				else
				{
						flag[0]=0;
						flag[3]=0;													
				}
			}
		}
		else
		{
			if(gpr[compare]==gpr[0])
			{
					flag[3]=1;
					flag[0]=0;									
			}
			else if(gpr[compare]>gpr[0])
			{
					flag[0]=1;
					flag[3]=0;										
			}
			else
			{
					flag[0]=0;
					flag[3]=0;												
			}
		}
		return false;
	}
	else
		return true;
}
