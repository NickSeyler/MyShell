//Author:   Nick Seyler
//Date:     4/30/18
//File:     mycommands.h

#ifndef MYCOMMANDS_H
#define MYCOMMANDS_H


class mycommands
{
public:
   mycommands();
   //constructor
   
   int myexit();
   //exit the shell
   
   void mycat(char *[]);
   
   void mycp(char *[]);
   
   void myls();
   
   void mygrep(char *[], int);
//***NEW***//
   void mymkdir(char *[]);
      
   void myrmdir(char *[]);   
   
   void mysleep(char *[]);
      
   void mydiff(char *[]);
};

#endif