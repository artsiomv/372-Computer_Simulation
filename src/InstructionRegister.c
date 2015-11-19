/*
 * InstructionRegister.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */

#include <stdio.h>
#include <string.h>
#include "InstructionRegister.h"

int fromAlphaToDec(char* binInstr, char* parameter) {
//	printf("3 %s\n", parameter);
//	if(strcmp(binInstr, "0100") == 0 || strcmp(binInstr, "0011") == 0) {
		char* pars = parameter;
		int k;
		int num = 0;
		int len = strlen(parameter);
		for(k = 0; k < len-1; k++) {
			int tempNum = (int)pars[k]-48;
			num = num + tempNum;
			num = num*10;
		}
		int tempNum = (int)pars[k]-48;
		num = num + tempNum;
		return num;
//	}
//	return 0;
}

char* fromDecToBin(int num) {
	static char bin[25];
	int i = 262144;
	while(i >= 1) {
		if(num - i >= 0) {
			strcat(bin, "1");
			num = num - i;
		} else {
			strcat(bin, "0");
		}
		i /= 2;
	}
	return bin;
}

//char* fromHexToBinary(int num) {
//	printf("%d\n", num);
//	int hex = num - '0';
//	printf("%d\n", hex);
//	int i = 262144;
//	while(i >= 1) {
//		if(num - i >= 0) {
//			printf("%d\n", 1);
//			num = num - i;
//		} else
//			printf("%d\n", 0);
//		i /= 2;
//	}
//	return "";
//}

char* getBinaryRegister(char* reg) {
	if(strcmp("$zero", reg) == 0) {
		return "0000";
	} else if(strcmp("$at", reg) == 0) {
		return "0001";
	} else if(strcmp("$v0", reg) == 0) {
		return "0010";
	} else if(strcmp("$a0", reg) == 0) {
		return "0011";
	} else if(strcmp("$a1", reg) == 0) {
		return "0100";
	} else if(strcmp("$a2", reg) == 0) {
		return "0101";
	} else if(strcmp("$t0", reg) == 0) {
		return "0110";
	} else if(strcmp("$t1", reg) == 0) {
		return "0111";
	} else if(strcmp("$t2", reg) == 0) {
		return "1000";
	} else if(strcmp("$s0", reg) == 0) {
		return "1001";
	} else if(strcmp("$s1", reg) == 0) {
		return "1010";
	} else if(strcmp("$s2", reg) == 0) {
		return "1011";
	} else if(strcmp("$k0", reg) == 0) {
		return "1100";
	} else if(strcmp("$sp", reg) == 0) {
		return "1101";
	} else if(strcmp("$fp", reg) == 0) {
		return "1110";
	} else if(strcmp("$ra", reg) == 0) {
		return "1111";
	}
	return "";
}

char* InstructionRegister(char* instruction, char* params[]) {
	static char memLine[33] = "";

	if(strcmp("0000", instruction) == 0) { //ADD
		char* unused = "0000000000000000";
		char* binReg1 = getBinaryRegister(params[0]);
		char* binReg2 = getBinaryRegister(params[1]);
		char* binReg3 = getBinaryRegister(params[2]);

		strcpy(memLine, instruction);
		strcat(memLine, binReg1);
		strcat(memLine, binReg2);
		strcat(memLine, unused);
		strcat(memLine, binReg3);

		return memLine;
	}
	else if(strcmp("0001", instruction) == 0) { //NAND
		char* unused = "0000000000000000";
		char* binReg1 = getBinaryRegister(params[0]);
		char* binReg2 = getBinaryRegister(params[1]);
		char* binReg3 = getBinaryRegister(params[2]);

		strcpy(memLine, instruction);
		strcat(memLine, binReg1);
		strcat(memLine, binReg2);
		strcat(memLine, unused);
		strcat(memLine, binReg3);

		return memLine;
	}
	else if(strcmp("0010", instruction) == 0) { //ADDI
		char* sign = "";
		char* binReg1 = getBinaryRegister(params[0]);
		char* binReg2 = getBinaryRegister(params[1]);
		char* third = "";
		int num = 0;
		if(strcmp(params[2], "$zero") == 0) {
			third = "0000000000000000000";
		}
		else {
			num = fromAlphaToDec(instruction, params[2]);
			third = fromDecToBin(num);
		}
		if(num >= 0) sign = "0";
		if(num < 0) sign = "1";

		strcpy(memLine, instruction);
		strcat(memLine, binReg1);
		strcat(memLine, binReg2);
		strcat(memLine, sign);
		strcat(memLine, third);

//		for(int i = 0; i < sizeof(memLine); i++) {
//			printf("ADDI %d - %c \n",i, memLine[i]);
//		}

		return memLine;
	}
	else if(strcmp("0011", instruction) == 0) { //LW
		//assuming that the hex number will always be 0x42
		char* hex = "00000000000001000010";
		//TODO
		char *tok;
		char* parameters[2];
		parameters[0] = strtok(params[1], "x");
		parameters[0] = strtok(NULL, "(");
		parameters[1] = strtok(NULL, ")");

		char* binReg = getBinaryRegister(params[0]);
		char* binReg2 = getBinaryRegister(parameters[1]);
		strcpy(memLine, instruction);
		strcat(memLine, binReg);
		strcat(memLine, binReg2);
		strcat(memLine, hex);
		return memLine;
	}
	else if(strcmp("0100", instruction) == 0) { //SW
		//assuming that the hex number will always be 0x42
		char* hex = "00000000000001000010";
		//TODO
		char *tok;
		char* parameters[2];
		parameters[0] = strtok(params[1], "x");
		parameters[0] = strtok(NULL, "(");
		parameters[1] = strtok(NULL, ")");

		char* binReg = getBinaryRegister(params[0]);
		char* binReg2 = getBinaryRegister(parameters[1]);
		strcpy(memLine, instruction);
		strcat(memLine, binReg);
		strcat(memLine, binReg2);
		strcat(memLine, hex);
		return memLine;
	}
	else if(strcmp("0101", instruction) == 0) { //BEQ
		//assuming that the hex number will always be 0x42
//		char* hex = "00000000000001000010";
		//TODO
		char *tok;
		char* parameters[2];
		parameters[0] = strtok(params[1], "x");
		parameters[0] = strtok(NULL, "(");
		parameters[1] = strtok(NULL, ")");

		char* binReg = getBinaryRegister(params[0]);
		char* binReg2 = getBinaryRegister(parameters[1]);
		strcpy(memLine, instruction);
		strcat(memLine, binReg);
		strcat(memLine, binReg2);
//		strcat(memLine, hex);
		return memLine;
	}
	else if(strcmp("0110", instruction) == 0) { //JALR
	}
	else if(strcmp("NOP", instruction) == 0) {
		//????????
	}
	else if(strcmp("0111", instruction) == 0) {
	}
	return "";
}
