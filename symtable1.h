#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include "Hash.h"

 using namespace std;


int size=0;
void DisplaySym();
void InsertSym();

struct stab
{
    string label;
    int addr;
    struct stab *next;
};
    
struct stab *last, *first;

void InsertSym(string l,  int LOCCTR)
{
    int n;
    struct stab *p;
    p = new stab;
    p->label = l;
    p->addr = LOCCTR;
    p->next=NULL;
    if(size==0)
    {
      first=p;
      last=p;
    }
    else
    {
      last->next=p;
      last=p;
    }
    size++;
}

void DisplaySym()
{
  int i;
  struct stab *p;
  p=first;
  ofstream f("SYMTAB.txt");
  cout<<"\n\t\t\tLABEL\t\t\tADDRESS\n";
    for(i=0;i<size;i++)
   {
      f << p->label <<"    "<< hex << p->addr << endl;
      cout<<"\n\t\t\t"<<p->label<<"\t\t\t"<<p->addr<<endl;
      p=p->next;
  }
  f.close();
}

bool SearchSym(string lab)
{
 int i,flag=0;
 struct stab *p;
 p=first;
  for(i=0;i<size;i++)
   {
    if(p->label == lab)
     flag=1;
    p=p->next;
   }
 return flag;
}

// void init()
// {
//     fstream f;
//     f.open("SYMTAB.txt", std::fstream::app);
// }