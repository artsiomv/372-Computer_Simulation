#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "main.h"

typedef struct structInstruction{
	unsigned int opcode;
	unsigned int reg1;
	unsigned int reg2;
	unsigned int sign;
	char rest[20];
} Instruction;
Instruction structInstruction;
char fileInstructions[500][500];
int startAddress = 0;
int ZRegister = 0;

void execute(int opcode, int reg1, int reg2, int field3, int func) {
	int ans;
//	printf("OPCODE %d %d, %d, %d\n", opcode, reg1, reg2, field3);
	if(opcode == 0) { 			//ADD
//		printf("ADD\n");
		ans = ALU(loadFrom(reg2), loadFrom(field3), func);
		loadTo(reg1, ans);
	}
	else if(opcode == 1) {		//NAND
//		printf("NAND IN EX ALU\n");
		ans = ALU(loadFrom(reg2), loadFrom(field3), func);
//		printf("NAND IN EX %d\n", ans);
		loadTo(reg1, ans);
	}
	else if(opcode == 10) {		//ADDI
//		printf("ADDI\n");
		ans = ALU(loadFrom(reg2), field3, func);
		loadTo(reg1, ans);
	}
	else if(opcode == 11) {		//LW
//		printf("F\n");
		ans = ALU(loadFrom(reg2), field3, func);
//		printf("%d\n", ans);
//		printf("%s\n", getMemory(1000));
		loadTo(reg1, fromBinToDec(getMemory(ans)));
//		printf("R\n");
	}
	else if(opcode == 100) {		//SW
		ans = ALU(loadFrom(reg2), field3, func);
//		printf("SW %d\n", field3);
//		printf("SW %d\n", loadFrom(reg2));
//		printf("SW %d\n", loadFrom(reg1));
//		printf("SW ANS %d\n", ans);
//		printf("BIN %s\n", fromDecToBin(loadFrom(reg1)));
//		printf("%s\n", getMemory(1000));
		Memory(fromDecToBin(loadFrom(reg1)), ans);
//		printf("%s\n", getMemory(1000));
	}
	else if(opcode == 101) {		//BEQ
//		printf("BEQ\n");
		if(ZRegister == 0) {
			ans = ALU(loadFrom(reg1), loadFrom(reg2), func);
//			printf("%d\n",field3);
			if(ans == 0) ZRegister = 1;
		} else {
			ans = ALU(getPC(), field3, func);
//			printf("%d\n", getPC());
//			printf("%d\n", field3);
//			printf("%d\n", func);
//			printf("LLLLLLLL %d\n", ans);
			setPC(ans);
		}
	}
	else if(opcode == 110) { 		//JALR
//		printf("JALR\n");
//		printf("%d\n", loadFrom(reg1));
		setPC(loadFrom(reg1));
//		printf("PC JALR %d\n", getPC());
		// set reg2 to the PC+1
	}
}

void getRType(int func) {
	int opcode = structInstruction.opcode;
	int reg1 = structInstruction.reg1;
	int reg2 = structInstruction.reg2;
	int reg3 = 0;
	int i;
	for(i = 15; i < strlen(structInstruction.rest); i++) {
		if(structInstruction.rest[i]== '1') reg3 = reg3 * 10 + 1;
		else reg3 = reg3 * 10;
	}
	execute(opcode, reg1, reg2, reg3, func);
}

void getADDI(int func) {
	int num = 0;
	char buffer[20];
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
	int opcode = structInstruction.opcode;
	int reg1 = structInstruction.reg1;
	int reg2 = structInstruction.reg2;
	char* rest = structInstruction.rest;

	//find imm value
	int num = 0;
	int j;
	for(j = 0; j < strlen(rest); j++) {
		if(rest[j] == '1') num = num*2+1;
		else num = num*2+0;
	}
//	printf("H\n");
	execute(opcode, reg1, reg2, num, func);
}

void getBEQ(int func) {
	int opcode = structInstruction.opcode;
	int reg1 = structInstruction.reg1;
	int reg2 = structInstruction.reg2;
	char* rest = structInstruction.rest;

//	printf("%d\n", opcode);
//	printf("%d\n", reg1);
//	printf("%d\n", reg2);
//	printf("%s\n", rest);
	int num = 0;
	int j;
	for(j = 0; j < strlen(rest); j++) {
		if(rest[j] == '1') num = num*2+1;
		else num = num*2+0;
	}
//	printf("NUM %d\n", num);
	execute(opcode, reg1, reg2, num, func);
	if(ZRegister == 1) {
		func = 0;
		execute(opcode, reg1, reg2, num, func);
	}
}

void getJALR() {
	int opcode = structInstruction.opcode;
	int reg1 = structInstruction.reg1;
	int reg2 = structInstruction.reg2;
	char* unused = structInstruction.rest;
	execute(opcode, reg1, reg2, 0, -1);
}

int decode() {
	int func = -1;
	if(structInstruction.opcode == 0) { 			//ADD
//		printf("ADD\n");
		func = 0;
		getRType(func);
	}
	else if(structInstruction.opcode == 1) {		//NAND
//		printf("NAND\n");
		func = 1;
		getRType(func);
	}
	else if(structInstruction.opcode == 10) {       //ADDI
//		printf("ADDI\n");
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
		func = 10;
		getBEQ(func);
	}
	else if(structInstruction.opcode == 110) {		//JALR
		getJALR();
	}
	return 0;
}

void fetch(int line) {
	//load instruction from memory PC -> MAR
	char* lineOfMemory = getMemory(line);
//	printf("opcode4 %s \n", lineOfMemory);
	//increment PC, PC -> A; A+1 -> PC
	ALU(line, 0, 11);
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
	decode();
}

char* getBinaryInstruction(char* inst) {
	for(int i = 0; i < strlen(inst); i++) {
		inst[i] = toupper(inst[i]);
	}
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

void output(int maxLines) {
	 FILE* outFile = fopen("output.txt", "w");
	 fprintf(outFile, "$zero: %d\n$at: %d\n$v0: %d\n$a0: %d\n$a1: %d\n$a2: %d\n",
			 getRegInfo(0), getRegInfo(1), getRegInfo(2), getRegInfo(3), getRegInfo(4), getRegInfo(5));
	 fprintf(outFile,"$t0: %d\n$t1: %d\n$t2: %d\n$s0: %d\n$s1: %d\n",  getRegInfo(6), getRegInfo(7), getRegInfo(8), getRegInfo(9), getRegInfo(10));
	 fprintf(outFile,  "$s2: %d\n$k0: %d\n$sp: %d\n$fp: %d\n$ra: %d\n",getRegInfo(11), getRegInfo(12), getRegInfo(13), getRegInfo(14), getRegInfo(15));

	 for(int i = 0; i < maxLines; i++) {
		 fprintf(outFile, "%d  %s | %s %s\n",2000+i, getMemory(2000+i),getLabel(2000+i), fileInstructions[i]);
	 }
}

int main() {
	FILE *fp;
	char buff[500];
	char *tok;
	char* instruction;
	char* label;
	char* parameters[4];
	short i = 0;
	char* p[4];
	//create Memory pool
	create_pool(20000);
	initialize();

	fp = fopen("input.txt", "r");
	while(fgets(buff, 500, fp) != NULL) {
		if(*buff != ';') {
			buff[strcspn(buff, "\r\n;")] = 0;
			int j = 0;
			char* binInstr = "";
			if(buff[0] != '\t') {
				tok = strtok(buff,"\t");
				label = strtok(buff, ":");
				setLabel(label, 2000+i);
				tok = strtok(NULL, " ");
				instruction = tok;
				binInstr = getBinaryInstruction(instruction);
				tok = strtok(NULL, ", ");
				parameters[j] = tok;
				j++;
				if(tok == NULL) {
					strcpy(fileInstructions[i], instruction);
				}
				else {
					tok = strtok(NULL, ", ");
					parameters[j] = tok;
					j++;
					tok = strtok(NULL, ", ");
					parameters[j] = tok;
					j++;
					char string[50];
					memset(string, 0, sizeof(string));
					strcpy(string, instruction);
					strcat(string, " ");
					for(int k = 0; k < j; k++) {
						strcat(string, parameters[k]);
						strcat(string, ", ");
					}
					strcpy(fileInstructions[i], string);
				}
			}
			i++;
		}
	}
	fclose(fp);

	i = 0;
	fp = fopen("input.txt", "r");
	while(fgets(buff, 500, fp) != NULL) {
		if(*buff != ';') {
			buff[strcspn(buff, "\r\n;")] = 0;
//			printf("%s\n", buff);
			int j = 0;
			char* binInstr = "";
			if(buff[0] == '\t') {
				tok = strtok(buff,"\t");
				strcpy(fileInstructions[i], tok);
				tok = strtok(tok, " ");
				instruction = tok;
				binInstr = getBinaryInstruction(tok);
				tok = strtok(NULL, ", ");
				parameters[j] = tok;
				j++;
				tok = strtok(NULL, ", ");
				parameters[j] = tok;
				j++;
				tok = strtok(NULL, ", ");
				parameters[j] = tok;
				j++;
			}
			else if(buff[0] != '\t') {
				tok = strtok(buff,"\t");
				label = strtok(buff, ":");
				setLabel(label, 2000+i);
				tok = strtok(NULL, " ");
				instruction = tok;
				binInstr = getBinaryInstruction(instruction);
				tok = strtok(NULL, ", ");
				parameters[j] = tok;
				j++;
				if(tok == NULL) {
					strcpy(fileInstructions[i], instruction);
				}
				else {
					tok = strtok(NULL, ", ");
					parameters[j] = tok;
					j++;
					tok = strtok(NULL, ", ");
					parameters[j] = tok;
					j++;
					char string[50];
					memset(string, 0, sizeof(string));
					strcpy(string, instruction);
					strcat(string, " ");
					for(int k = 0; k < j; k++) {
						strcat(string, parameters[k]);
						strcat(string, ", ");
					}
					strcpy(fileInstructions[i], string);
				}
			}
//			printf("FI %s\n", fileInstructions[i]);

			char* memoryLine = InstructionRegister(binInstr, parameters, i);
			Memory(memoryLine, getPC()+i);
			i++;
		}
	}
	fclose(fp);
	setPC(2001);
	int k = 0;
	printf("Memory at 1000 before: %s\n", getMemory(1000));
	while(getPC() < i+2000-1) {
//		printf("%d\n", getPC());

		fetch(getPC());
//		printf("$a0: %d\n", getRegInfo(3));
//		printf("$a1: %d\n", getRegInfo(4));
//		printf("$a2: %d\n", getRegInfo(5));
//		printf("$t0: %d\n", getRegInfo(6));
//		printf("$t1: %d\n", getRegInfo(7));
//		printf("$t2: %d\n", getRegInfo(8));
//		printf("$s0: %d\n", getRegInfo(9));
	}
	printf("Memory at 1000  after: %s\n", getMemory(1000));
	output(i);
}
