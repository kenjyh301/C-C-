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

uint8_t data[6120];
FILE *f;
int Package_index=0;

void initFreq() {

	memset(freq, 0, 256 * 2);


	uint8_t header[] = { 0, 0 };

	memset(data, 0, 6120);
	while (header[0] != 0xaa) {
		fread(header, 2, 1, f);
//		printf("%d\n", header[0]);
	}
	fread(data, 6120, 1, f);
	uint8_t *ch;
	for (int i = 0; i < 6120; i++) {
		ch = data[i];
		int index = (int) ch;
		//		if(freq[index]<256)
		freq[index]++;
	}
	Package_index++;
//	for (int i = 0; i < 256; i++) {
//		if (i % 8 == 0)
//			printf("\n");
//		printf("%d  ", (int) freq[i]);
//	}
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
	uint8_t *output;
	output = mEncode((char*) "abababcdca", 10);
	char *ret;
	ret = mDecode(output, 19, 10);
	for (int i = 0; i < 10; i++) {
		printf(" %c ", ret[i]);
	}
}

void print_result(char* ret,int length){
//	printf("\ndata in: ");
//
//	for (int i = 0; i < length; i++) {
//		printf("%hhx  ", data[i]);
//	}
//
//	printf("\ndata out: ");
//
//	for (int i = 0; i < length; i++) {
//		printf(" %hhx ", ret[i]);
//	}

	printf("\n Efficient: %f", output_size / 6120.0 * 100.0);
}


int main() {
//	testCase();




	f = fopen("log.log", "r");
	if (f == NULL)
		printf("open file not ok\n");
	else
		printf("open file successfully\n");

for(int i=0;i<45;i++){
	initFreq();

	printf("\n");

	for(int i=0;i<100;i++){
		printf("%hhx  ",data[i]);
	}
	printf("\n");

	mBuildTree(0);
	createMap();
//	for (int i = 0; i < 10; i++) {
//		int index=(uint8_t)data[i];
//		printf("\ncode:%hhx + size:%d    ",mapping[index].code, mapping[index].size);
//	}
	uint8_t *output;

	int length=6120;
	output = mEncode(data, length);
//	printf("a%hhx  \n",output[output_size-1]);
//	printf("a%hhx  \n",output[output_size-2]);
//	printf("%d %d",decode_size,output_size -1);

	char *ret;
//
//
//	printf("")
	ret = mDecode(output, decode_size, length);
	if(ret==NULL)return 1;

	print_result(ret,length);

//	map m= mapping[1];
//	node_t* node= topNode->left->right->right;
}
	return 0;
}

