/*
 * main.c
 *
 *  Created on: Dec 4, 2020
 *      Author: minh
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#include "ArimethicCoding.h"

int main(){
	char s[]={0x33,0x0D,0x00,0xF6,0x3F,0x20};

	float value= mencode(s, 6);
//	printf("%s\n",s);
	printf("%30.28f",value);
	printf("\n");

	long double value1=value;
	mdecode(value1,6);
	return 0;
}




