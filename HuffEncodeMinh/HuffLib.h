/*
 * HuffLib.h
 *
 *  Created on: Dec 5, 2020
 *      Author: minh
 */

#ifndef HUFFLIB_H_
#define HUFFLIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pqueue.h"
#include <math.h>

pqueue_t* pqueue;
uint16_t freq[256];

int decode_size=0;
int output_size;

extern int Package_index;
extern uint8_t data[];

typedef struct{
	char code;
	int size;
}map;

map mapping[256];

//typedef struct MinHeapNode {
//	char data;
//	struct MinHeapNode *left, *right;
//} MinHeapNode;

typedef struct node_t
{
	pqueue_pri_t pri;
	char data;
	struct node_t *left, *right;
	size_t pos;
} node_t;

node_t* topNode;

static int
cmp_pri(pqueue_pri_t next, pqueue_pri_t curr)
{
	return (next > curr);
}


static pqueue_pri_t
get_pri(void *a)
{
	return ((node_t *) a)->pri;
}


static void
set_pri(void *a, pqueue_pri_t pri)
{
	((node_t *) a)->pri = pri;
}


static size_t
get_pos(void *a)
{
	return ((node_t *) a)->pos;
}


static void
set_pos(void *a, size_t pos)
{
	((node_t *) a)->pos = pos;
}

node_t* initNode(pqueue_pri_t pri,char data,node_t* left,node_t* right){
	node_t* ret=(node_t*)malloc(sizeof(node_t));
	ret->pri=pri;
	ret->data=data;
	ret->left=left;
	ret->right=right;
	return ret;
}


void mBuildTree(int size) {
	node_t *left, *right, *top;
	int maxBranch=8;

	int nodes = 0;
	for (int i = 0; i < 256; i++) {
		if (freq[i] != 0)
			nodes++;
	}

	pqueue=pqueue_init(nodes, cmp_pri, get_pri, set_pri, get_pos, set_pos);

	for (int i = 0; i < 256; i++) {
		if (freq[i] != 0) {
			node_t *tmp;
			tmp= initNode(freq[i], i, NULL, NULL);
			pqueue_insert(pqueue, tmp);
		}
	}

	while(pqueue_size(pqueue)>1){
		int Q_size= pqueue_size(pqueue);
		if(pqueue_size(pqueue)<=maxBranch+1) break;

		int num_newNode= Q_size/2;
		node_t** new_node= (node_t**)malloc(num_newNode*(sizeof(node_t*)));
		for(int i=0;i<num_newNode;i++){
//			new_node[i]= (node_t*)malloc(sizeof(node_t));
			node_t* popNode = (node_t*)pqueue_pop(pqueue);
			left = popNode;
			popNode = (node_t*) pqueue_pop(pqueue);
			right = popNode;
			new_node[i]=initNode(left->pri+right->pri, '$', left, right);
		}

		for(int i=0;i<num_newNode;i++){
			pqueue_insert(pqueue, new_node[i]);
		}

		maxBranch--;


	}


	while (pqueue_size(pqueue)>1) {
		node_t* popNode = (node_t*)pqueue_pop(pqueue);
		left= popNode;
		popNode = (node_t*)pqueue_pop(pqueue);
		right = popNode;
//		top = initMinHeap('$', left, right);
		top= initNode(left->pri+right->pri, '$', left, right);
		pqueue_insert(pqueue, top);
	}
	topNode = (node_t*)pqueue_pop(pqueue);
}

void printCode(node_t* topNode,char code,int size){
	if(topNode->left!=NULL){
		code=code<<1|0;
		size++;
		char c= topNode->data;
		printCode(topNode->left,code,size);
		size--;
		code=code>>1;
	}else{
		int index=(uint8_t)topNode->data;
		map m;
		m.code= code;
		m.size= size;
		mapping[index].code=m.code; //copy m to maaping indexth
		mapping[index].size= m.size;
		if(size>8)printf("\nsize too large %d %d",index,mapping[index].size);
	}

	if(topNode->right){
		code = code << 1 | 1;
		size++;
		char c= topNode->data;
		printCode(topNode->right, code, size);
		size--;
		code=code>>1;
	}
}

void createMap(){

	memset(mapping,0,sizeof(map)*256);

	printCode(topNode,0,0);
}


void shiftBitThrough(uint8_t data,uint8_t* buffer,int bit_length,int buffer_length){

}

uint8_t* mEncode(char* s,int length){
	int sizeInBit=0;
	for(int i=0;i<length;i++){
		int index= (uint8_t)s[i];
		sizeInBit+=mapping[index].size;
	}

	decode_size= sizeInBit;

	int buffer_size= ceil(sizeInBit/8.0);

	output_size= buffer_size;

	uint8_t* buffer= (uint8_t*)malloc(buffer_size*sizeof(uint8_t));
	memset(buffer,0,buffer_size*sizeof(uint8_t));
//	int separate=0;

	char* test=buffer+193;

	for(int i=length-1;i>=0;i--){
		int byte_end= (sizeInBit-1)/8;
		int mapping_index= (uint8_t)s[i];
		int byte_start= (sizeInBit-mapping[mapping_index].size)/8;

		if(byte_start==byte_end)// data in the same byte
		{
			char m=s[i];
			uint8_t tmp=mapping[mapping_index].code;
			int shift= sizeInBit-mapping[mapping_index].size - byte_start*8;
			tmp<<=shift;


			buffer[byte_start]|=tmp;

			sizeInBit-=mapping[mapping_index].size;
		}
		//data in different byte
		else{
			char c= mapping_index;
			uint16_t tmp=(uint8_t)mapping[mapping_index].code;
			int shift= sizeInBit-mapping[mapping_index].size - byte_start*8;
			tmp<<=shift;
			buffer[byte_end]|=(uint8_t)(tmp>>8);
			buffer[byte_start]|=(uint8_t)(tmp);
			sizeInBit-=mapping[mapping_index].size;
		}
	}

//	for(int i=0;i<buffer_size;i++){
//		printf("a%d   %hhx   ",i,buffer[i]);
//	}
	return buffer;
}




char* mDecode(uint8_t* input,int sizeInBit,int length){
	char* answer= (char*)malloc(length);
	int index=length;
	node_t* itearator= topNode;
	for(int i= sizeInBit-1;i>=0;i--){
		int bytePos= i/8;
		int bitPos= i-bytePos*8;
		uint8_t check= 1<<bitPos;
		//if bit =1
		if(input[bytePos]&check){
			itearator= itearator->right;
		}else itearator= itearator->left;

		if(itearator->left==NULL){
			index--;
			answer[index]=itearator->data;
			itearator= topNode;
		}

		//input error check
		if(index<0&&i>=0){
			printf("buffer too short\n");
			return NULL;
		}
	}

	if(index>0) {
		printf("buffer define long than data  %d  %d\n",index,Package_index);
		return NULL;
	}
	for(int i=0;i<length;i++){
		if((uint8_t)answer[i]!=data[i]){
			printf("Wrong result in value %d\n",i);
		}
	}
	printf("Decode success");
	return answer;
}

#endif /* HUFFLIB_H_ */
