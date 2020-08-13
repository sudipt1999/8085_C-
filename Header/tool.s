#include "master.h"
#include "global.h"
#include "tools.h"
#include "arithmetic.h"
#include "branching.h"
#include "logical.h"
#include "load.h"

int program_counter[500];
int index_pc=0;
int size_pc=0;

void program_counter_increment(int temp_memory)
{
	program_counter[index_pc++]=temp_memory;							
	if(index_pc>size_pc)
		size_pc=index_pc;
}

string dec2hex(int n, int size)											//TOOLS.h
{
	string str="";
	if(n==0 && size==2)
		str="00";
	else if(n==0 && size==4)
		str="0000";
	else
	{
		while(n!=0)
		{
			int r=n%16;
			n=n/16;
			if(r>=0 && r<=9)
			{
				str=str+char(r+48);
			}
			else
			{
				switch(r)
				{
					case 10:str=str+'A';
						break;
					case 11:str=str+'B';
						break;
					case 12:str=str+'C';
						break;
					case 13:str=str+'D';
						break;
					case 14:str=str+'E';
						break;
					case 15:str=str+'F';
						break;
				}
			}
		}
		int i=str.length();
		for(int j=0;j<i/2;j++)
		{
			char temp=str[j];
			str[j]=str[i-j-1];
			str[i-j-1]=temp;
		}
		if(size == 2)
		{
			if( i == 2 )
				return str;
			else
			{
				str="0"+str;
            }
		}
		else if( size == 4 )
		{
			if( i == 4 )
				return str;
			else if(i == 3 )
			{
				str="0"+str;
			}
			else if(i == 2 )
			{
				str="00"+str;
			}
			else if(i == 1)
			{
				str="000"+str;
			}
		}
	}
	return str;
}
int hex2dec(string a)													// TOOLS.h
{														// hexdecimal validator missing
	int l=a.length(),i=0,dec=0,p=pow(16,l-1);
	while(i<l)
	{
		int temp;
		if(a[i]>=48 && a[i]<=57)
			temp=a[i]-48;
		else
		{
			switch(a[i])
			{
				case 'A':
				case 'a': temp=10;
					break;
				case 'B':
				case 'b': temp=11;
					break;
				case 'C':
				case 'c': temp=12;
					break;
				case 'D':
				case 'd': temp=13;
					break;
				case 'E':
				case 'e': temp=14;
					break;
				case 'F':
				case 'f': temp=15;
					break;
				default	:	return -1;
			}
		}
		dec=dec+p*temp;
		i++;
		p=p/16;
	}
	return dec;
}


string string_uppercase(string temp)
{
	int l=temp.length();
	char c;
	string s="";
	for(int i=0;i<l;i++)
	{
		c=toupper(temp[i]);
		s=s+c;
	}
	return s;
}


bitset<5> flag;					// | S | Z | AY | P | CY |

void set_flag_register(int result)
{
	bitset<8> name(result);                   //store our result in binay form
	if(result>255)								//to set carry flag
	{
		flag[0]=1;
	}
	else
	{
		flag[0]=0;
	}
	if(result<0)									//to set sign flag
	{
		flag[4]=1;
	}
	else
	{
		flag[4]=0;
	}
	int numberof1=name.count();					   //count no of 1
	if(numberof1%2==0)
	{
		flag[1]=1;
	}
	else
	{
		flag[1]=0;
	}
	int numberof0=8-numberof1;					   //count no 0
	if(numberof0==8)
	{
		flag[3]=1;
	}
	else
	{
		flag[3]=0;
	}		
}


vector<string> splitter(string temp)									// TOOLS.H
{
	vector<string>v;
	string var;
	string res(temp);
	const char *delimiter = " ,";
	char *str = (char *)res.c_str();;
	char *pch;
	pch = strtok(str,delimiter);
	while(pch!=NULL){
		var = pch;
		v.push_back(var);
		pch = strtok(NULL,delimiter);
	}
	return v;
}


map<string, int> opcode;	// FOR CHECK_OPCODE for the size of opcode

void initilize_map_opcode()
{
	opcode["STAX"]=1;
	opcode["SET"]=3;
	opcode["MOV"]=1;
	opcode["XCHG"]=1;
 	opcode["ADD"]=1;
	opcode["SUB"]=1;
	opcode["INR"]=1;
	opcode["DCR"]=1;
	opcode["INX"]=1;
	opcode["DCX"]=1;
	opcode["CMP"]=1;
	opcode["CMA"]=1;
	opcode["DAD"]=1;
	opcode["MVI"]=2;
	opcode["ADI"]=2;
	opcode["SUI"]=2;
	opcode["JNZ"]=3;
	opcode["JZ"]=3;
	opcode["LXI"]=3;
	opcode["JNC"]=3;
	opcode["JC"]=3;
	opcode["JMP"]=3;
	opcode["LHLD"]=3;
	opcode["SHLD"]=3;
	opcode["STA"]=3;
	opcode["LDA"]=3;
	opcode["HLT"]=-2;
}


int check_opcode(string key)
{
	if (opcode.find(key) == opcode.end())
		return -1;
	else
		return opcode[key];
}


map<int,string> memory;		

int check_memory(int key)
{
	if (memory.find(key) == memory.end())
		return -1;
	else
		return key;
}

int resister_is(string temp)
{
	if(temp=="M")								// | A | B | C | D | E | H | L | M | *  |
		return 7;								// | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | -1 |
	else if(temp=="A")
		return 0;
	else if(temp=="B")
		return 1;
	else if(temp=="C")
		return 2;
	else if(temp=="D")
		return 3;
	else if(temp=="E")
		return 4;
	else if(temp=="H")
		return 5;
	else if(temp=="L")
		return 6;
	else
		return -1;
}

map<int,int> storage;

int check_storage(int key)			//		30.7.17
{
	if (storage.find(key) == storage.end())
		return -1;
	else
		return storage[key];
}

int gpr[7];				 	

int rpair(int start)						//		30.7.17
{
	string temp="";
	temp=temp+dec2hex(gpr[start],2);
	temp=temp+dec2hex(gpr[start+1],2);
	return hex2dec(temp);
}

bool set1(string temp_string)							
{
	vector<string> v;
	v=splitter(temp_string);
	int size=v.size();
	if(size==3)
	{
		int len=v[1].length();
		int len2=v[2].length();
		if (len == 4 && len2 == 2)
		{
			len=hex2dec(v[1]);
			len2=hex2dec(v[2]);
			if(len==-1 || len2==-1)
				return true;
			storage[len]=len2;
			return false;
		}
		else
			return true;
	}
	else
		return true;
}

bool check_function(string instruction)
{
    vector<string> v;
    v=splitter(instruction);
    if(v[0]=="MOV")
    {
        return mov(instruction);
    }
    else if(v[0]=="MVI")
    {
		return mvi(instruction);
    }
    else if(v[0]=="LXI")
    {
        return lxi(instruction);
    }
    else if(v[0]=="LDA")
    {
        return lda(instruction);
    }
    else if(v[0]=="STA")
    {
        return sta(instruction);
    }
    else if(v[0]=="SHLD")
    {
        return shld(instruction);
    }
    else if(v[0]=="LHLD")
    {
        return lhld(instruction);
    }
    else if(v[0]=="STAX")
    {
        return stax(instruction);
    }
    else if(v[0]=="XCHG")
    {
        return xchg(instruction);
    }
    else if(v[0]=="ADD")
    {
        return add(instruction);
    }
    else if(v[0]=="ADI")
    {
        return adi(instruction);
    }
    else if(v[0]=="SUB")
    {
        return sub(instruction);
    }
    else if(v[0]=="INR")
    {
        return inr(instruction);
    }
    else if(v[0]=="DCR")
    {
        return dcr(instruction);
    }
    else if(v[0]=="INX")
    {
        return inx(instruction);
    }
    else if(v[0]=="DCX")
    {
        return dcx(instruction);
    }
    else if(v[0]=="DAD")
    {
        return dad(instruction);
    }
    else if(v[0]=="SUI")
    {
        return sui(instruction);
    }
    else if(v[0]=="CMA")
    {
        return cma(instruction);
    }
    else if(v[0]=="CMP")
    {
        return cmp(instruction);
    }
    else if(v[0]=="JMP")
    {
        return jmp(instruction);
    }
    else if(v[0]=="JC")
    {
        return jc(instruction);
    }
    else if(v[0]=="JNZ")
    {
        return jnz(instruction);
    }
    else if(v[0]=="JZ")
    {
        return jz(instruction);
    }
    else if(v[0]=="JNC")
    {
        return jnc(instruction);
    }
    else if(v[0]=="HLT")
    {
		return false;
	}
	else if(v[0]=="SET")
		return set1(instruction);
	else 
		return true;
}

bool does_file_exist(const char *fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

void execution()
{
	 index_pc=0;
     while(index_pc<size_pc)
     {
           string function1=memory[program_counter[index_pc]];	
           bool check=check_function(function1);
           if(index_pc>size_pc)
		   {
				cout<<"Invalid memory location"<<endl;
		   }
           if(check)
           {
                   cout<<"*** SYNTAX ERROR at Line Number "<<index_pc<<" -> "<<function1<<" ***"<<endl;
                   break;
           }
           index_pc++;
      }
       for(int i=0;i<7;i++)
       {
			cout<<dec2hex(gpr[i],2)<<" ";
	   }
	   cout<<endl;
}

bool input_file(char *arg)
{
	bool termination_flag=false;
	ifstream input;
	input.open(arg);
	string temp_string;
	int start_memory,memory_address;
	input>>temp_string;
	start_memory=hex2dec(temp_string);								//STARTING ADDRESS
	if(start_memory==-1)
	{
		cout<<"***ERROR: Invalid Memory Address ***"<<endl;
		termination_flag=true;
	}
	else
	{
		memory_address=start_memory;
		input.ignore();
	}
	while(!termination_flag)
	{
		getline(input,temp_string);
		temp_string=string_uppercase(temp_string);
		program_counter_increment(memory_address);
		memory[memory_address]=temp_string;
		vector<string> v;
		string temp(temp_string);
		v = splitter(temp);											// To Split the string into parts
		int size=check_opcode(v[0]); 								// To fetch Size of OPCODE
		if(size==-1)
		{
			cout<<"*** ERROR: INVALID 8085 COMMAND. ***\nTerminating Program..."<<endl;							// ERROR STATEMENT
			termination_flag=true;
			break;
		}
		else if(size==-2) 											// RETURN -2 for HLT
		{
			break;
		}
		else
		{
			memory_address += size;
		}
		temp_string="";
	}
	input.close();
	return termination_flag;
}

bool input()
{
	bool termination_flag=false;
	string temp_string;
	int start_memory,memory_address;
	cout<<"Enter starting Memory Address in Hexdecimal: ";
	cin>>temp_string;
	start_memory=hex2dec(temp_string);								//STARTING ADDRESS
	if(start_memory==-1)
	{
		cout<<"***ERROR: Invalid Memory Address ***"<<endl;
		termination_flag=true;
	}
	else
	{
		memory_address=start_memory;
		cout<<"Enter Assembly language code below"<<endl;
		cin.ignore();
	}
	while(!termination_flag)
	{
		cout<<dec2hex(memory_address,4)<<" >> ";
		getline(cin,temp_string);
		temp_string=string_uppercase(temp_string);
		program_counter_increment(memory_address);
		memory[memory_address]=temp_string;
		vector<string> v;
		string temp(temp_string);
		v = splitter(temp);											// To Split the string into parts
		int size=check_opcode(v[0]); 								// To fetch Size of OPCODE
		if(size==-1)
		{
			cout<<"*** ERROR: INVALID 8085 COMMAND. ***\nTerminating Program..."<<endl;							// ERROR STATEMENT
			termination_flag=true;
			break;
		}
		else if(size==-2) 											// RETURN -2 for HLT
		{
			break;
		}
		else
		{
			memory_address += size;
		}
		temp_string="";
	}
	return termination_flag;
}
