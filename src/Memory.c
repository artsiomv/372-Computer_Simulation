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
#include "main.h"

#include <stdint.h>

int32_t my_32bit_int;

typedef struct instruction{
	char memoryLine[33];
} Instruction;

typedef struct memoryHeap{
	Instruction inst[5000];
} Heap;
static void* heap;
static Heap* root;

void create_pool(int size) {
    heap = malloc(size);
    //give it a storage
    root = malloc(sizeof(Heap));

    if(heap == NULL) {
        printf ("Failed to allocate space for %d bytes\n", size);
        return;
    }
    root = heap;
    Heap* current = root;
    for(int i = 0; i < 5000; i++) {
    	memset(current->inst[i].memoryLine, 0, sizeof(current->inst[i].memoryLine));
    	strcpy(current->inst[i].memoryLine, fromDecToBin((abs((int)current->inst[i].memoryLine))%10000));
    }
}

int Memory(char* memoryLine, int lines) {
//	printf("................................ %d\n", heap);
//	printf("MemL %d\n", lines);
	Heap* current = root;
	strcpy(current->inst[lines].memoryLine, memoryLine);
//	printf("LLLLLTTTTTLLLLL  %d\n", root->inst[2004].reg1);
	return 0;
}

char* getMemory(int i) {
//	printf("TTTTTTTTTTT %d\n", root->num);
	return root->inst[i].memoryLine;
}

