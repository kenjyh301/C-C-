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

//MinHeapNode* initMinHeap(int data,MinHeapNode *l, MinHeapNode *r) {
//	MinHeapNode *ret;
//	ret->data = data;
//	ret->left = l;
//	ret->right = r;
//	return ret;
//}

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
		mapping[index]=m; //copy m to maaping indexth
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

void mEncode(char* s,uint8_t* output,int length){
	int sizeInBit=0;
	for(int i=0;i<length;i++){
		sizeInBit+=mapping[s[i]].size;
	}
	int buffer_size= ceil(sizeInBit/8.0);
	uint8_t* buffer= (uint8_t*)malloc(buffer_size*sizeof(uint8_t));

//	int separate=0;

	for(int i=length-1;i>=0;i--){
		int byte_end= sizeInBit/8;
		int byte_start= (sizeInBit-mapping[s[i]].size)/8;

		if(byte_start==byte_end)// data in the same byte
		{
			uint8_t tmp=mapping[s[i]].code;
			int shift= sizeInBit-mapping[s[i]].size - byte_start*8;
			tmp<<=shift;
			buffer[byte_start]|=tmp;
		}
		//data in different byte
		else{
			uint16_t tmp=mapping[s[i]].code;
			int shift= sizeInBit-mapping[s[i]].size - byte_start*8;
			tmp<<=shift;
			buffer[byte_end]|=(uint8_t)(tmp>>8);
			buffer[byte_start]|=(uint8_t)(tmp);
		}
	}

	for(int i=0;i<buffer_size;i++){
		printf("%hhx   ",buffer[i]);
	}
	output=buffer;
}

#endif /* HUFFLIB_H_ */
