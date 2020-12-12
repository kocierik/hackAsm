#include "instruction.h"

void removeSpace(char *line){
      int i=0;
      while(line[i]!='\0')
      {
          if(line[i]==' '||line[i]=='\n'||line[i]=='\t'||line[i]=='\r'){
              int j=i;
              while(line[j]!='\0'){
                  line[j]=line[j+1];
                  j++;
              }
          } else i++;
      }
}

void checkComment(char *line){
    int i=0;
    while (line[i]!='\0')
    {
        if(line[i]=='/' && line[i+1]=='/') line[i]='\0';
        else i++;
    }
}