#ifndef RSALIB_H
#define RSALIB_H

#include "HeapCalculator.h"

void WriteKey(LInt, LInt);
LInt GetPublicN(LInt, LInt);
LInt GetTrapdoorD(LInt, LInt, LInt);
void EncryptText(LInt, LInt, FILE*, char*);

#endif