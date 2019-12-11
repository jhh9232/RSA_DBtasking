#ifndef CREATE_PRIME_H
#define CREATE_PRIME_H

#include "./HeapCalculator.h"

void GeneratorPrime(LInt*, int, char);
void ThreadGeneratorPrime(LInt*, int, char, unsigned int*);
int NextGenerator(LInt*);
int check3mul(LInt);
int AddGenerator(LInt*, char*);

#endif