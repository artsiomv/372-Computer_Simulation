/*
 * InstructionRegister.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "InstructionRegister.h"
#include <stdlib.h>

int fromAlphaToDec(char* parameter) {
	char* pars = parameter;
	int negative = 0;
	int k;
	int num = 0;
	int len = strlen(parameter);
	for(k = 0; k < len-1; k++) {
		if(pars[k] == '-') {
			negative = 1;
		} else {
			int tempNum = (int)pars[k]-48;
			num = num + tempNum;
			num = num*10;
		}
	}
	int tempNum = (int)pars[k]-48;
	num = num + tempNum;

	if(negative == 1) num *= -1;
	return num;
}

char* fromDecToBin(int num) {
	static char bin[25];
	memset(bin, 0, sizeof(bin));
	int num2 = num;
	if(num < 0) num2 = (num2 *(-1));
	int i = 262144;
	while(i >= 1) {
		if(num2 - i >= 0) {
			strcat(bin, "1");
			num2 = num2 - i;
		} else strcat(bin, "0");
		i /= 2;
	}
	if(num < 0) {
		char result[25];
		strcpy(result, "");
		int i;
		for(i = 0; i < strlen(bin); i++) {
			if(bin[i] == '1') strcat(result, "0");
			else if(bin[i] == '0') strcat(result, "1");
		}
		strcpy(bin, result);
	}
	return bin;
}

int fromBinToDec(char* bin) {
	//find imm value
	int num = 0;
	int i;
	for(i = 0; i < strlen(bin); i++) {
		if(bin[i] == '1') num = num*2+1;
		else num = num*2+0;
	}
	return num;
}

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

void getRTypeInstructionInfo(char memLine[], char* instruction, char* params[]) {
	char* unused = "0000000000000000";
	char* binReg1 = getBinaryRegister(params[0]);
	char* binReg2 = getBinaryRegister(params[1]);
	char* binReg3 = getBinaryRegister(params[2]);

	strcpy(memLine, instruction);
	strcat(memLine, binReg1);
	strcat(memLine, binReg2);
	strcat(memLine, unused);
	strcat(memLine, binReg3);
}

void getITypeInstructionInfoLWSW(char memLine[], char* instruction, char* params[]) {
	char hex[20];
	char* sign = "";

	static char* parameters[2];
	parameters[0] = strtok(params[1], "x");
	parameters[0] = strtok(parameters[0], "(");

	int num = fromAlphaToDec(parameters[0]);
	char* in = fromDecToBin(num);
	strcpy(hex, in);
	parameters[1] = strtok(NULL, ")");

	if(num >= 0) sign = "0";
	if(num < 0) sign = "1";

	char* binReg = getBinaryRegister(params[0]);
	char* binReg2 = getBinaryRegister(parameters[1]);
	strcpy(memLine, instruction);
	strcat(memLine, binReg);
	strcat(memLine, binReg2);
	strcat(memLine, sign);
	strcat(memLine, hex);
}

void getADDIInstructionInfo(char memLine[], char* instruction, char* params[]) {
	char* sign = "";
	char* binReg1 = getBinaryRegister(params[0]);
	char* binReg2 = getBinaryRegister(params[1]);
	char* third = "";
	int num = 0;
	if(strcmp(params[2], "$zero") == 0) {
		third = "0000000000000000000";
	}
	else {
		num = fromAlphaToDec(params[2]);
		third = fromDecToBin(num);
	}
	if(num >= 0) sign = "0";
	if(num < 0) sign = "1";

	strcpy(memLine, instruction);
	strcat(memLine, binReg1);
	strcat(memLine, binReg2);
	strcat(memLine, sign);
	strcat(memLine, third);
}

char* InstructionRegister(char* instruction, char* params[]) {
	static char memLine[33] = "";
	memset(memLine, 0, sizeof(memLine));
	//.ORIG
	if(strcmp(".ORIG", instruction) == 0) {
		int orig = fromAlphaToDec(params[0]);
		char *start = fromDecToBin(orig);
		char* before = "0000000000000";
		strcpy(memLine, before);
		strcat(memLine, start);
		setPC(orig);
		return memLine;
	}
	else if(strcmp(".END", instruction) == 0){
		return "00000000000000000000000000000000";
	}
	/*****************************************/
	/******************ADD********************/
	/*****************************************/
	else if(strcmp("0000", instruction) == 0) { //ADD
		getRTypeInstructionInfo(memLine, instruction, params);
		return memLine;
	}

	/*****************************************/
	/******************NAND*******************/
	/*****************************************/
	else if(strcmp("0001", instruction) == 0) { //NAND
		getRTypeInstructionInfo(memLine, instruction, params);
		return memLine;
	}
	/*****************************************/
	/******************ADDI*******************/
	/*****************************************/
	else if(strcmp("0010", instruction) == 0) { //ADDI
		getADDIInstructionInfo(memLine, instruction, params);
		return memLine;
	}
	/*****************************************/
	/*******************LW********************/
	/*****************************************/
	else if(strcmp("0011", instruction) == 0) { //LW
		getITypeInstructionInfoLWSW(memLine, instruction, params);
		return memLine;
	}
	/*****************************************/
	/*******************SW********************/
	/*****************************************/
	else if(strcmp("0100", instruction) == 0) { //SW
		getITypeInstructionInfoLWSW(memLine, instruction, params);
		return memLine;
	}
	/*****************************************/
	/******************BEQ********************/
	/*****************************************/
	else if(strcmp("0101", instruction) == 0) { //BEQ
		//too hard to implement, needs further research
		//TODO
		char* parameters[2];
//
		char* binReg = getBinaryRegister(params[0]);
		char* binReg2 = getBinaryRegister(params[1]);
		strcpy(memLine, instruction);
		strcat(memLine, binReg);
		strcat(memLine, binReg2);
		strcat(memLine, params[2]);
		return memLine;
	}
	/*****************************************/
	/******************JALR*******************/
	/*****************************************/
	else if(strcmp("0110", instruction) == 0) { //JALR

	}
	return "";
}
