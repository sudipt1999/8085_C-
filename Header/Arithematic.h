#include "master.h"
#include "global.h"
#include "tools.h"

bool add(string temp_string) 
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int from=resister_is(v[1]);
		if(from==-1)
			return true;
		else if(from==7)
		{
			from=check_storage(rpair(5));
			if(from==-1)
                return true;
            else
                gpr[0]=gpr[0]+from;
		}
		else
		{
			gpr[0]=gpr[0]+gpr[from];
		}
		set_flag_register(gpr[0]);
		return false;
	}
	else
		return true;
}

bool adi(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int from=resister_is(v[1]);
		if(from==-1)
		{
			if((v[1].length())==2)
			{
				int data=hex2dec(v[1]);
				if(data==-1)
					return true;
				gpr[0]=gpr[0]+data;
				set_flag_register(gpr[0]);
				return false;
			}
			else
				return true;
		}
		else
			return true;
	}
	else
		return true;
}

bool sub(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int from=resister_is(v[1]);
		if(from==-1)
			return true;
		else if(from==7)
		{
			from=check_storage(rpair(5));
			if(from==-1)
                return true;
            else
                gpr[0]=gpr[0]-from;
		}
		else
		{
			gpr[0]=gpr[0]-gpr[from];
		}
		set_flag_register(gpr[0]);
		gpr[0]=fabs(gpr[0]);
		return false;
	}
	else
		return true;
}

bool sui(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int from=resister_is(v[1]);
		if(from==-1)
		{
			if((v[1].length())==2)
			{
				from=hex2dec(v[1]);
				if(from==-1)
					return true;
				gpr[0]=gpr[0]-from;
				set_flag_register(gpr[0]);
				gpr[0]=fabs(gpr[0]);
				return false;
			}
			else
				return true;
		}
		else
			return true;
	}
	else
		return true;
}

bool inx(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int temp=resister_is(v[1]);
		if(temp==7)
			return true;
		else if(temp==1 || temp==3 || temp==5)
		{
				string data;
				int from=rpair(temp);
				from+=1;
				if(from>65535)
				{
					from=0;
					data="0000";
				}
				else
				{
					data=dec2hex(from,4);
				}
				bitset<16> name(from);                   
				if(from<0)									
				{
					flag[4]=1;
				}
				else
				{
					flag[4]=0;
				}
				int numberof1=name.count();					   
				if(numberof1%2==0)
				{
					flag[1]=1;
				}
				else
				{
					flag[1]=0;
				}
				int numberof0=16-numberof1;					   
				if(numberof0==16)
				{
					flag[3]=1;
				}
				else
				{
					flag[3]=0;
				}
				string X1="",X2="";
				X1=X1+data[0]+data[1];
				X2=X2+data[2]+data[3];
				gpr[temp]=hex2dec(X1);
				gpr[temp+1]=hex2dec(X2);
				return false;
		}
		else
		{
			return true;
		}
	}
	return true;
}

bool inr(string temp_string)
{
		vector<string> v;
		v=splitter(temp_string);
		int size=v.size();
		if(size==2)
		{
			 int temp=resister_is(v[1]);
			 int from;
			 if(temp==-1)
				 return true;
			 else if(temp==7)
		     {
				 from=check_storage(rpair(5));
				 from=from+1;
				 if(from>255)
				 {
					 from=0;
				 }
				storage[rpair(5)]=from;
			 }
			 else
			 {
				 from=gpr[temp]+1;
				 if(from>255)
					from=0;
				 else
				 {
					gpr[temp]=from;
				 }
			 }
			set_flag_register(from);
			return false;
		}
		return true;
}

bool dcx(string temp_string)
{
		vector<string> v;
		v=splitter(temp_string);
		int size=v.size();
		if(size==2)
		{
			int temp=resister_is(v[1]);
			if(temp==7)
				return true;
			else if(temp==1 || temp==3 || temp==5)
			{
				string data;
				int from=rpair(temp);	
				from=from-1;
				if(from==-1)
				{
					from=65535;
					data="FFFF";
				}
				else if(from==0)
				{
					from=0;
					data="0000";
				}
				else
				{
					data=dec2hex(from,4);
				}
				bitset<16> name(from);      
				if(from<0)									
				{
					flag[4]=1;
				}
				else
				{
					flag[4]=0;
				}
				int numberof1=name.count();	 
				if(numberof1%2==0)
				{
					flag[1]=1;
				}
				else
				{
					flag[1]=0;
				}
				int numberof0=16-numberof1;	
				if(numberof0==16)
				{
					flag[3]=1;
				}
				else
				{
					flag[3]=0;
				}
				string X1="",X2="";
				X1=X1+data[0]+data[1];
				X2=X2+data[2]+data[3];
				gpr[temp]=hex2dec(X1);
				gpr[temp+1]=hex2dec(X2);
				return false;
			}
			else
				return true;
		}
		else
			return true;
}

bool dcr(string temp_string)
{
		vector<string> v;
		v=splitter(temp_string);
		int size=v.size();
		if(size==2)
		{
			int temp=resister_is(v[1]);
			int from;
		    string data;
		    if(temp==-1)
				 return true;
		    else if(temp==7)
		    {
				 from=check_storage(rpair(5));
				 from=from-1;
				 if(from<0)
					storage[rpair(5)]=255;
				 else
					storage[rpair(5)]=from;
			 }
			 else
			 {
				 from=gpr[temp]-1;
				 if(from<0)
					gpr[temp]=255;
				 else
					gpr[temp]=from;
			 }
			 set_flag_register(from);
			return false;
		}
		return true;
}

bool dad(string temp_string)
{
		vector<string> v;
		v=splitter(temp_string);
		int size=v.size();
		if(size==2)
		{
			int temp=resister_is(v[1]);
			if(temp==7)
				return true;
			else if(temp==1 || temp==3 || temp==5)
			{
				int from=rpair(temp);
				int with=rpair(5);
				int result=from+with;
				if(result>65535)
				{
					flag[0]=1;
				}
				string data=dec2hex(result,4);
				string X1="",X2="";
				X1=X1+data[0]+data[1];
				X2=X2+data[2]+data[3];
				gpr[5]=hex2dec(X1);
				gpr[6]=hex2dec(X2);
				return false;
			}
			else
				return true;
		}
		else
			return true;
}
