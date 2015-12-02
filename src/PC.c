/*
 * PC.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */
#include <stdio.h>
#include <string.h>
int counter = 0;
void setPC(int num) {
//	printf("<><><PCS><><> %d\n", counter);
	counter = num;
//	printf("<><><PCS><><> %d\n", counter);
}
int getPC() {
//	printf("<><><PCG><><> %d\n", counter);
	return counter;
}

