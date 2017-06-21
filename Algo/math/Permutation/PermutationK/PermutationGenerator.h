/*
* PermutationGenerator.h
*
*  Created on: 2010-11-11
*      Author: LQW
*/
#include "HeaderPublic.h"

#ifndef PERMUTATIONGENERATOR_H_
#define PERMUTATIONGENERATOR_H_

typedef enum {
	enumDICTIONARY_SEQ,
	enumINCREASE_SYSTEM,
	enumDECREASE_SYSTEM,
	enumADJACENT_EXCHANGE
} PERMULATE_METHOD;

typedef enum {
	enumGENERATE_ALL, enumNEXT_N
} OPERATE_TYPE;

class PermutationGenerator {
public:
	PERMULATE_METHOD m_enPermulateAlgo;//which algorithm you exploit?
	OPERATE_TYPE m_enOperateType;//whick operate you ask for?
	int m_inNextN;
	int m_inElementNumer;
	string m_stPrimitiveStr;

	void fnNextN();
	void fnDictionaryNextN();
	void fnIncSysNextN();
	void fnDecSysNextN();
	void fnAdjExchNextN();

	PermutationGenerator();
	virtual ~PermutationGenerator();

private:
	void fnDictionaryGetIntermediaryNumber(int*);
	void fnDictionaryCalIntermediaryNumber(int,int*,int*);
	void fnTRanIncSys(const int,int*);
	void fnDictionaryGetNextNum(int*);

	void fnIncSysGetIntermediaryNumber(int*);
	void fnIncSysCalIntermediaryNumber(int, int*, int*);
	void fnIncSysGetNextNum(int*);

	void fnDecSysGetIntermediaryNumber(int*);
	void fnDesSysCalIntermediaryNumber(int, int*, int*);
	void fnTRanDecSys(const int, int*);
	void fnDecSysGetNextNum(int*);

	void fnAdjExcGetIntermediaryNumber(int*);
	void fnAdjExcCalIntermediaryNumber(int, int*, int*);
	void fnAdjExcGetNextNum(int*,bool*);
};

#endif /* PERMUTATIONGENERATOR_H_ */
