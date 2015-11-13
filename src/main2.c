#include <stdio.h>
#include <string.h>
#include <regex.h>

#include "main.h"

int fetch() {
	return 0;
}

int decode() {
	return 0;
}

int execute() {
	return 0;
}


char* getBinaryInstruction(char* inst) {
	if(strcmp("ADD", inst) == 0) {
		return "0000";
	} else if(strcmp("NAND", inst) == 0) {
		return "0001";
	} else if(strcmp("ADDI", inst) == 0) {
		return "0010";
	} else if(strcmp("LW", inst) == 0) {
		return "0011";
	} else if(strcmp("SW", inst) == 0) {
		return "0100";
	} else if(strcmp("BEQ", inst) == 0) {
		return "0101";
	} else if(strcmp("JALR", inst) == 0) {
		return "0110";
	} else if(strcmp("HALT", inst) == 0) {
		return "0111";
	}
	return "";
}

int main() {
	FILE *fp;
	char buff[20];
	char *tok;
	char* instruction;
	char* parameters[4];
	short i = 0;
	fp = fopen("input2.txt", "r");
	while(fgets(buff, 20, fp)) {
		int j = 0;
		tok = strtok(buff, " ");
		instruction = tok;
		printf("INST %s\n", instruction );

		char* binInstr = getBinaryInstruction(tok);
		printf("%s\n", binInstr );

		tok = strtok(NULL, ", ");
		parameters[j] = tok;
		printf("+ %s\n", parameters[j] );
		j++;
		tok = strtok(NULL, ", ");
		parameters[j] = tok;
		printf("+ %s\n", parameters[j] );
		j++;
		tok = strtok(NULL, ", ");
		parameters[j] = tok;
		printf("+ %s\n", parameters[j] );
		j++;
		Memory(instruction, parameters, j, i);
		i++;
	}
	fclose(fp);
	int k;
	for(k = 0; k < i; k++) {
		fetch();
		decode();
		execute();

	}
}
