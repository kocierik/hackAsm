#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 130
struct simTable{
  char simbolo[SIZE];
  int val;
  struct simTable *next;
}Symbol;

struct simTable* insert(struct simTable* element, int new_data, char* simb);
struct simTable* define();
int newSimbol(struct simTable* head, char* line);
int convertData(char *str);
void convertBinary(int n,FILE* fOut);
struct simTable* aInstruction(char *line,struct simTable* table,FILE *fOut);
void destA(char *line, char* C_instr);
void jumpA(char *line, char* C_instr);
void compA(char *riga, char* C_instr);
char* cInstruction(char *riga, char *C_instr);