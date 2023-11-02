#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "line.h"
#define MAX_LINE 1024

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("파일명을 입력해주세요.");
        return 1;
    }
    
    int lineCount;
    LineInfo* table = makeTable(argv[1], &lineCount);
    if (table == NULL) {
        return 1;
    }
    
    char input[256];

	do {
    printf(">> ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;  
    if (strcmp(input, "q") == 0) {
        break;
    }
	else if(input[0]>='a'&&input[0]<='z'){
		char command = input[0];
    	int line = atoi(&input[1]);

   		switch (command) {
    		case 'p':
        		printLine(argv[1], table, line);
        		break;
    		case 'd':
        		deleteLine(table, &lineCount, line);
        		break;
    		case 'a':
        		addLine(argv[1], table, &lineCount, line);
        		break;
    		case 's':
        		replaceLine(argv[1], table, &lineCount, line);
    	    	break;
			default:
				printf("그런 명령어는 없습니다만?\n");
				break;
   		}
	}
	else{
		printLines(argv[1], table, input, lineCount);
	}

    
} while (1);

    

    free(table);
    return 0;
}