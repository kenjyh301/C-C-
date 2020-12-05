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
#include "PQ.h"


pq_t NodeQueue;
uint16_t freq[256];

typedef struct MinHeapNode{
	char data;
	uint8_t freq;

	struct MinHeapNode *left,*right;
}MinHeapNode;


pq_compare_f compareNode(MinHeapNode* a, MinHeapNode* b){
	return a->freq>b->freq;
}

//typedef struct MinHeapSortQueue{
//	unsigned int size;
//	unsigned int capacity;
//	struct MinHeapNode** array;
//}MinHeapSortQueue;

MinHeapNode* initNode(int data,uint8_t freq,MinHeapNode *l, MinHeapNode *r){
	MinHeapNode* ret;
	ret->data=data;
	ret->freq=freq;
	ret->left=l;
	ret->right=r;
	return ret;
}

//MinHeapSortQueue* initNodeQueue(){
//	MinHeapSortQueue* ret= (MinHeapSortQueue*)malloc(sizeof(MinHeapSortQueue));
//	ret->size=0;
//	ret->capacity=256;
//	ret->array= (MinHeapSortQueue**)malloc(ret->capacity*sizeof(MinHeapSortQueue*));
//	return ret;
//}

//void swapNode(MinHeapNode** a,MinHeapNode** b){
//	MinHeapNode* tmp=a;
//	*a=*b;
//	*b=tmp;
//}

void mEndcode(int size){
	MinHeapNode *left,*right,*top;
	int nodes=0;
	for(int i=0;i<256;i++){
		if(freq[i]!=0)nodes++;
	}
	NodeQueue= pq_new_queue(nodes*sizeof(MinHeapNode*), compareNode, NULL);

	for(int i=0;i<256;i++){
		if(freq[i]!=0){
			MinHeapNode* tmp;
			tmp=initNode(i, freq[i], NULL, NULL);
			pq_enqueue(NodeQueue, tmp, NULL);// maybe not true

		}
	}

	while(pq_number_of_entries(NodeQueue)>1){
		left= pq_dequeue(NodeQueue, NULL);
		right= pq_dequeue(NodeQueue, NULL);
		top= initNode('$', left->freq+right->freq, left, right);
		pq_enqueue(NodeQueue, top, NULL);
	}
}



#endif /* HUFFLIB_H_ */
