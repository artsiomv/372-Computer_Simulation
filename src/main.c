/*
 ============================================================================
 Name        : 372-Simulator.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

//int printOut(Instruction* inst, int numberOfLines, FILE* outFile) {
//	int i, j;
//	for (i = 0; i < 1; i++) {
//		fprintf(outFile, "\n%s", &inst[i].instruction);
//		for (j = 0; j < 3; j++) { //sizeof(inst->pars) / sizeof(inst[0])
//			fprintf(outFile, "\n%s", &inst[i].pars[j].par);
//		}
//	}
////	    for (i = 0; i < numberOfCustomers; i++) {
////	        fprintf(outFile, "\n%s\n", customer[i].customerNames);
////	        for (j = 0; j < customer[i].counter; j++) {
////	            fprintf(outFile, "%s %d $%.2lf\n", customer[i].itemList[j].nameTag,customer[i].itemList[j].amount,customer[i].itemList[j].price );
////	        }
////	    }
//	return 0;
//}

int decode(char* instruction, char* parameters, int lines) {
	char* params[10];

	/* get the first token */
	strtok(parameters, ", ");

	int i = 0;
	/* walk through other tokens */
	while( parameters != NULL ) {
		params[i] = parameters;
		//split on comma and space
		parameters = strtok(NULL, ", ");
		i++;
	}

	//send instruction to the instruction register to get binary
	char* binaryInstruction = InstructionRegister(instruction, params, i);


//	Memory(instruction, params, i, lines);

//	for(int j = 0; j < i; j++) {
//		printf("%d- %s\n",j, params[j]);
//	}
//	printf("\n");

	return 0;
}
int scanInput(FILE* inputFile, int lines) {
	char instruction[100];
	char* parameters;
	char* waste;

	while (feof(inputFile) == 0) {
		if (fgets(instruction, 200, inputFile) != NULL) {

			//split on semicolon
			strtok_r(instruction, ";", &waste);

			//split on first space
			strtok_r(instruction, " ", &parameters);

			lines++;
//			printf("%d\n", lines);
			//decode the text into different variables
			decode(instruction, parameters, lines);
		}
	}
	return 0;
}

int main(void) {
	FILE* inputFile = fopen("input.txt", "r");
	FILE* outputFile = fopen("output.txt", "w");
	int lines = 0;
	scanInput(inputFile, lines);

//	printOut(*inst, numberOfLines, outputFile); fputs(str, outputFile);
}

