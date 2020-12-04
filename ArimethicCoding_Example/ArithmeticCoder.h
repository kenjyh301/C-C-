/*
 * ArithmeticCoder.h
 *
 *  Created on: Dec 4, 2020
 *      Author: minh
 */

#ifndef ARITHMETICCODER_H_
#define ARITHMETICCODER_H_

#include <fstream>
#include <iostream>
using namespace std;
class ArithmeticCoderC{
	public:ArithmeticCoderC();
	void SetFile( fstream *file );
	void Encode( const unsigned int low_count,const unsigned int high_count,const unsigned int total );
	void EncodeFinish();void DecodeStart();unsigned int DecodeTarget( const unsigned int total );
	void Decode( const unsigned int low_count,const unsigned int high_count );
	protected:// bit operations
	void SetBit( const unsigned char bit );
	void SetBitFlush();
	unsigned char GetBit();
	unsigned char mBitBuffer;
	unsigned char mBitCount;// in-/output
	fstream *mFile;// encoder & decoderunsigned
	int mLow;
	unsigned int mHigh;

	unsigned int mStep;
	unsigned int mScale;// decoder
	unsigned int mBuffer;
};

#endif /* ARITHMETICCODER_H_ */
