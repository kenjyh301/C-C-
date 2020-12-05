/*
 * ArimethicCoding.c
 *
 *  Created on: Dec 4, 2020
 *      Author: minh
 */

#include "ArimethicCoding.h"
#include <math.h>

int i=0;

float mencode(char* s,int length){

	int room=256;

//	float value=0;
//	float tmp=0;
	float afterRange[2];
	mGetValue(0, 1, 64, s[0], afterRange);

	for(i=1;i<length;i++){
		if(i%2==0) room=64;
		else{
			room=256;
		}
		mGetValue(afterRange[0], afterRange[1], room, s[i],afterRange);
	}
	return afterRange[0];
}

void mGetValue(float min,float max,int room,char c,float* afterRange){
	int index= c;
	float range= (max-min)/room;
	afterRange[0]= min+range*index;
	afterRange[1]=afterRange[0]+range;
}

uint8_t detectRange(long double* afterRange,int room,long double value){
	long double max= afterRange[1];
	long double min= afterRange[0];
	long double range= (max-min)/room;
	int index= (value-min)/range;
	printf("%d  ",index);
	afterRange[0]= min+index*range;
	afterRange[1]= afterRange[0]+range;
	if(value==afterRange[0]){
		return 1;
	}
	else return 0;
}

void mdecode(long double value,int length){
	int index=0;
	int room=2;
	int count=0;
	long double afterRange[]={0.0,1.0};
	while(1){
		if(index%2==0)room=64;
		else room=256;
		uint8_t ret=detectRange(afterRange, room, value);
		index++;
		if(ret)break;

		if(index==length)break;
	}
}

