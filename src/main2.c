#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "main.h"

typedef struct instruction{
	unsigned int opcode;
	unsigned int reg1;
	unsigned int reg2;
	unsigned int rest;
} Instruction;
Instruction instruction;
//Instruction inst;

void fetch(int line) {
//	printf("@%d\n", line);
	instruction = getMemory(line);
//	printf("- %s\n", instruction);
//	printf("- %04d\n", instruction.opcode);

}

void execute(int opcode, int reg1, int reg2, int reg3, int func) {
	//TODO
	int ans;
	printf("_____ %d\n", reg1);
	if(opcode == 0) {
		ans = ALU(loadFrom(reg2), loadFrom(reg3), func);
	}
	else if(opcode == 10) {
		ans = ALU(reg2, reg3, func);

	}
	loadTo(reg1, ans);
	printf(">>>> %d\n", ans);
	printf("<<<< %d\n" , loadFrom(reg1));
}

int decode() {
	int func = -1;
//	int instruct = 0;
//	int opcode = 0;
//	int reg1 = 0;
//	int reg2 = 0;
//	int rest = 0;
//	int i;
//
//	//get opcode
//	for(i = 0; i < 4; i++) {
////		printf("%c\n", instruction[i]);
//		if(instruction[i] == '1') {
//			printf("1");
//			opcode = opcode * 10 + 1;
//		}
//		else opcode = opcode * 10;
//	}
//	printf("OP  %d\n", opcode);
//	instruction.opcode = opcode;
//
//	//get first register
//	for(i = 4; i < 8; i++) {
//		if(instruction[i]== '1') reg1 = reg1 * 10 + 1;
//		else reg1 = reg1 * 10;
//	}
//	instruction.reg1 = reg1;
//	//get second register
//	for(i = 8; i < 12; i++) {
//		if(instruction[i]== '1') reg2 = reg2 * 10 + 1;
//		else reg2 = reg2 * 10;
//	}
//	instruction.reg2 = reg2;
//	//get the rest of the numbers
//	for(i = 12; i < 32; i++) {
//		if(instruction[i]== '1') rest = rest * 10 + 1;
//		else rest = rest * 10;
//	}
//	instruction.rest = rest;


//	printf("%d\n", instruction.opcode);
	if(instruction.opcode == 0) { 				//ADD
		func = 0;
		int opcode = instruction.opcode;
		int reg1 = instruction.reg1;
		int reg2 = instruction.reg2;
		int unused = 0000000000000000;   //0x16
		int reg3 = instruction.rest;
		execute(opcode, reg1, reg2, reg3, func);
	}
	else if(instruction.opcode == 1) {			//NAND

	}
	else if(instruction.opcode == 10) {         //ADDI
		func = 0;
		char buffer[20];// = instruction.rest;
		sprintf(buffer, "%d", instruction.rest);
		int offSet = sizeof(buffer) - sizeof(instruction.rest);

		char off[20] = "";
		for(int i = 0; i < offSet; i++) {
			if(strcmp(off, "") == 0) strcpy(off, "0");
			else strcat(off, "0");
		}
		strcat(off, buffer);

		//find imm value
		int num = 0;
		for(int i = 0; i < strlen(off); i++) {
			if(off[i] == '1') num = num*2+1;
			else num = num*2+0;
		}

		int opcode = instruction.opcode;
		int reg1 = instruction.reg1;
		int reg2 = instruction.reg2;
		int field3 = num;

		execute(opcode, reg1, reg2, field3, func);
	}
	else if(instruction.opcode == 11) {			//LW

	}
	else if(instruction.opcode == 100) {		//SW

	}
	else if(instruction.opcode == 101) {		//BEQ

	}
	else if(instruction.opcode == 110) {		//JALR

	}
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

	//create Memory pool
	create_pool(12800);

	//find labels
	fp = fopen("input2.txt", "r");
	while(fgets(buff, 50, fp)) {
		buff[strcspn(buff, "\r\n")] = 0;
		tok = strtok(buff, " ");

	}
	fclose(fp);

	fp = fopen("input2.txt", "r");
	while(fgets(buff, 50, fp)) {
		buff[strcspn(buff, "\r\n")] = 0;
		printf("%d - %s\n", i, buff);
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
		char* memoryLine = InstructionRegister(binInstr, parameters);
		printf("  %s\n", memoryLine);
		Memory(memoryLine, i);
		i++;
	}
	fclose(fp);
	int k;
	for(k = 0; k < i; k++) {
		fetch(fetchPC());
		decode();
//		execute();
	}
}
