//Author:   Nick Seyler
//Date:     4/30/18
//File:     myshell.cpp

#include "mycommands.h"
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM 1000

int takeInput()
{
   mycommands c;                                   //create a mycommands object with the name c
   char str[MAXIMUM], temp[MAXIMUM];
   char *copy, *token, *command;
   char *arguments[MAXIMUM];
   int count = 0;
   
   printf("%s", "Enter a Command >> ");
   fgets(str, MAXIMUM, stdin);                     //take input and save it to str
   copy = strdup(str);                             //save str to copy
   
   while((token = strsep(&copy," ")) != NULL)      //separates input delimited by spaces
   {
      if(token[0] == '\"' && token[strlen(token)-1] != '\"') //if the token starts with " and does not end with "...
      {
         if (count == 0)
         {
            printf("%s\n", "Error: Commands do not start with \" in this simple shell");
            return 1;
         }
         
         strcpy(temp, token);                      //...copy the token into a temp string...
         while (token[strlen(token)-1] != '\"')    //do this if the next token still hasn't ended with "
         {
            if (token[strlen(token)-1] == '\n')    //if the token ended in a newline
            {
               token = strsep(&token,"\n");        //remove the newline
               if (token[strlen(token)-1] != '\"') //if the token still hasn't ended with "
               {
                  printf("%s\n", "Error: could not find closing \"");
                  return 1;
               }
               else
               {
               }
            }
            else
            {
               strcat(temp, " ");                     //...append whitespace to temp...
               token = strsep(&copy, " ");            //...get the next token...
               strcat(temp, token);                   //...append the token to temp...
               token = &temp[0];                      //...and set token to temp
            }
         }
      }
      token = strsep(&token,"\n");                 //remove newline character in order to pass input properly
      
      if (count == 0)
      {
         printf("Command Name: %s\n", token);
         command = token;                          //separates command from arguments
      }
      else
      {
         printf("Argument: %s\n", token);
         arguments[count-1] = token;               //puts arguments into an array
      }
      
      count++;                                     //increment input number
   }
                    
   if(strcmp(command, "exit") == 0)                
      return c.myexit();                           //call myexit() regardless of additional arguments
   else if (strcmp(command, "cat") == 0)
   {
      if (count != 2)                              
         printf("%s%s\n", command, " usage: cat filename");
      else
         c.mycat(arguments);                       //call mycat(char* arguments[])
   }
   else if (strcmp(command, "cp") == 0)
   {
      if (count != 3)
         printf("%s%s\n", command, " usage: cp filename1 filename2");
      else
         c.mycp(arguments);                        //call mycp(char* arguments[])
   }
   else if (strcmp(command, "ls") == 0)
   {
      if (count > 1)
         printf("%s%s\n", command, " usage: ls [NO ARGUMENTS]");
      else
         c.myls();                                 //call myls()
   }
   else if (strcmp(command, "grep") == 0)
   {
      if (count <= 2)
         printf("%s%s\n", command, " usage: grep string filename1 filename2 filename...");
      else
         c.mygrep(arguments, count-2);             //call mygrep(char* arguments[], amountoffiles)
   }
   else if (strcmp(command, "mkdir") == 0)
   {
      if (count != 2)
         printf("%s%s\n", command, " usage: mkdir directoryname");
      else
         c.mymkdir(arguments);                     //call mymkdir(char * arguments[])
   }
   else if (strcmp(command, "rmdir") == 0)
   {
      if (count != 2)
         printf("%s%s\n", command, " usage: rmdir directoryname");
      else
         c.myrmdir(arguments);                     //call myrmdir(char * arguments[])
   }
   else if (strcmp(command, "sleep") == 0)
   {
      if (count != 2)
         printf("%s%s\n", command, " usage: sleep time");
      else
         c.mysleep(arguments);                     //call mysleep(char * arguments[])
   }
   else if (strcmp(command, "diff") == 0)
   {
      if (count != 3)
         printf("%s%s\n", command, " usage: diff filename1 filename2");
      else
         c.mydiff(arguments);                      //call mydiff(char * arguments[])
   }
   else
      printf("'%s' is not a command.\n", command); //the command does not exist
   
   return 1;                                       //loop
}

int main()
{
   while (takeInput())                             //takeInput() returns 1 if the command is not exit and returns 0 if the command is exit
   {
   }
   return(0);
}