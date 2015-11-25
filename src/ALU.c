/*
 * ALU.c
 *
 *  Created on: Nov 3, 2015
 *      Author: Artiom
 */

int ALU(int A, int B, int func)
{
	//output from the calculations
	int answer;

	//function passed into ALU
	/*
	 * We need to pass in the func, (00 for ADD, 01 for NAND, 10 for A - B, and 11 for A + 1)
	 * We need the func to be passed in because that way we know what operations we are doing
	 * Im not sure how to pass in value to this "class"
	 */

	//ADD
	if (func == 0)
	{
		answer = A + B;
	}
	//NAND
	else if (func == 1)
	{
		//have to get binary, then AND it, and then do NOT on it
		//not sure how to do
	}
	//A-B
	else if (func == 10)
	{
		answer = A - B;
	}
	//A + 1 (increment)
	else if (func == 11)
	{
		answer = A + 1;
	}

	return answer;
}
