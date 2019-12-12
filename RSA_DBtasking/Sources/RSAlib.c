#include "../Headers/RSAlib.h"

LInt GetOulerN(LInt, LInt, LInt);
LInt GetSubordinationK(LInt, LInt);

void WriteKey(LInt prime1, LInt prime2)
{

	LInt N = GetPublicN(prime1, prime2);
	LInt e = SetLArray("3");
	LInt d = GetTrapdoorD(prime1, prime2, e);
	ReverseMalloc(&(prime1.num));
	ReverseMalloc(&(prime2.num));
	ReverseMalloc(&(N.num));
	ReverseMalloc(&(e.num));
	ReverseMalloc(&(d.num));
	
	FILE* writing = fopen("RSA_KEY.conf", "w+, ccs=UTF-8");
	fprintf(writing, "[PRIME]\n");
	fprintf(writing, "prime1=%s\nprime2=%s\n", prime1.num, prime2.num);
	fprintf(writing, "[KEYS]\n");
	fprintf(writing, "PUBN=%s\nPUBE=%s\nTRAPD=%s\n", N.num, e.num, d.num);

	free(N.num);
	free(e.num);
	free(d.num);
	fclose(writing);
}

LInt GetPublicN(LInt prime1, LInt prime2)
{
	LInt N = { null, 0, NULL };
	LMultiple(&N, prime1, prime2);
	return N;
}

LInt GetTrapdoorD(LInt prime1, LInt prime2, LInt e)
{
	LInt lone = SetLArray("1");
	LInt OulerN = GetOulerN(prime1, prime2, lone);
	LInt trapdoor = GetSubordinationK(OulerN, e);

	LMultiple(&trapdoor, trapdoor, OulerN);
	LPlus(&trapdoor, trapdoor, lone);
	LDivide(&trapdoor, trapdoor, e, false);

	free(OulerN.num);
	free(lone.num);
	return trapdoor;
}

void EncryptText(LInt N, LInt e, FILE* writing, char* origin)
{
	//LInt encrypted[4098] = { 0, };



	strncpy(origin, "byebye sir!", 19);
	origin[strlen(origin)] = null;
	for (int i = 0; i < (int)strlen(origin); i++)
		printf("%d ", origin[i]);
	printf("\n");
}


LInt GetOulerN(LInt prime1, LInt prime2, LInt lone)
{
	LInt OulerN = { null, 0, NULL };
	LInt p1 = { null, 0, NULL };
	LInt p2 = { null, 0, NULL };

	LMinus(&p1, prime1, lone);
	LMinus(&p2, prime2, lone);
	LMultiple(&OulerN, p1, p2);

	free(p1.num);
	free(p2.num);
	return OulerN;
}

LInt GetSubordinationK(LInt OulerN, LInt e)
{
	LInt k = { null, 0, NULL };
	
	LDivide(&k, OulerN, e, true);
	LMinus(&k, e, k);

	return k;
}