#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0
#define null '\0'

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

int IsNumber(char*);
void Eliminate(char*);
void Reverse(char*);
void ReverseMalloc(char**);
void ReversePrint(const char *, char*);

#endif // !COMMON_H