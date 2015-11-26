#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "main.h"

typedef struct structInstruction{
	unsigned int opcode;
	unsigned int reg1;
	unsigned int reg2;
	unsigned int sign;
	char rest[20];
} Instruction;
Instruction structInstruction;

void execute(int opcode, int reg1, int reg2, int field3, int func) {
	//TODO
	int ans;
	if(opcode == 0) { 			//ADD
		ans = ALU(loadFrom(reg2), loadFrom(field3), func);
		loadTo(reg1, ans);
	}
	else if(opcode == 01) {		//NAND
		ans = ALU(loadFrom(reg2), loadFrom(field3), func);
		loadTo(reg1, ans);
	}
	else if(opcode == 10) {		//ADDI
		ans = ALU(loadFrom(reg2), field3, func);
		loadTo(reg1, ans);
	}
	else if(opcode == 11) {		//LW
		ans = ALU(loadFrom(reg2), field3, func);
		loadTo(reg1, fromBinToDec(getMemory(ans)));
	}
	else if(opcode == 100) {		//SW
		ans = ALU(loadFrom(reg2), field3, func);
		Memory(fromDecToBin(loadFrom(reg1)), ans);
	}
}

void getRType(int func) {
	int opcode = structInstruction.opcode;
	int reg1 = structInstruction.reg1;
	int reg2 = structInstruction.reg2;
	int unused = 000000000000000;   //16x0
	int reg3 = 0;
	int i;
	for(i = 15; i < strlen(structInstruction.rest); i++) {
		if(structInstruction.rest[i]== '1') reg3 = reg3 * 10 + 1;
		else reg3 = reg3 * 10;
	}
	execute(opcode, reg1, reg2, reg3, func);
}

void getADDI(int func) {
	char buffer[20];
	int num = 0;
	memset(buffer, 0, sizeof(buffer));
	if(structInstruction.sign == 1) {
		int j;
		for(j = 0; j < strlen(structInstruction.rest); j++) {
			if(structInstruction.rest[j] == '1') strcat(buffer, "0");
			else if(structInstruction.rest[j] =='0') strcat(buffer, "1");
		}
		num = ((fromBinToDec(buffer)+1) *(-1));
	} else {
		int j;
		for(j = 0; j < strlen(structInstruction.rest); j++) {
			if(structInstruction.rest[j] == '1') strcat(buffer, "1");
			else if(structInstruction.rest[j] =='0') strcat(buffer, "0");
		}
		num = fromBinToDec(buffer);
	}
	int opcode = structInstruction.opcode;
	int reg1 = structInstruction.reg1;
	int reg2 = structInstruction.reg2;
	int field3 = num;
	execute(opcode, reg1, reg2, field3, func);
}

void getLWSW(int func) {
	char buffer[20];
//	sprintf(buffer, "%s", structInstruction.rest);
	int opcode = structInstruction.opcode;
	int reg1 = structInstruction.reg1;
	int reg2 = structInstruction.reg2;
	int sign = structInstruction.sign;
	char* rest = structInstruction.rest;

//
//
//
//	static char binRestReverse[20] = "";
//	memset(binRestReverse, 0, sizeof(binRestReverse));
//	while(num != 0) {
//		if((num % 2) == 1) {
//			num -= 1;
//			num /= 10;
//			if(strcmp(binRestReverse, "") == 0) strcpy(binRestReverse, "1");
//			else strcat(binRestReverse, "1");
//		} else {
//			num /= 10;
//			if(strcmp(binRestReverse, "") == 0) strcpy(binRestReverse, "0");
//			else strcat(binRestReverse, "0");
//		}
//	}
//	char binRest[20] = "";
//	int i;
//	for(i = 19; i > 0-1; i--) {
//		if(binRestReverse[i] == '1') {
//			if(strcmp(binRest, "") == 0) strcpy(binRest, "1");
//			else strcat(binRest, "1");
//		} else if(binRestReverse[i] == '0') {
//			if(strcmp(binRest, "") == 0) strcpy(binRest, "0");
//			else strcat(binRest, "0");
//		}
//	}

	//find imm value
	int num = 0;
	int j;
	for(j = 0; j < strlen(rest); j++) {
		if(rest[j] == '1') num = num*2+1;
		else num = num*2+0;
	}
	execute(opcode, reg1, reg2, num, func);
}

void fetch(int line) {
	//load instruction from memory PC -> MAR
	char* lineOfMemory = getMemory(line);
	//increment PC, PC -> A; A+1 -> PC
	setPC(ALU(getPC(), 0, 11));

	int instruction = 0;
	int opcode = 0;
	int reg1 = 0;
	int reg2 = 0;
	int sign = 0;
	char rest[20];
	memset(rest, 0, sizeof(rest));
	memset(structInstruction.rest, 0, sizeof(structInstruction.rest));
	int i;
	//get opcode
	for(i = 0; i < 4; i++) {
		if(lineOfMemory[i]== '1') opcode = opcode * 10 + 1;
		else opcode = opcode * 10;
	}
	structInstruction.opcode = opcode;
	//get first register
	for(i = 4; i < 8; i++) {
		if(lineOfMemory[i]== '1') reg1 = reg1 * 10 + 1;
		else reg1 = reg1 * 10;
	}
	structInstruction.reg1 = reg1;
	//get second register
	for(i = 8; i < 12; i++) {
		if(lineOfMemory[i]== '1') reg2 = reg2 * 10 + 1;
		else reg2 = reg2 * 10;
	}
	structInstruction.reg2 = reg2;
	//get the rest of the numbers
	if(lineOfMemory[12]== '1') sign = 1;
	else sign = 0;
	structInstruction.sign = sign;
	for(i = 13; i < 32; i++) {
		if(lineOfMemory[i]== '1') strcat(rest, "1");
		else strcat(rest, "0");
	}
	strcpy(structInstruction.rest, rest);
}

int decode() {
	int func = -1;
	if(structInstruction.opcode == 0) { 			//ADD
		func = 0;
		getRType(func);
	}
	else if(structInstruction.opcode == 1) {		//NAND
		func = 1;
		getRType(func);
	}
	else if(structInstruction.opcode == 10) {       //ADDI
		func = 0;
		getADDI(func);
	}
	else if(structInstruction.opcode == 11) {		//LW
		func = 0;
		getLWSW(func);
	}
	else if(structInstruction.opcode == 100) {		//SW
		func = 0;
		getLWSW(func);
	}
	else if(structInstruction.opcode == 101) {		//BEQ

	}
	else if(structInstruction.opcode == 110) {		//JALR

	}
	return 0;
}

char* getBinaryInstruction(char* inst) {
	if(strcmp(".ORIG", inst) == 0) {
		return ".ORIG";
	} else if(strcmp(".END", inst) == 0) {
		return ".END";
	} else if(strcmp("ADD", inst) == 0) {
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
	char buff[500];
	char *tok;
	char* instruction;
	char* parameters[4];
	short i = 0;

	//create Memory pool
	create_pool(20000);

	//find labels
//	fp = fopen("input2.txt", "r");
//	while(fgets(buff, 50, fp)) {
//		if(*buff != ';') {
//
//		}
//		buff[strcspn(buff, "\r\n")] = 0;
//		tok = strtok(buff, " ");
//
//	}
//	fclose(fp);

//	char buff[30];
	fp = fopen("input2.txt", "r");
	while(fgets(buff, 500, fp) != NULL) { //use sscanf
		if(*buff != ';') {
			buff[strcspn(buff, "\r\n;")] = 0;
			int j = 0;
			tok = strtok(buff,"\t");
			printf("%d - %s\n", i, buff);
			tok = strtok(tok, " ");
			instruction = tok;
			char* binInstr = getBinaryInstruction(tok);
			tok = strtok(NULL, ", ");
			parameters[j] = tok;
			j++;
//			printf("t %s\n", tok);
			tok = strtok(NULL, ", ");
			parameters[j] = tok;
			j++;
			tok = strtok(NULL, ", ");
			parameters[j] = tok;
//			printf("t %s\n", tok);
//			for(int i = 0; i < 4; i++) {
//				printf("%d %s\n",i,  parameters[i]);
//			}
			j++;
			if(strcmp(binInstr, ".ORIG") == 0) {
				InstructionRegister(instruction, parameters);
			}
			else if (strcmp(binInstr, ".END") == 0) {
				break;
			}
			else {
				char* memoryLine = InstructionRegister(binInstr, parameters);
				Memory(memoryLine, getPC()+i);
				printf("  %s\n", memoryLine);
				i++;
			}
		}
	}
	fclose(fp);
	int k;
	for(k = 0; k < i; k++) {
		fetch(getPC());

		decode();
		printf("$a0 %d\n", loadFrom(11));
		printf("$a1 %d\n", loadFrom(100));
		printf("$a2 %d\n", loadFrom(101));
		printf("MEM_1000 %s\n", getMemory(1000));
	}
}
