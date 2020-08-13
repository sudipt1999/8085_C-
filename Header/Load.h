#include "master.h"
#include "global.h"
#include "tools.h"

bool mov(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==3)
	{
		int to=resister_is(v[1]);
		int from=resister_is(v[2]);
		if(to == -1 || from == -1)
			return true;
		else if( to == 7 && from == 7)
			return true;
		else if( to == 7 && from!=7 && from!=-1 )
		{
			to=rpair(5);
			storage[to]=gpr[from];
		}
		else if( from == 7 && to!=7 && to!=-1)
		{
			from=rpair(5);
			gpr[to]=storage[from];
		}
		else
		{
			gpr[to]=gpr[from];
		}
		return false;
	}
	else
		return true;
}

bool mvi(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==3)
	{
		int to=resister_is(v[1]);
		if(to == -1 )
			return true;
		else if( to == 7 )
		{
			int len=v[2].length();
			if(len == 2)
			{
				int data=hex2dec(v[2]);
				if(data==-1)
					return true;
				to=rpair(5);
				storage[to]=data;
			}
			else
				return true;
		}
		else
		{
			int data=hex2dec(v[2]);
			if(data==-1)
					return true;
			gpr[to]=data;
		}
		return false;
	}
	else
		return true;
}

bool lxi(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==3)
	{
		int to=resister_is(v[1]);
		if(to == -1 || to == 7)
			return true;
		else
		{
			int len=v[2].length();
			if(len == 4)
			{
				string data=v[2];
				string temp1="",temp2="";
				temp1=temp1+data[0]+data[1];
				temp2=temp2+data[2]+data[3];
				if(to == 1)
				{
					gpr[1]=hex2dec(temp1);
					gpr[2]=hex2dec(temp2);
				}
				else if(to == 3)
				{
					gpr[3]=hex2dec(temp1);
					gpr[4]=hex2dec(temp2);
				}
				else if(to == 5)
				{
					gpr[5]=hex2dec(temp1);
					gpr[6]=hex2dec(temp2);
				}
				else
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	else
		return true;
}

bool xchg(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==1)
	{
		int swap_temp=gpr[5];
		gpr[5]=gpr[3];
		gpr[3]=swap_temp;
		swap_temp=gpr[6];
		gpr[6]=gpr[4];
		gpr[4]=swap_temp;
		return false;
	}
	else
		return true;
}

bool lhld(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int len=v[1].length();
		if(len == 4 )
		{
			int address=hex2dec(v[1]);
			if(address==-1)
				return true;
			string data=dec2hex(storage[address],2);
			string temp1="",temp2="";
			temp1=temp1+data[0]+data[1];
			data=dec2hex(storage[address+1],2);
			temp2=temp2+data[0]+data[1];
			gpr[6]=hex2dec(temp1);
			gpr[5]=hex2dec(temp2);
			return false;
		}
		else
		{
			return true;
		}
	}
	else
		return true;
}

bool lda(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int len=v[1].length();
		if(len == 4 )
		{
			int data=hex2dec(v[1]);
			if(data==-1)
					return true;
			gpr[0]=storage[data];
			return false;
		}
		else
		{
			return true;
		}
	}
	else
		return true;
}

bool shld(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int len=v[1].length();
		if(len == 4 )
		{
			int address=hex2dec(v[1]);
			if(address==-1)
				return true;
			storage[address]=gpr[6];
			storage[address+1]=gpr[5];
			return false;
		}
		else
		{
			return true;
		}
	}
	else
		return true;
}

bool sta(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int len=v[1].length();
		if(len == 4 )
		{
			int address=hex2dec(v[1]);
			if(address==-1)
					return true;
			storage[address]=gpr[0];
			return false;
		}
		else
		{
			return true;
		}
	}
	else
		return true;
}

bool stax(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int index=resister_is(v[1]);
		if(index == 1 || index == 3 || index == 5)
		{
			string temp="";
			temp=temp+dec2hex(gpr[index],2);
			temp=temp+dec2hex(gpr[index+1],2);
			int address=hex2dec(temp);
			if(address==-1)
				return true;
			storage[address]=gpr[0];
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}
