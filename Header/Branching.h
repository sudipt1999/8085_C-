#include "master.h"
#include "global.h"
#include "tools.h"

bool jc(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		if(flag[0]==1)
		{
			int address=hex2dec(v[1]);
			if(address==-1)
				return true;
			bool is_there=false;
			for(int i=0;i<size_pc;i++)
			{
				if(program_counter[i]==address)
				{
					is_there=true;
					index_pc=i-1;
					return false;
				}
			}
			if(!is_there)
			{
				return true;
			}
		}
		else
			return false;
	}
		return true;
}

bool jmp(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		int address=hex2dec(v[1]);
		if(address==-1)
			return true;
		bool is_there=false;
		for(int i=0;i<size_pc;i++)
		{
			if(program_counter[i]==address)
			{
				is_there=true;
				index_pc=i-1;
				return false;
			}
		}
		if(!is_there)
		{
			return true;
		}
	}
	return true;
}

bool jnc(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		if(flag[0]==0)
		{
			int address=hex2dec(v[1]);
			if(address==-1)
					return true;
			bool is_there=false;
			for(int i=0;i<size_pc;i++)
			{
				if(program_counter[i]==address)
				{
					is_there=true;
					index_pc=i-1;
					return false;
				}
			}
			if(!is_there)
			{
				return true;
			}
		}
		else
			return false;
	}
		return true;
}

bool jnz(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		if(flag[3]==0)
		{
			int address=hex2dec(v[1]);
			if(address==-1)
				return true;
			bool is_there=false;
			for(int i=0;i<size_pc;i++)
			{
				if(program_counter[i]==address)
				{
					is_there=true;
					index_pc=i-1;
					return false;
				}
			}
			if(!is_there)
			{
				return true;
			}
		}
		else
			return false;
	}
	return true;
}

bool jz(string temp_string)
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==2)
	{
		if(flag[3]==1)
		{
			int address=hex2dec(v[1]);
			if(address==-1)
				return true;
			bool is_there=false;
			for(int i=0;i<size_pc;i++)
			{
				if(program_counter[i]==address)
				{
					is_there=true;
					index_pc=i-1;
					return false;
				}
			}
			if(!is_there)
			{
				return true;
			}
		}
		else
			return false;
	}
		return true;
}
