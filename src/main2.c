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

int fromAlphaToDec(char* binInstr, char* parameters[]) {
	if(strcmp(binInstr, "0100") == 0) {
		char* pars = parameters[1];
		int k;
		int num = 0;
		int len = strlen(parameters[1]);
		for(k = 0; k < len-1; k++) {
			int tempNum = (int)pars[k]-48;
			num = num + tempNum;
			num = num*10;
		}
		int tempNum = (int)pars[k]-48;
		num = num + tempNum;
		return num;
	}
	return 0;
}

char* fromDecToBin(int num) {
	printf("%d\n", num);
	char bin[25];
	int i = 524288;
	while(i >= 1) {
		printf("%d\n", i);
		if(num - i >= 0) {
			strcat(bin, "1");
			num = num - i;
		}  else {
			strcat(bin, "0");

		}
		i /= 2;
	}
	return bin;
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

		char* binInstr = getBinaryInstruction(tok);

		tok = strtok(NULL, ", ");
		parameters[j] = tok;
		j++;
		tok = strtok(NULL, ", ");
		parameters[j] = tok;
		j++;
		tok = strtok(NULL, ", ");
		parameters[j] = tok;
		j++;
//		Memory(instruction, parameters, j, i);
		int num = fromAlphaToDec(binInstr, parameters);
		char* binNum = fromDecToBin(num);
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
