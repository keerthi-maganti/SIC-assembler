#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include "symtable1.h"
//#include "Hash.h"

using namespace std;

hashing begin()
{
	ifstream fp("input");
	ofstream fw;
	fw.open("OPCODE_TABLE");															//Open the file that contains all the opcodes
    hashing obj;																		//Create object of class hashing
	string line;																		//line stores the string in each line taken from the file
	string word;																		//word stores the words in each line
	if (fp.is_open())
	{
    	while (getline (fp,line) )
    	{
      		istringstream iss(line);													//recognizes space or newline character
      		while(iss >> word)															//exctract the word from the line and store it in 'word'
            {   obj.insert(word);														//Insert the word into the opcode table
//            	cout<<word<<endl;
            }
        }
    }
    for(int i=0; i<49; i++)
    	for(int j=0; j<3; j++)
    	{	
//    		cout<<"index:\t"<<i<<"\t"<<obj.opcodeTable[i][j]<<endl;
    		fw << obj.opcodeTable[i][j] << '\n';										//for further use, write the opcode table into a file
    	}

 //   cout<<"Insertion successful\n";
    	return obj;
}

int main()
{
	hashing obj;								 //Class-hashing defined in "Hash.h". Object of type hashing is declared.
	obj = begin();                               //This function defined in "Hash.h" creates the opcode table for further use.
	ofstream rec("IntermediateRecord.txt");		 //Output file to store program name, starting address and code length
	ifstream fp("inst.sic");                     //Input file that has assemly code.
	ofstream fo("Intermediate.txt");             //Output file that will have LOCCTR values for each instruction.
	int locCntr = 0;                             //Integer variable that holds present location counter value.
  	int codeLength = 0;                          //Varibale that holds length of the program.
	string line;                                 //String variable that holds the currently extracted line. 
	string word;                                 //String variable that holds the currently extracted word from the line.
	int startAddr;                               //Variable that holds the starting address of the assembly code.
  	string progName;							 //String variable that holds the name of the program
  	int error;									 //Error flag.
  	int startFlag = 0;							 //Flag that checks if the line is the first line.
  	int wordCount = 1;							 //Integer variable that keeps track of word-index in a line.
  	int prevLoc;
  	int flag = 0;
//  	init();
//If the inout file is open, do:
	if (fp.is_open())
	{
//Get line from file pointed to by fp(which is "inst.sic") and store it in the string variable-line.    
 		while (getline (fp,line, '\n') )
		{
			istringstream iss(line);					//tokenizes the line. iss is the pointer to the words.
//If the line has the assembler directive - "START",
			if(line.find("START") && startFlag == 0)
			{
				startFlag = 1;							//First line is read. Set startFlag  to 1.
				int loopCounter = 0;					//Reading first word in the first line.
				while(iss >> word)						//Extract each word from iss and put it to variable word
				{
/* Checks for the no. of words in the starting line. If there are only two words, it implies that starting address is not defined. */
					if (loopCounter == 0)
					{
						progName = word;
						loopCounter++;
					}
					else if (loopCounter == 1)
					{
						loopCounter++;
					}
					else if (loopCounter == 2)
					{
						loopCounter++;
						stringstream ss(word);
						ss >> hex >> startAddr;
					}
				}
/* If there is not third word in the first line, initialize startAddr to zero. */ 
				if (loopCounter == 2)
					startAddr = 0;
/* Initialze location counter to the starting address obtained. */
				locCntr = startAddr;
				fo << hex << locCntr << "   " << line << "\n";
				continue;
			}
/*If line is not the starting line, do */
			else
			{
				wordCount = 1;				//Initialize wordCount to 1 everytime a new line is extracted.
				prevLoc = locCntr;			//Assign prevLoc with the value of current locCntr.

				while(iss >> word)			//Extract each word from iss and put it to variable word
				{	
					if(word == "END")
					{
						flag = 1;
						break;
					}
					if(wordCount == 2 && word  != "END")
					{
						if(obj.found(word));
						else if(word == "RESW")
						{
				        	iss >> word;
				        	wordCount++;
				        	const char* val = word.c_str();
							locCntr += 3 * atoi(val);
							continue;
			        	}

						else if(word == "RESB")
						{
			    	    	iss >> word;
			    	    	wordCount++;
							locCntr += stoi(word);
							continue;
			        	}

						else if(word == "BYTE")
						{
					  		iss >> word;
					  		wordCount++;
							if(word.at(0) == 'C')
								locCntr += word.length() - 3;
							else
								locCntr++;
							continue;
			        	}
						else if(word == "WORD")
						{	
							iss >> word;
							wordCount++;
							locCntr += 3;
			          		continue;
			        	}
			        	else
			        		locCntr += 3;
					}

					if(wordCount == 1 && word != "END")
					{
						if(!SearchSym(word))
						{
							if(obj.found(word) == false)
							{
								InsertSym(word, locCntr);
							}
						}
						else
							error = 1;
					}

					wordCount++;
				}
				if(word == "END" || flag == 1)
				{
					fo << "         " << line << "\n";
					break;
				}
//				if(!flag)
				else
					fo << hex << prevLoc << "   " << line << "\n";
			}
        }
    }
    DisplaySym();
//    cout<<hex<<locCntr<<endl;
    cout<< "\n\nProgram name:\t" << progName << endl;
//    rec << progName << endl;
    cout<< "Starting address:"<< hex << startAddr << endl;
//    rec << hex << startAddr << endl;
	codeLength = locCntr - startAddr;
	cout << "Program length:\t  "<< hex << codeLength << endl << endl;
	rec << progName << "\t" << hex << startAddr << "\t" << hex << codeLength << endl;
}