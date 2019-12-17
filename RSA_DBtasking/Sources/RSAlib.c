#include "../Headers/RSAlib.h"

LInt publicN = { null, 0, NULL };
LInt publicE = { null, 0, NULL };
LInt trapdoor = { null, 0, NULL };

void Init(LInt* bign)
{
	bign->sign = null;
	bign->len = 0;
	if (bign->num)
		free(bign->num);
	bign->num = NULL;
}

void SetPubN(LInt bign, int isheap)
{
	if (publicN.num)
		free(publicN.num);

	publicN.sign = bign.sign;
	publicN.len = bign.len;
	if (isheap)
	{
		publicN.num = (char*)malloc(bign.len + 1);
		strncpy(publicN.num, bign.num, bign.len);
		publicN.num[bign.len] = null;
	}
	else
	{
		publicN.num = bign.num;
	}
}
void SetPubE(LInt bign, int isheap)
{
	if (publicE.num)
		free(publicE.num);

	publicE.sign = bign.sign;
	publicE.len = bign.len;
	if (isheap)
	{
		publicE.num = (char*)malloc(bign.len + 1);
		strncpy(publicE.num, bign.num, bign.len);
		publicE.num[bign.len] = null;
	}
	else
	{
		publicE.num = bign.num;
	}
}
void SetPrvD(LInt bign, int isheap)
{
	if (trapdoor.num)
		free(trapdoor.num);
	
	trapdoor.sign = bign.sign;
	trapdoor.len = bign.len;
	if (isheap)
	{
		trapdoor.num = (char*)malloc(bign.len + 1);
		strncpy(trapdoor.num, bign.num, bign.len);
		trapdoor.num[bign.len] = null;
	}
	else
	{
		trapdoor.num = bign.num;
	}
}

LInt GetPubN()
{
	return publicN;
}
LInt GetPubE()
{
	return publicE;
}
LInt GetPrvD()
{
	return trapdoor;
}

void DestroyAll()
{
	Init(&publicN);
	Init(&publicE);
	Init(&trapdoor);
}

LInt GetOulerN(LInt, LInt, LInt);
LInt GetSubordinationK(LInt);

void WriteKey(LInt prime1, LInt prime2)
{

	GetPublicN(prime1, prime2);
	publicE = SetLArray("65537");
	GetTrapdoorD(prime1, prime2);

	ReverseMalloc(&(prime1.num));
	ReverseMalloc(&(prime2.num));
	ReverseMalloc(&(publicN.num));
	ReverseMalloc(&(publicE.num));
	ReverseMalloc(&(trapdoor.num));
	
	FILE* writing = fopen("RSA_KEY.conf", "w+, ccs=UTF-8");
	fprintf(writing, "[PRIME]\n");
	fprintf(writing, "prime1=%s\nprime2=%s\n", prime1.num, prime2.num);
	fprintf(writing, "[KEYS]\n");
	fprintf(writing, "PUBN=%s\nPUBE=%s\nTRAPD=%s\n", publicN.num, publicE.num, trapdoor.num);

	DestroyAll();
	fclose(writing);
}

void GetPublicN(LInt prime1, LInt prime2)
{
	Init(&publicN);
	LMultiple(&publicN, prime1, prime2);
}

void GetTrapdoorD(LInt prime1, LInt prime2)
{
	if (!(publicE.num))
		return;

	printf("trapdoorstart!\n");
	Init(&trapdoor);
	LInt lone = SetLArray("1");
	LInt OulerN = GetOulerN(prime1, prime2, lone);
	LInt k = SetLArray("1");

	LInt difference = { null, 0, NULL };
	LInt tempdif = { null, 0, NULL };
	LInt temp = { null, 0, NULL };
	//1
	LMultiple(&temp, k, OulerN);
	LPlus(&temp, temp, lone);
	LDivide(&difference, temp, publicE, true);
	if (LIntIsZero(&difference))
	{
		printf("k = 1\n");
		LDivide(&trapdoor, temp, publicE, false);
		free(temp.num);
		free(difference.num);
		free(OulerN.num);
		free(lone.num);
		return;
	}
	//2
	LPlus(&k, k, lone);
	LMultiple(&temp, k, OulerN);
	LPlus(&temp, temp, lone);
	LDivide(&tempdif, temp, publicE, true);
	if (LIntIsZero(&tempdif))
	{
		printf("k = 2\n");
		LDivide(&trapdoor, temp, publicE, false);
		free(temp.num);
		free(difference.num);
		free(tempdif.num);
		free(OulerN.num);
		free(lone.num);
	}
	if (LIntCompare(&difference, &tempdif, true) == 1)
	{
		LPlus(&temp, tempdif, publicE);
		LMinus(&difference, temp, difference);
	}
	else
	{
		LMinus(&difference, tempdif, difference);
	}
	free(temp.num);
	while (true)
	{
		LPlus(&k, k, lone);
		LPlus(&tempdif, tempdif, difference);
		int cmp = LIntCompare(&tempdif, &publicE, true);
		if (cmp == 1)
			LMinus(&tempdif, tempdif, publicE);
		else if (cmp == 0) break;
		else if (LIntIsZero(&tempdif)) break;
	}
	free(difference.num);
	free(tempdif.num);

	LIntPrint(k);
	LMultiple(&trapdoor, k, OulerN);
	LPlus(&trapdoor, trapdoor, lone);
	LDivide(&trapdoor, trapdoor, publicE, false);
	
	free(k.num);
	free(OulerN.num);
	free(lone.num);
	printf("trapdoor end\n");
}

void EncryptText(FILE* writing, char* buf)
{
	//LInt origin = { null, 0, NULL };
	//LInt encrypted = { null, 0, NULL };
	char buffer[10] = { null };

	if (!(publicN.len && publicE.len && trapdoor.len))
		return;

	for (int i = 0; i < (int)strlen(buf); i++)
	{
		sprintf(buffer, "%d", (int)buf[i]);
		printf("integer : \"%s\"\n", buffer);

		//m^e mod N = c
		LInt encrypt = SetLArray(buffer);
		//bInt1^bInt2 mod bInt3
		//LModularSquare(&bInt1, bInt1, bInt2, bInt3);
		LModularSquare(&encrypt, encrypt, publicE, publicN);
		ReverseMalloc(&(encrypt.num));
		if (encrypt.sign == plus)
		{
			printf("%s\n", encrypt.num);
			fprintf(writing, "%s ", encrypt.num);
		}
		else if (encrypt.sign == minus)
		{
			printf("-%s\n", encrypt.num);
			fprintf(writing, "-%s ", encrypt.num);
		}

		free(encrypt.num);
		memset(buffer, null, strlen(buffer));
	}
	fprintf(writing, "\n");
}

void DecryptText(char* buf, char* origin, int seq)
{
	if (!(publicN.len && publicE.len && trapdoor.len))
		return;

	//c^d mod N = m
	LInt decrypt = SetLArray(buf);
	LModularSquare(&decrypt, decrypt, trapdoor, publicN);
	printf("result : %s\n", decrypt.num);
	if (decrypt.sign == minus)
	{
		decrypt.num = (char*)realloc(decrypt.num, decrypt.len + 2);
		decrypt.num[decrypt.len] = minus;
		decrypt.len++;
		decrypt.num[decrypt.len] = null;
	}
	ReverseMalloc(&(decrypt.num));
	int temp = atoi(decrypt.num);
	printf("orig : %d\n", temp);
	origin[seq] = (char)temp;
	free(decrypt.num);
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

LInt GetSubordinationK(LInt OulerN)
{
	LInt k = { null, 0, NULL };
	
	LDivide(&k, OulerN, publicE, true);
	LMinus(&k, publicE, k);
	if (k.num[0] == one && k.num[1] == null)
		LPlus(&k, k, publicE);
	

	return k;
}