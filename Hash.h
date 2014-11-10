#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
//#include "symtable1.h"
//#include "testSymtab.h"
//#include <boost/lexical_cast.hpp>

using namespace std;

class hashing
{
public:
	string opcodeTable[49][3];
public:
	hashing()
    {
		for(int i=0; i<49; i++)
            for(int j=0; j<3; j++)
            {
                opcodeTable[i][j] = '0';
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
				
        //cout<<"done"<<opcodeTable[index][i]<<endl;
		        break;
			}
		}
	}

	int found(string word)
	{
		int index,foundFlag=0;
		index = hash(word);
		for(int i=0; i<3; i++)
    	{
    		if(word == "LDA")
    			cout<<index<<endl;
//      cout<<opcodeTable[index][i]<<" "<<i;
    		if(opcodeTable[index][i].compare(word) == 0)
    		{	
//    			cout<<opcodeTable[index][i]<<endl;
//					foundFlag=1;
    			return 1;
			}
		}
//    if(foundFlag)
 //     return 1;
  //  else
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