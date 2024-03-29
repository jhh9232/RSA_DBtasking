#ifndef COMMON_H
#define COMMON_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#define true 1
#define false 0
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define ERROR 0
#define null '\0'
//RSA 4096
#define LARGELEN 4100
#define PRIMELEN 258

#define plus (char)43       //'+'
#define minus (char) 45     //'-'
#define multiple (char)42   //'*'
#define divide (char)47     //'/'
#define mod (char)46        //'.'
#define square (char)94     //'^'

#define zero (char)48
#define one (char)49
#define two (char)50
#define three (char)51
#define four (char)52
#define five (char)53
#define six (char)54
#define seven (char)55
#define eight (char)56
#define nine (char)57

typedef struct LargeHeapInt LInt;

struct LargeHeapInt
{
	char sign;
	size_t len;
	char *num;
};

int Wait(int);
int IsNumber(char*);
void Eliminate(char*);
void Reverse(char*);
void ReverseMalloc(char**);
void ReversePrint(const char *, char*);
void ReverseMinusPrint(const char*, char*);


void SetLInit(LInt*);
LInt SetLArray(char*);
LInt SetLInt(char*);
void LIntPrint(LInt);

void LIntSetMalloc(char**, size_t);
void LIntSetCalloc(char**, size_t);
void LIntCopy(LInt*, LInt*);
void LIntCopySize(LInt*, LInt*, size_t);

#endif // !COMMON_H