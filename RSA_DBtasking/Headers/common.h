#ifndef COMMON_H
#define COMMON_H

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
#define LARGELEN 500

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

typedef struct LargeInt LInt;

struct LargeInt
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



LInt SLConst(char*);
LInt SLInt(char*);
void SPLInt(LInt**, char*);
char* GLInt(LInt);
size_t GLLen(LInt);
char GLSign(LInt);
void LIntPrint(LInt);
void DLInt(LInt*);
void DPInt(LInt**);

#endif // !COMMON_H