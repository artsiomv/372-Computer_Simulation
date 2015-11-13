/*
 * Memory.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct parameter_str {
	char* par;
} Parameter;

typedef struct instruction_str {
    char* instruction;
	int counter;
    Parameter pars[4];
} Instruction;

int Memory(char* instruction, char* params[], int numberOfParameters, int lines) {
	Instruction instructs[100]; // <-  this line indicates how many lines is maximum in the file.
	instructs[lines].counter = numberOfParameters;
	instructs[lines].instruction = instruction;
	for(int i = 0; i < numberOfParameters; i++) {
		instructs[lines].pars[i].par = params[i];
	}

	return 0;
}

int getMemory() {

}
