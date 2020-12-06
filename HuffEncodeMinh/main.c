/*
 * main.c
 *
 *  Created on: Dec 5, 2020
 *      Author: minh
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "HuffLib.h"
#include "pqueue.h"

void initFreq() {
	FILE *f;
	memset(freq, 0, 256 * 2);
	f = fopen("log.log", "r");
	if (f == NULL)
		printf("open file not ok\n");
	else
		printf("open file successfully\n");
	uint8_t header[] = { 0, 0 };
	uint8_t data[6120];
	memset(data, 0, 6120);
	while (header[0] != 0xaa) {
		fread(header, 2, 1, f);
		printf("%d\n", header[0]);
	}
	fread(data, 6120, 1, f);
	uint8_t *ch;
	for (int i = 0; i < 6120; i++) {
		ch = data[i];
		int index = (int) ch;
		//		if(freq[index]<256)
		freq[index]++;
	}
	for (int i = 0; i < 256; i++) {
		if (i % 8 == 0)
			printf("\n");
		printf("%d  ", (int) freq[i]);
	}
}


//abababcdca --4a 3b 2c 1d
void testCase(){
	memset(freq, 0, 256 * 2);
	freq['a']=4;
	freq['b']=3;
	freq['c']=2;
	freq['d']=1;
	mBuildTree(0);
	createMap();
	printf("%d  %d  %d  %d\n", mapping['a'].code, mapping['b'].code,
			mapping['c'].code, mapping['d'].code);
	printf("%d  %d  %d  %d\n", mapping['a'].size, mapping['b'].size,
				mapping['c'].size, mapping['d'].size);
}


int main() {
	testCase();
	uint8_t* output;
	mEncode((char*)"abababcdca", output, 10);
	return 0;
}

