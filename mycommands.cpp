#include "mycommands.h"
#include <sys/types.h> 
#include <sys/stat.h>
#include <dirent.h> 
#include <fcntl.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5000

mycommands::mycommands ()
{
}

int mycommands::myexit()
{
   printf("%s\n", "Exiting Shell");
   return 0;
}

void mycommands::mycat(char *arguments[])
{
   char buf[MAX];
   FILE *fp;
   DIR *dir = opendir(arguments[0]);

   if(dir)                                     //check if dir exists
   {
      printf("%s%s\n", arguments[0], "is a directory");
      closedir(dir);
   }
   else
   {
      if(access(arguments[0], F_OK)!= -1)      //check if file exists
      {
	     fp=fopen (arguments[0], "r+");
	     while(fgets(buf, MAX, fp))
            fputs(buf, stdout);
         fclose(fp);
      }
      else
         printf("%s%s%s\n", "cat: ", arguments[0], ": no such file or directory");
   }
}

void mycommands::mycp(char *arguments[])
{
   char buf[MAX];
   FILE *fp1;
   FILE *fp2;
   if (access(arguments[0], F_OK) != -1)        //check if file exists
   {
      fp1=fopen (arguments[0], "r+");
      fp2=fopen (arguments[1], "w+");
      
      while(fgets(buf, MAX, fp1))
         fputs(buf, fp2);                       //put the contents of fp1 into fp2
      fclose(fp1);
      fclose(fp2);
   }
   else
      printf("%s%s%s\n", "fp: ", arguments[0], ": file does not exist");
}

void mycommands::myls()
{
   char buf[MAX];
   DIR *dir = opendir(getcwd(buf, MAX));
   struct dirent *d;
   
   d = readdir(dir);                            //remove . from results
   d = readdir(dir);                            //remove .. from results
   
   while ((d = readdir(dir)) != NULL)
      printf("%s\n", d->d_name);
}

void mycommands::mygrep(char* arguments[], int filecount)
{
   char buf[MAX];
   char string[MAX];
   FILE *fp;
   char* ret;
   
   if (arguments[0][0] == '\"' && arguments[0][strlen(arguments[0])-1] == '\"')  //checks if the string to search contains quotes
   {
      strncpy(string, arguments[0], strlen(arguments[0])-1);                     //removes the quotation marks
      memmove(string, string+1, strlen(string));
      for (int i = 0; i<filecount; i++)                                          //searches every file line by line and outputs the results
      {
         if (access(arguments[i+1], F_OK) != -1)
         {
            fp=fopen(arguments[i+1], "r+");
            while (fgets(buf, MAX, fp) != NULL)
               if(strstr(buf, string))
                  fputs(buf, stdout);
              
            fclose(fp);
         }
         else
            printf("%s%s%s\n", "grep: ", arguments[i+1], ": file does not exist");
      }

   }
   else
      printf("%s\n", "string argument must be enclosed in '\"'");
}
//***NEW***//
void mycommands::mymkdir(char * arguments[])
{
   char buf[MAX];
   struct stat st = {0};
   
   if (getcwd(buf, MAX) != NULL)
   {
      strcat(buf, "/");
      strcat(buf, arguments[0]);
      if (stat(buf, &st) == -1)     //if directory does not exist
         mkdir(buf, 0700);
      else
         printf("%s\n", "directory already exists");
   }  
}

void mycommands::myrmdir(char * arguments[])
{
   char buf[MAX];
   struct stat st = {0};
   
   if(getcwd(buf, MAX) != NULL)
   {
      strcat(buf, "/");
      strcat(buf, arguments[0]);
      if (stat(buf, &st) == -1)     //if directory does not exist
         printf("%s\n", "directory does not exist");
      else
      {
         DIR *dir = opendir(buf);
         struct dirent *d;
         int n = 0;
         while ((d = readdir(dir)) != NULL) {
            n++;
         }
         closedir(dir);
         if (n > 2)
            printf("%s\n", "directory is not empty");
         else
            rmdir(buf);
      }
   }
}

void mycommands::mysleep(char * arguments[])
{
   int num = atoi(arguments[0]);
   sleep(num);
}

void mycommands::mydiff(char* arguments[])
{
   char buf[MAX], buf2[MAX];
   FILE *fp1;
   FILE *fp2;
   
   if (access(arguments[0], F_OK) != -1)        //check if file exists
      if(access(arguments[1], F_OK) != -1)
      {
         fp1=fopen (arguments[0], "r+");
         fp2=fopen (arguments[1], "r+");
         while (fgets(buf, MAX, fp1) != NULL && fgets(buf2, MAX, fp2) != NULL) {
            if (strcmp (buf, buf2) != 0)        //check if buffers are equal
            {
               strtok(buf, "\n");              
               strtok(buf2, "\n");              //remove newline character
               printf("%s%s\n", "<", buf);
               printf("%s\n", "---");
               printf("%s%s\n\n", ">", buf2);
            }
         }
         fclose(fp1);
         fclose(fp2);
      }
      else
         printf("%s%s%s\n", "diff: ", arguments[1], ": file does not exist");
   else
      printf("%s%s%s\n", "diff: ", arguments[0], ": file does not exist");
}