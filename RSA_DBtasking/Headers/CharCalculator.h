#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "./common.h"

int gitPlus(LInt*, LInt, LInt);
int gitMinus(LInt*, LInt, LInt);
int gitMultiple(LInt*, LInt, LInt);
int gitDivide(LInt*, LInt, LInt, int);
int gitChangeBinary(LInt*, LInt);
int gitModularSquare(LInt*, LInt, LInt);

void Plus(char**, char*, char*);
void Minus(char**, char*, char*);
void Multiple(char**, char*, char*);
void Divide(char**, char*, char*, int);

void ChangeBinary(char**, char*);
void Operate(char**, char*, char *, char);
void Modular(char**, char*, char*, char*, char);
void ModularSquare(char**, char*, char*);


#endif