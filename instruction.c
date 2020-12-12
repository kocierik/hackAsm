#include "whitespace.h"
#include "instruction.h"

struct simTable* insert(struct simTable* element, int new_data, char* simb){ 
      struct simTable* new_node = (struct simTable*) malloc(sizeof(struct simTable)); 
      new_node->val  = new_data; 
      strcpy(new_node->simbolo, simb); 
      new_node->next = element; 
      return (new_node); 
}
struct simTable* define(){
      struct simTable* element =(struct simTable*) malloc(sizeof(struct simTable)); 
      strcpy(element->simbolo,"0");
      element->next=NULL; 
      element=insert(element,0,"SP");
      element=insert(element,1,"LCL");
      element=insert(element,2,"ARG");
      element=insert(element,3,"THIS");
      element=insert(element,4,"THAT");  
      element=insert(element,16384,"SCREEN");  
      element=insert(element,24576,"KBD");    
      element=insert(element,0,"R0");
      element=insert(element,1,"R1");
      element=insert(element,2,"R2");
      element=insert(element,3,"R3");
      element=insert(element,4,"R4");
      element=insert(element,5,"R5");
      element=insert(element,6,"R6");
      element=insert(element,7,"R7");
      element=insert(element,8,"R8");
      element=insert(element,9,"R9");
      element=insert(element,10,"R10");
      element=insert(element,11,"R11");
      element=insert(element,12,"R12");
      element=insert(element,13,"R13");
      element=insert(element,14,"R14");
      element=insert(element,15,"R15");
  return (element);
}

int newSimbol(struct simTable* element, char* line){
      while (element!= NULL) {
          if(strcmp(element->simbolo,line)==0) return 0;
          element = element->next;
        }
        return 1;
}

int convertData(char *str){
    int val;
    val = 0;
    while(*str){
        if (*str >= '0' && *str <= '9'){
            val *= 10;
            val += *str - '0';
          }
        else return val;
        str++;
      }
    return val;
}

void convertBinary(int n,FILE* fOut){
      int a[15],i; 
      for(i=0;n>0;i++){    
          a[i]=n%2;    
          n=n/2;    
      }
          for(int j=14-i;j>=0;j--)    
            fprintf(fOut,"0");     
          for(i=i-1;i>=0;i--)   
            fprintf(fOut,"%d",a[i]);    
}

struct simTable* aInstruction(char *line,struct simTable* table,FILE *fOut){
 int cnt=0;
 struct simTable* element=table;
        int j=0;
        while(line[j]!='\0'){
            line[j]=line[j+1];
            j++;}
        j=0;
        if (line[0] >= '0' && line[0] <= '9'){
         int num = convertData(line);
         fprintf(fOut, "%d", 0);
         convertBinary(num,fOut);
         fprintf(fOut, "\n");
         } else{
        if(newSimbol(element,line)==1){
          table=insert(table,16+cnt,line);
          cnt++;
        } 
        element=table;
        while (element!=NULL)
        {
          if(strcmp(line,element->simbolo)==0)
          {
            int num=element->val;
            fprintf(fOut, "%d", 0);
            convertBinary(num,fOut);
            fprintf(fOut, "\n");
          }
          element=element->next;
          }
        }
  return table;
}

void destA(char *line, char* C_instr){
  int counter = 0,equal=0;
  while (line[counter]!='\0'){
    if(line[counter]=='=') equal=1;
      counter++;
    }
  if(equal==1){
  C_instr[10]='\0';
  if (line[0] == 'A' && line[1] == 'M' && line[2] == 'D'){strcat(C_instr,"111");}
  else if (line[0] == 'A' && line[1] == 'D'){strcat(C_instr,"110");}
  else if (line[0] == 'A' && line[1] == 'M'){strcat(C_instr,"101");}
  else if (line[0] == 'A'){strcat(C_instr,"100");}
  else if (line[0] == 'M' && line[1] == 'D'){strcat(C_instr,"011");}
  else if (line[0] == 'D'){strcat(C_instr,"010");}
  else if (line[0] == 'M'){strcat(C_instr,"001");}
  else {strcat(C_instr,"000");}}
  else strcat(C_instr,"000");
}

void jumpA(char *line, char* C_instr){
  int i=0;
  C_instr[13]='\0';
  while (line[i]!='\0')
  {
    if (line[i] == ';' && line[i+1] == 'J'){
    if (line[i+2] == 'M' && line[i+3] == 'P'){strcat(C_instr,"111");}
    else if (line[i+2] == 'L' && line[i+3] == 'E'){strcat(C_instr,"110");}
    else if (line[i+2] == 'N' && line[i+3] == 'E'){strcat(C_instr,"101");}
    else if (line[i+2] == 'L' && line[i+3] == 'T'){strcat(C_instr,"100");}
    else if (line[i+2] == 'G' && line[i+3] == 'E'){strcat(C_instr,"011");} 
    else if (line[i+2] == 'E' && line[i+3] == 'Q'){strcat(C_instr,"010");}
    else if (line[i+2] == 'G' && line[i+3] == 'T'){strcat(C_instr,"001");}}
  i++;
  }
  if(C_instr[13]=='\0') strcat(C_instr,"000");
}

void compA(char *riga, char* C_instr){
  char comp[3];
  C_instr[3] = '\0';
  int counter = 0, CInstructionA=0;
  while (riga[counter] != '=' && riga[counter]!='\0')counter++;
  int i=counter, j=0;
  while(riga[i]!='\0'){  
    if (riga[i] == 'M') CInstructionA = 1;
    i++;
    }
    if(riga[counter]!='='){
    strncpy(comp,riga,3);
    } else{
      comp[0]=riga[counter+1];
      comp[1]=riga[counter+2];
      comp[2]=riga[counter+3];
    }
    while(comp[j]!='\0'){
      j++;
      if(comp[j]==';') comp[j]='\0';
    }
    if (CInstructionA==1){      
    if (strncmp(comp,"D|M",3)==0){strcat(C_instr,"1010101");}
    else if (strncmp(comp,"D&M",3)==0){strcat(C_instr,"1000000");}
    else if (strncmp(comp,"M-D",3)==0){strcat(C_instr,"1000111");}
    else if (strncmp(comp,"D-M",3)==0){strcat(C_instr,"1010011");}
    else if (strncmp(comp,"D+M",3)==0){strcat(C_instr,"1000010");}
    else if (strncmp(comp,"M-1",3)==0){strcat(C_instr,"1110010");}
    else if (strncmp(comp,"M+1",3)==0){strcat(C_instr,"1110111");}
    else if (strncmp(comp,"-M",2)==0){strcat(C_instr,"1110011");}
    else if (strncmp(comp,"!M",2)==0){strcat(C_instr,"1110001");}
    else if (strncmp(comp,"M",1)==0){strcat(C_instr,"1110000");}}
    else if (CInstructionA == 0){ 
    if (strncmp(comp,"D|A",3)==0){strcat(C_instr,"0010101");}
    else if (strncmp(comp,"D&A",3)==0){strcat(C_instr,"0000000");}
    else if (strncmp(comp,"A-D",3)==0){strcat(C_instr,"0000111");}
    else if (strncmp(comp,"D-A",3)==0){strcat(C_instr,"0010011");}
    else if (strncmp(comp,"D+A",3)==0){strcat(C_instr,"0000010");}
    else if (strncmp(comp,"A-1",3)==0){strcat(C_instr,"0110010");}
    else if (strncmp(comp,"D-1",3)==0){strcat(C_instr,"0001110");}
    else if (strncmp(comp,"A+1",3)==0){strcat(C_instr,"0110111");}
    else if (strncmp(comp,"D+1",3)==0){strcat(C_instr,"0011111");}
    else if (strncmp(comp,"-A",2)==0){strcat(C_instr,"0110011");}
    else if (strncmp(comp,"-D",2)==0){strcat(C_instr,"0001111");}
    else if (strncmp(comp,"!A",2)==0){strcat(C_instr,"0110001");}
    else if (strncmp(comp,"!D",2)==0){strcat(C_instr,"0001101");}
    else if (strncmp(comp,"A",1)==0){strcat(C_instr,"0110000");}
    else if (strncmp(comp,"D",1)==0){strcat(C_instr,"0001100");}
    else if (strncmp(comp,"-1",2)==0){strcat(C_instr,"0111010");}
    else if (strncmp(comp,"1",1)==0){strcat(C_instr,"0111111");}
    else if (strncmp(comp,"0",1)==0){strcat(C_instr,"0101010");}}
}
 
char* cInstruction(char *riga, char *C_instr){
  strcat(C_instr,"111");
  compA(riga, C_instr);
  destA(riga, C_instr);
  jumpA(riga, C_instr);
  C_instr[17]='\0';
  return(C_instr);
}