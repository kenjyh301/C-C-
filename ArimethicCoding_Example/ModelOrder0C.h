/*
 * ModelOrder0C.h
 *
 *  Created on: Dec 4, 2020
 *      Author: minh
 */

#ifndef MODELORDER0C_H_
#define MODELORDER0C_H_

#include "ModelI.h"
class ModelOrder0C: public ModelI {
public:
	ModelOrder0C();
protected:
	void Encode();
	void Decode();
	unsigned int mCumCount[257];
	unsigned int mTotal;
};

#endif /* MODELORDER0C_H_ */
