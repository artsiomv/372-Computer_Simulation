/*
 * Registers.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct register_str {
	int numberStored;
	char* binaryNumberStored;
} Register;
	//maybe make a random values?
	int $zero = 0;
	int $at = 0;
	int $v0 = 0;
	int $a0 = 0;
	int $a1 = 0;
	int $a2 = 0;
	int $t0 = 0;
	int $t1 = 0;
	int $t2 = 0;
	int $s0 = 0;
	int $s1 = 0;
	int $s2 = 0;
	int $k0 = 0;
	int $sp = 0;
	int $fp = 0;
	int $ra = 0;

int loadTo(int reg, int num) {
	char* ptr;

	if(reg == 0) {
		//can't write here, this is $zero
	}
	else if(reg == 1) {
		$at = num;
	}
	else if(reg == 10) {
		$v0 = num;
	}
	else if(reg == 11) {
		$a0 = num;
	}
	else if(reg == 100) {
		$a1 = num;
	}
	else if(reg == 101) {
		$a2 = num;
	}
	else if(reg == 110) {
		$t0 = num;
	}
	else if(reg == 111) {
		$t1 = num;
	}
	else if(reg == 1000) {
		$t2 = num;
	}
	else if(reg == 1001) {
		$s0 = num;
	}
	else if(reg == 1010) {
		$s1 = num;
	}
	else if(reg == 1011) {
		$s2 = num;
	}
	else if(reg == 1100) {
		$k0 = num;
	}
	else if(reg == 1101) {
		$sp = num;
	}
	else if(reg == 1110) {
		$fp = num;
	}
	else if(reg == 1111) {
		$ra = num;
	}
	return 0;
}

int loadFrom(int reg) {
	if(reg == 0) {
		return $zero;
	}
	else if(reg == 1) {
		return $at;
	}
	else if(reg == 10) {
		return $v0;
	}
	else if(reg == 11) {
		return $a0;
	}
	else if(reg == 100) {
		return $a1;
	}
	else if(reg == 101) {
		return $a2;
	}
	else if(reg == 110) {
		return $t0;
	}
	else if(reg == 111) {
		return $t1;
	}
	else if(reg == 1000) {
		return $t2;
	}
	else if(reg == 1001) {
		return $s0;
	}
	else if(reg == 1010) {
		return $s1;
	}
	else if(reg == 1011) {
		return $s2;
	}
	else if(reg == 1100) {
		return $k0;
	}
	else if(reg == 1101) {
		return $sp;
	}
	else if(reg == 1110) {
		return $fp;
	}
	else if(reg == 1111) {
		return $ra;
	}
	return 0;
}

int getRegInfo(int num) {
	if(num == 0) return $zero;
	if(num == 1) return $at;
	if(num == 2) return $v0;
	if(num == 3) return $a0;
	if(num == 4) return $a1;
	if(num == 5) return $a2;
	if(num == 6) return $t0;
	if(num == 7) return $t1;
	if(num == 8) return $t2;
	if(num == 9) return $s0;
	if(num == 10) return $s1;
	if(num == 11) return $s2;
	if(num == 12) return $k0;
	if(num == 13) return $sp;
	if(num == 14) return $fp;
	if(num == 15) return $ra;
	else return -1;
}
