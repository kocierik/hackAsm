#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "whitespace.h"
#include "instruction.h"

int main(int argc, char **argv) {
    FILE *fin, *fOut,*fin2;
        fin=fopen(argv[1],"r");
        int str_len= strlen(argv[1])+1,k=0;
        char nome[str_len];
        strncpy(nome,argv[1],str_len);
        for (int i = 0; i < str_len; i++) 
        {
            if(nome[i]=='.'){
                nome[i+1]='\0';
                strcat(nome,"hack");
                i=str_len;
            }
        }
        fin2=fopen(argv[1],"r");
        struct simTable* table=define();
        char riga[128]; 
        int scarto=1, numberline=0;
        while (!feof(fin2)) 
        {
          fgets(riga,128,fin2);
          removeSpace(riga);
          checkComment(riga);
          if(riga[0]!='\n' && riga[0]!='\0' && riga[0]!='\t' && riga[0]!='\r'){
          numberline++;
            if(riga[0]=='('){
              int q=0;
              while(riga[q]!='\0'){
                riga[q]=riga[q+1];
                q++;
              }
              k=0;
              while (riga[k]!='\0')
              {
                if(riga[k]==')') riga[k]='\0';
                else k++;
              }
              if(newSimbol(table,riga)==1){
                table=insert(table, numberline-scarto,riga); scarto++;
              }
            }
          }
          riga[0]='\0';
        }
        numberline=0;
        fOut=fopen(nome,"w");
        while(!feof(fin)){
            fgets(riga,256,fin);
            str_len=strlen(riga);
            removeSpace(riga);
            checkComment(riga);
            if(riga[0]!='\n' && riga[0]!='\0' && riga[0]!='\t' && riga[0]!='\r' && riga[0]!='('){
            if (riga[0] != '@'){
                char C_instr[18];
                C_instr[0]='\0';
                strncpy(riga,cInstruction(riga,C_instr),17);
                fprintf(fOut, "%s\n" , riga);
            } else{table=aInstruction(riga,table,fOut);}
             riga[0]='\0';
             }
        }  
	  fclose(fin);
    fclose(fOut);
	  return 0;
}
