#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include "symtable1.h"
#include "Hash.h"

using namespace std;

hashing begin()
{
	ifstream fp("input");
	ofstream fw;
	fw.open("OPCODE_TABLE");											 //Open the file that contains all the opcodes
    hashing obj;														 //Create object of class hashing
	string line;														 //line stores the string in each line taken from the file
	string word;														 //word stores the words in each line
	string mnemo;
	if (fp.is_open())
	{
    	while (getline (fp,line) )
    	{
      		istringstream iss(line);									 //recognizes space or newline character
      		if(iss >> word)												 //exctract the word from the line and store it in 'word'
            {   obj.insert(word);
            	mnemo = word;
            	iss >> word;
            	obj.insertOpcode(word, mnemo);							//Insert the word into the opcode table
            }
        }
    }
//for further use, write the opcode table into a file
    for(int i=0; i<49; i++)
    	for(int j=0; j<3; j++)
    	{	
    		fw << obj.opcodeTable[i][j] << "\t"<< obj.opCode[i][j]<<'\n';
    	}
    	return obj;
}


void DisplaySym()
{
    int i;
    struct stab *p;
    p = first;
    ofstream f("SYMTAB.txt");
    f << "\n\t\t\tLABEL\t\t\tADDRESS\n";
    for(i=0; i<size; i++)
    {
      f << p->label <<"    "<< hex << p->addr << endl;
//      cout<<"\n\t\t\t"<<p->label<<"\t\t\t"<<p->addr<<endl;
      p=p->next;
    }
    f.close();
}


int main()
{
	hashing obj;							 //Class-hashing defined in "Hash.h". Object of type hashing is declared.
	obj = begin();                           //This function defined in "Hash.h" creates the opcode table for further use.
	ofstream rec("IntermediateRecord.txt");	 //Output file to store program name, starting address and code length
	ifstream fp("inst.sic");                 //Input file that has assemly code.
	ofstream fo("Intermediate.txt");         //Output file that will have LOCCTR values for each instruction.
	int locCntr = 0;                         //Integer variable that holds present location counter value.
  	int codeLength = 0;                      //Varibale that holds length of the program.
	string line;                             //String variable that holds the currently extracted line. 
	string word;                             //String variable that holds the currently extracted word from the line.
	int startAddr;                           //Variable that holds the starting address of the assembly code.
  	string progName;						 //String variable that holds the name of the program
  	int error=2;								 //Error flag.
  	int startFlag = 0;						 //Flag that checks if the line is the first line.
  	int wordCount = 1;						 //Integer variable that keeps track of word-index in a line.
  	int prevLoc;							 //Integer variable that holds the value of previous locCntr value.
  	int flag = 0;							 //Flag that checks if the line has the assembler disrective END - line 111.
//If the inout file is open, do:
	if (fp.is_open())
	{
//Get line from file pointed to by fp(which is "inst.sic") and store it in the string variable-line.    
 		while (getline (fp,line, '\n') )
		{
//			error = 2;
			istringstream iss(line);					//tokenizes the line. iss is the pointer to the words.
//If the line has the assembler directive - "START",
			if(line.find("START") && startFlag == 0)
			{
//				error = 0;
				startFlag = 1;							//First line is read. Set startFlag  to 1.
				int loopCounter = 0;					//Reading first word in the first line.
				while(iss >> word)						//Extract each word from iss and put it to variable word
				{
/* Checks for the no. of words in the starting line. If there are only two words, it implies that starting address is not defined. */
					if(!word.compare("START"))
					{
						error = 0;
					}
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
/* If there is no third word in the first line, initialize startAddr to zero. */ 
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
//				error = 2;
				wordCount = 1;				//Initialize wordCount to 1 everytime a new line is extracted.
				prevLoc = locCntr;			//Assign prevLoc with the value of current locCntr.

				while(iss >> word)			//Extract each word from iss and put it to variable word
				{
//If word is END, set flag to 1 since locCntr should not be written to file when line has the assemlber directive END 	

					if(word == "END")
					{
						flag = 1;
//						error = 0;
//						continue;
					}
//When the extracted word is the second word in the current, line, do
					if(wordCount == 2)
					{
//						if(obj.found(word));	//word is a mnemonic. Do nothing.
						 if(word == "RESW")
						{
				        	iss >> word;	//Extract the next word that has the number of words to be allocated
				        	wordCount++;	//Increment the wordCount
				        	const char* val = word.c_str();	//Converts string to cstring since cstring is supported by the function atoi.
							locCntr += 3 * atoi(val);	//atoi converts ASCII value to integer.
							error = 0;
//							continue;
			        	}

						else if(word == "RESB")
						{
			    	    	iss >> word;	//Extract the next word that has the number of bytes to be allocated
			    	    	wordCount++;	//Increment the wordCount
							//locCntr += stoi(word);
							locCntr +=  strtoul(word.c_str(), NULL, 10);
							error = 0;
//							continue;
			        	}

						else if(word == "BYTE")
						{
					  		iss >> word;	//Extract the next word to check whether it is a character constant or hexadecimal constant.
					  		wordCount++;	//Increment the wordCount
							if(word.at(0) == 'C')
								locCntr += word.length() - 3;
							else
								locCntr++;
							error = 0;
//							continue;
			        	}
						else if(word == "WORD")
						{	
							iss >> word;
							wordCount++;
							locCntr += 3;
							error = 0;
//			          		continue;
			        	}
			        	else
			        	{	locCntr += 3;
//			        		continue;
			        	}
					}
//					error = 2;
//If the word is the first word of the line, it is either a label or a mnemonic and hence do
					if(wordCount == 1 && word != "END")
					{
/*Is the word already present in the symbol table? 
If yes, set error flag to 1 that corresponds to duplicate symbol error.
If no, check if the word is a mnemonic. If not, insert the symbol into the symbol table. */ 
						if(!SearchSym(word))
						{
							if(obj.found(word) == false)
							{
								InsertSym(word, locCntr);
								error = 0;
							}
						}
						else
							error = 1;
					}
					wordCount++;
				}
				if(word == "END" || flag == 1)
				{
//					error = 0;
					fo << "         " << line << "\n";
					break;
				}
				else
					fo << hex << prevLoc << "   " << line << "\n";
			}
        }
    }
    DisplaySym();		//Creates the file, "SYMTAB.txt"
    switch(error)
    {
    	case 0 : cout<< "\n\nProgram name:\t" << progName << endl;
			     cout<< "Starting address:"<< hex << startAddr << endl;
			     codeLength = locCntr - startAddr;
				 cout << "Program length:\t  "<< hex << codeLength << endl << endl;
				 rec << progName << "\t" << hex << startAddr << "\t" << hex << codeLength << endl;
				 cout<<"Pass-1 complete. Check files - 'Intermediate.txt', 'IntermediateRecord.txt', 'SYMTAB.txt'\n"<<endl;
				 break;
		case 1 : cout<<"Duplicate symbol not allowed\n";
				 exit(0);
		case 2 : cout<<"Invalid keyword\n";
				 exit(0);
	}
}