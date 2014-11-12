#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <sstream>

using namespace std;

//Given the opcode and the target address, object code is calculated as follows
//1.Convert opcode to it's binary equivalent
//2.If there is "X", then, target address = target address + (X)
char convertToHex(int w)
{
	w = w - 48 + 8;
	switch(w)
	{
		case 10: return 'A';
		case 11: return 'B';
		case 12: return 'C';
		case 13: return 'D';
		case 14: return 'E';
		case 15: return 'F';
		default: return char(w + 48);
	}
}

string findObjCode(string opcode, string targetAddr, string line)
{
	string objCode;
	int target;
	int x;
	char w;
	objCode = opcode + targetAddr;
	if(!line.find(",X"))
	{
		w = objCode[2];
		w = convertToHex(w);
		objCode[2] = w;
		cout<<"In if obj \n";
	}
	return objCode;
}
