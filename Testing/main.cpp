#include "master.h"
#include "global.h"
#include "tools.h"
#include "Arithematic.h"
#include "Branching.h"
#include "Load.h"
#include "Logical.h"
int main(int argc, char *argv[])
{
	initilize_map_opcode();												
	if(argc==1) 													
	{
		bool termination_flag=false;
		termination_flag=input();
		if(!termination_flag)
		{
			index_pc=0;
			execution();
		}
		else
		{
			cout<<"*** ERROR: Invalid Input ***"<<endl;								
		}
	}
	else if (argc==2) 
	{
		string arg2(argv[1]);
		if(string_uppercase(arg2)=="--DEBUGGER")			
		{
			bool termination_flag=false;
			termination_flag=input();
			if(!termination_flag)
			{
				//DEBUGGER FUNCTIONALITY
				index_pc=0;
				this_is_debugger();
			}
			else
			{
				cout<<"*** ERROR: Invalid Input. ***"<<endl;							
			}
		}
		else // FILE HANDELING W/O DEBUGGER // *** CHECK BLANK FILE AND SET EOF CONDITION ***
		{
			if(does_file_exist(argv[1])) 
			{
				bool termination_flag=false;
				termination_flag=input_file(argv[1]);
				if(!termination_flag)
				{
					index_pc=0;
                    execution();                      
				}
				else
				{
					cout<<"*** ERROR: Invalid Input. ***"<<endl;							
				}
			}
			else
			{
				cout<<"*** ERROR: Invalid File. File does not exist. ***"<<endl;
			}
		}
	}
	else if ( argc==3 ) // FILE HANDELING WITH DEBUGGER
	{
		string arg3=argv[2];
		if(string_uppercase(arg3)=="--DEBUGGER")
		{
			if(does_file_exist(argv[1])) 
			{
				bool termination_flag=false;
				termination_flag=input_file(argv[1]);
				if(!termination_flag)
				{
					index_pc=0;
                    this_is_debugger();
				}
				else
				{
					cout<<"*** ERROR: Invalid Input. ***"<<endl;								
				}
			}
			else
			{
				cout<<"*** ERROR: Invalid File. File does not exist. ***"<<endl;
			}
		}
		else
		{
			cout<<"*** ERROR: Invalid Argument Format. ***\n Valid Format: [<Exectable File> <Input File> <--debugger>]"<<endl;
		}
	}
	else
	{
		cout<<"*** ERROR: Invalid Number of Arguments ***"<<endl;
	}
	cout<<"\t*** THE END ***"<<endl;
	return 0;
}
