#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class hashing
{
public:
	string opcodeTable[49][3];	//Array of strings storing MNEMONICS
	string opCode[49][3];		//Array of strings storing corresponding OPCODES
public:
//Constructor to initialize the tables to zero
	hashing()
    {
		for(int i=0; i<49; i++)
            for(int j=0; j<3; j++)
            {
                opcodeTable[i][j] = '0';
                opCode[i][j] = '0';
            }
	}
	int hash(string word)
	{
		int index=0;
        int k = 1;
		for(int i=0; i<word.length(); i++)
		{
			index += k * word[i];
		    k += 1;    
        }
		index = index%49;
		return index;
	}

	void insert(string word)
	{
		int index;
		index = hash(word);
		int i=0;
		for(i=0; i<3; i++)
		{
			if(!(opcodeTable[index][i].compare("0")))
			{
				opcodeTable[index][i] = word;
		        break;
			}
		}
	}

	void insertOpcode(string word, string mnemo)
	{
		int index;
		index = hash(mnemo);
		int i=0;
		for(i=0; i<3; i++)
		{
			if(!(opCode[index][i].compare("0")))
			{
				opCode[index][i] = word;
		        break;
			}
		}
	}

	string getOpCode(string mnemo)
	{
		int index;
		index = hash(mnemo);
		for(int i=0; i<3; i++)
    	{
    		if(opcodeTable[index][i].compare(mnemo) == 0)
    			return opCode[index][i];
		}
		return 0;		
	}
	int found(string word)
	{
		int index,foundFlag=0;
		index = hash(word);
		for(int i=0; i<3; i++)
    	{
    		if(opcodeTable[index][i].compare(word) == 0)
    			return 1;
		}
		return 0;
	}
};

//Function - begin() includes creating opcode table.
// void begin()
// {
// 	ifstream fp("input");
// 	ofstream fw;
// 	fw.open("OPCODE_TABLE");															//Open the file that contains all the opcodes
//     hashing obj;																		//Create object of class hashing
// 	string line;																		//line stores the string in each line taken from the file
// 	string word;																		//word stores the words in each line
// 	if (fp.is_open())
// 	{
//     	while (getline (fp,line) )
//     	{
//       		istringstream iss(line);													//recognizes space or newline character
//       		while(iss >> word)															//exctract the word from the line and store it in 'word'
//             {   obj.insert(word);														//Insert the word into the opcode table
// //            	cout<<word<<endl;
//             }
//         }
//     }
//     for(int i=0; i<49; i++)
//     	for(int j=0; j<3; j++)
//     	{	
// //    		cout<<"index:\t"<<i<<"\t"<<obj.opcodeTable[i][j]<<endl;
//     		fw << obj.opcodeTable[i][j] << '\n';										//for further use, write the opcode table into a file
//     	}

//  //   cout<<"Insertion successful\n";

// }