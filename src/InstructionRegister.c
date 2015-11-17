/*
 * InstructionRegister.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */

#include <stdio.h>
#include <string.h>
#include "InstructionRegister.h"

char* InstructionRegister(char* instruction, char* params[], int numberOfParameters) {
	int pars[numberOfParameters];
	int numberRetrieved;
	for(int i = 0; i < numberOfParameters; i++) {
		printf("PARS %s \n", params[i]);
	}

	char* binary;

	if(strcmp("ADD", instruction) == 0) {

		binary = "0000";
	}
	else if(strcmp("NAND", instruction) == 0) {
		binary = "0001";
	}
	else if(strcmp("ADDI", instruction) == 0) {
		//TODO
		binary = "0010";
	}
	else if(strcmp("LW", instruction) == 0) {
		for(int i = 1; i < numberOfParameters; i++) {
			pars[i] = loadFrom(params[i]);
		}
		binary = "0011";
	}
	else if(strcmp("SW", instruction) == 0) {
		loadTo(params);
	}
	else if(strcmp("BEQ", instruction) == 0) {
		binary = "0101";
	}
	else if(strcmp("JALR", instruction) == 0) {
		binary = "0110";
	}
	else if(strcmp("NOP", instruction) == 0) {
		//????????
	}
	else if(strcmp("HALT", instruction) == 0) {
		binary = "0111";
	}
	else if(strcmp("EI", instruction) == 0) {
		//????????
	}
	else if(strcmp("DI", instruction) == 0) {
		//?????????
	}
	else if(strcmp("RETI", instruction) == 0) {
		//??????????
	}
	else {
		binary = "24";
	}
	return binary;
}

