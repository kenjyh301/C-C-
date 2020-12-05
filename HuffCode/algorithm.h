/*
 * algorithm.h
 *
 *  Created on: Dec 5, 2020
 *      Author: minh
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_


//extern int maxcodelen;

struct pixfreq
{
    int pix;
    float freq;
    struct pixfreq *left, *right;
    char code[17];
};

struct huffcode
 {
    int pix, arrloc;
    float freq;
};



#endif /* ALGORITHM_H_ */
