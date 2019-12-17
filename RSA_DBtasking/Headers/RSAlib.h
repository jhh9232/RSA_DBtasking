#ifndef RSALIB_H
#define RSALIB_H

#include "HeapCalculator.h"

void SetPubN(LInt, int);
void SetPubE(LInt, int);
void SetPrvD(LInt, int);

LInt GetPubN();
LInt GetPubE();
LInt GetPrvD();

void DestroyAll();


void WriteKey(LInt, LInt);
void GetPublicN(LInt, LInt);
void GetTrapdoorD(LInt, LInt);
void EncryptText(FILE*, char*);
void DecryptText(char*, char*, int);

#endif