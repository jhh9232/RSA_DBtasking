#ifndef HEAP_CALCULATOR_H
#define HEAP_CALCULATOR_H

#include "./common.h"

int LPlus(LInt*, LInt, LInt);
int LMinus(LInt*, LInt, LInt);
int LMultiple(LInt*, LInt, LInt);
int LDivide(LInt*, LInt, LInt, int);
int LChangeBinary(LInt*, LInt);
//Heap을 쓰면 100자리 소수 판별하는 데 0.1 ~ 0.2초
int LParsePrime(LInt*, LInt, LInt);
int LModularSquare(LInt*, LInt, LInt, LInt);

void OperTmp(char*, char*, char*);

#endif