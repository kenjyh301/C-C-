/*
 * ArimethicCoding.h
 *
 *  Created on: Dec 4, 2020
 *      Author: minh
 */

#ifndef ARIMETHICCODING_H_
#define ARIMETHICCODING_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


float mencode(char* s,int length);

void mGetValue(float min,float max,int room,char c,float* afterRange);

void mdecode(long double value,int length);


#endif /* ARIMETHICCODING_H_ */
