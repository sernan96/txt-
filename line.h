#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE 1024

typedef struct {
	    long offset;
	        int length;
} LineInfo;

LineInfo* makeTable(char* filename, int* lineCount);
void printLine(char* filename, LineInfo* table, int lineNumber);
void printLines(char* filename, LineInfo* table, char* input, int lineCount);


void deleteLine(LineInfo* table, int* lineCount, int line);
void addLine(char* filename, LineInfo* table, int* lineCount, int line);
void replaceLine(char* filename, LineInfo* table, int* lineCount, int line);
