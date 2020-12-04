/*
 * ModelI.h
 *
 *  Created on: Dec 4, 2020
 *      Author: minh
 */

#ifndef MODELI_H_
#define MODELI_H_

#include "ArithmeticCoder.h"
#include <iostream>
#include <fstream>
enum ModeE {
	MODE_ENCODE = 0, MODE_DECODE
};
class ModelI {
public:
	void Process(fstream *source, fstream *target, ModeE mode);
protected:
	virtual void Encode() = 0;
	virtual void Decode() = 0;
	ArithmeticCoderC mAC;
	fstream *mSource;
	fstream *mTarget;
};

#endif /* MODELI_H_ */
