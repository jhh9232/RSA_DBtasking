#include "../Headers/RSAlib.h"

LInt GetOulerN(LInt, LInt, LInt);
LInt GetSubordinationK(LInt, LInt);

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