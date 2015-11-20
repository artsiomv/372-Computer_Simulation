/*
 * Memory.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

int32_t my_32bit_int;

typedef struct instruction{
	unsigned int opcode;
	unsigned int reg1;
	unsigned int reg2;
	unsigned int rest;
} Instruction;

typedef struct memoryHeap{
	Instruction inst[100];
} Heap;
static void* heap;
static Heap* root = NULL;

void create_pool(int size) {
    heap = malloc(size);
//    printf("%lu\n", sizeof(Line));
    //give it a storage
    root = malloc(sizeof(Heap));

    //create the pool
    if(heap == NULL) {
        printf ("Failed to allocate space for %d bytes\n", size);
        return;
    }
//    printf("%lu\n", sizeof(Heap));
    root = heap;
//    root->info.blockSize = size;
}

int Memory(char* memoryLine, int lines) {
	Heap* current = root;

	int instruction = 0;
	int opcode = 0;
	int reg1 = 0;
	int reg2 = 0;
	int rest = 0;
	int i;
	//get opcode
	for(i = 0; i < 4; i++) {
		if(memoryLine[i]== '1') opcode = opcode * 10 + 1;
		else opcode = opcode * 10;
	}
	current->inst[lines].opcode = opcode;
	//get first register
	for(i = 4; i < 8; i++) {
		if(memoryLine[i]== '1') reg1 = reg1 * 10 + 1;
		else reg1 = reg1 * 10;
	}
	current->inst[lines].reg1 = reg1;
	//get second register
	for(i = 8; i < 12; i++) {
		if(memoryLine[i]== '1') reg2 = reg2 * 10 + 1;
		else reg2 = reg2 * 10;
	}
	current->inst[lines].reg2 = reg2;
	//get the rest of the numbers
	for(i = 12; i < 32; i++) {
		if(memoryLine[i]== '1') rest = rest * 10 + 1;
		else rest = rest * 10;
	}
	current->inst[lines].rest = rest;

//	printf("M %04d%04d%04d%020d\n", current->inst[lines].opcode, current->inst[lines].reg1, current->inst[lines].reg2, current->inst[lines].rest);


//	for(int k = 0; k < 3; k++) {
//		printf("+%04d%04d%04d%020d\n", current->inst[k].opcode, current->inst[k].reg1, current->inst[k].reg2, current->inst[k].rest);
//	}

	return 0;
}

Instruction getMemory(int i) {
//	printf("%d\n", root->inst[i].opcode);
	return root->inst[i];
}
