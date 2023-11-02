#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "line.h"

LineInfo* makeTable(char* filename, int* lineCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return NULL;
    }
    
    LineInfo* table = (LineInfo*)malloc(sizeof(LineInfo) * MAX_LINE);
    *lineCount = 0;
    
    long offset = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        table[*lineCount].offset = offset;
        table[*lineCount].length = strlen(line);
        offset = ftell(file);
        (*lineCount)++;
    }
    
    fclose(file);
    return table;
}

void printLine(char* filename, LineInfo* table, int lineNumber) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return;
    }
    
    fseek(file, table[lineNumber-1].offset, SEEK_SET);
    char* line = (char*)malloc(table[lineNumber-1].length + 1);
    fread(line, 1, table[lineNumber-1].length, file);
    line[table[lineNumber-1].length] = '\0';
    
    printf("%d: %s", lineNumber, line);
    free(line);
    fclose(file);
}

void printLines(char* filename, LineInfo* table, char* input, int lineCount) {
    if (strchr(input, '*')) {
        for (int i = 1; i <= lineCount; i++) {
            printLine(filename, table, i);
        }
    } else if (strchr(input, '-')) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        for (int i = start; i <= end; i++) {
            printLine(filename, table, i);
        }
    } else {
        char* token = strtok(input, ", ");
        while (token != NULL) {
            int line = atoi(token);
            printLine(filename, table, line);
            token = strtok(NULL, ", ");
        }
    }
}
void deleteLine(LineInfo* table, int* lineCount, int line) {
    if(line > *lineCount || line < 1) {
        printf("잘못된 라인 번호입니다.\n");
        return;
    }
    for(int i = line - 1; i < *lineCount - 1; i++) {
        table[i] = table[i+1];
    }
    (*lineCount)--;
}

void addLine(char* filename, LineInfo* table, int* lineCount, int line) {
    if(line > *lineCount || line < 1) {
        printf("잘못된 라인 번호입니다.");
        return;
    }
    char* newLine = malloc(MAX_LINE);
    printf("추가할 문자열을 입력하세요: ");
    fgets(newLine, MAX_LINE, stdin);
    
    FILE* file = fopen(filename, "r");
    FILE* temp = fopen("temp.txt", "w");
    char buffer[MAX_LINE];
    int i;
    for(i = 0; i < line - 1; i++) {
        fgets(buffer, MAX_LINE, file);
        fputs(buffer, temp);
    }
    fputs(newLine, temp);
    while(fgets(buffer, MAX_LINE, file)) {
        fputs(buffer, temp);
    }
    fclose(file);
    fclose(temp);
    
    remove(filename);
    rename("temp.txt", filename);
    
    (*lineCount)++;
    for(i = *lineCount; i > line; i--) {
        table[i] = table[i-1];
    }
    long offset = line > 1 ? table[line-2].offset + table[line-2].length : 0;
    int length = strlen(newLine);
    table[line-1] = (LineInfo){offset, length};
    
    free(newLine);
}


void replaceLine(char* filename, LineInfo* table, int* lineCount, int line) {
    if(line > *lineCount || line < 1) {
        printf("잘못된 라인 번호입니다.");
        return;
    }
    char* newLine = malloc(MAX_LINE);
    printf("대체할 문자열을 입력하세요: ");
    fgets(newLine, MAX_LINE, stdin);
    
    FILE* file = fopen(filename, "r");
    FILE* temp = fopen("temp.txt", "w");
    char buffer[MAX_LINE];
    int i;
    for(i = 0; i < line - 1; i++) {
        fgets(buffer, MAX_LINE, file);
        fputs(buffer, temp);
    }
    fputs(newLine, temp);
    fgets(buffer, MAX_LINE, file);
    while(fgets(buffer, MAX_LINE, file)) {
        fputs(buffer, temp);
    }
    fclose(file);
    fclose(temp);
    
    remove(filename);
    rename("temp.txt", filename);
    
    long offset = line > 1 ? table[line-2].offset + table[line-2].length : 0;
    int length = strlen(newLine);
    table[line-1] = (LineInfo){offset, length};
    
    free(newLine);
}


