#include "../Headers/CharCalculator.h"
#include <malloc.h>
#include <stdarg.h>

void Plus(char** result, char* num1, char* num2)
{
	char res[205] = { null, };
	int i = 0, carry = 0;
	while(true)
	{
		if (*num1 == null)
		{
			if (*num2 == null)
			{
				if (carry > 0)
					res[i] = (char)(carry + zero);
				break;
			}
			else
			{
				res[i] = (char)((*num2 - 48) + carry);
				num2++;
			}
		}
		else if (*num2 == null)
		{
			res[i] = (char)((*num1 - zero) + carry);
			num1++;
		}
		else
		{
			res[i] = (char)((*num1 - zero) + (*num2 - zero) + carry);
			num1++;
			num2++;
		}

		if (res[i] > 9)
		{
			res[i] = (char)(res[i] - 10);
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		res[i] = (char)(res[i] + zero);
		i++;
	}
	if (*result != NULL)
		free(*result);
	*result = (char*)malloc(strlen(res)+1);
	strncpy(*result, res, strlen(res)+1);
	(*result)[strlen(res)] = null;
}

void Minus(char** result, char* num1, char* num2)
{
	char res[205] = { null, };
	int i = 0, carry = 0;
	while (true)
	{
		if (*num1 == null)
		{
			if (*num2 == null)
			{
				//음수일 경우 0을 리턴
				if (carry == 1)
				{
					res[0] = minus;
					res[1] = null;
					break;
				}
				break;
			}
			else
			{
				res[i] = (char)(0 - (*num2 - 48) - carry);
				num2++;
			}
		}
		else if (*num2 == null)
		{
			res[i] = (char)((*num1 - zero) - carry);
			num1++;
		}
		else
		{
			res[i] = (char)((*num1 - zero) - (*num2 - zero) - carry);
			num1++;
			num2++;
		}

		if (res[i] < 0)
		{
			res[i] = (char)(res[i] + 10);
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		res[i] = (char)(res[i] + zero);
		i++;
	}
	while (strlen(res) > 0 && res[strlen(res) - 1] == zero)
		res[strlen(res) - 1] = null;
	if (res[0] == null)
		res[0] = zero;

	if (*result != NULL)
		free(*result);
	*result = (char*)malloc(strlen(res) + 1);
	strncpy(*result, res, strlen(res) + 1);
	(*result)[strlen(res)] = null;
}

void Multiple(char** result, char* num1, char* num2)
{
	//2자리*2자리 = 4자리 (99*99 = 9801), 3자리*3자리 = 6자리 (999*999 = 998001)
	char* res = (char*)malloc(2);
	res[0] = zero;
	res[1] = null;

	if (num2[0] == zero && num2[1] == null)
		return;

	int i = 0, cipher = 0;
	while(*num2 != null)
	{ 
		char save[205] = { null, };
		int carry = 0, num1Size = (int)strlen(num1);
		for (i = 0; i < cipher; i++)
			save[i] = zero;
		for (i = cipher; i < num1Size + cipher; i++)
		{
			save[i] = (char)((num1[i - cipher] - zero) * (*num2 - zero) + carry);
			if (save[i] > 9)
			{
				carry = (int)(save[i] / 10);
				save[i] = (char)(save[i] % 10 + zero);
			}
			else
			{
				carry = 0;
				save[i] = (char)(save[i] + zero);
			}
		}
		if (carry > 0)
			save[(int)strlen(num1)+cipher] = (char)(carry + zero);
		
		Plus(&res, save, res);
		cipher++;
		num2++;
	}

	if (*result != NULL)
	{
		free(*result);
	}
	*result = (char*)malloc(strlen(res) + 1);
	strncpy(*result, res, strlen(res) + 1);
	(*result)[strlen(res)] = null;
	free(res);
}

void Divide(char** result, char* num1, char* num2, int isMod)
{
	char res[205] = { null, };

	int i;
	char quotient[205] = { null, };     //역순저장이 안 될 예정
	if ((num2[0] == zero && num2[1] == null))
	{
		if (*result)
			free(*result);
		*result = (char*)malloc(2);
		(*result)[0] = divide;
		(*result)[1] = null;
		return;
	}
	else if (strlen(num1) < strlen(num2))
	{
		if (isMod)
		{
			char* memory = (char*)malloc(strlen(num1) + 1);
			strncpy(memory, num1, strlen(num1));
			memory[strlen(num1)] = null;
			if (*result)
				free(*result);
			*result = (char*)malloc(strlen(memory) + 1);
			strncpy(*result, memory, strlen(memory));
			(*result)[strlen(memory)] = null;
			free(memory);
			return;
		}
		else
		{
			if (*result)
				free(*result);
			*result = (char*)malloc(2);
			(*result)[0] = zero;
			(*result)[1] = null;
			return;
		}
	}

	for (i = (int)strlen(num1) - 1; i >= 0; i--)
	{
		size_t size = strlen(res);
		res[size] = num1[i];
		if (strlen(res) >= strlen(num2))
		{
			char* tmpRes = (char*)malloc(strlen(res) + 1);
			strncpy(tmpRes, res, strlen(res) + 1);
			tmpRes[strlen(res)] = null;
			ReverseMalloc(&tmpRes);

			int minusCnt = -1;
			while (tmpRes[0] != minus)
			{
				strncpy(res, tmpRes, strlen(tmpRes));
				memset(res+strlen(tmpRes), null, 205-strlen(tmpRes));
				Minus(&tmpRes, tmpRes, num2);
				minusCnt++;
			}

			while (strlen(res) > 0 && res[strlen(res) - 1] == zero)
				res[strlen(res) - 1] = null;

			quotient[strlen(quotient)] = (char)(minusCnt + zero);
			Reverse(res);
			free(tmpRes);
		}
		else
		{
			quotient[strlen(quotient)] = zero;
		}
	}
	if (*result != NULL)
		free(*result);

	if (isMod == true)
	{
		Reverse(res);
		while (strlen(res) > 0 && res[strlen(res) - 1] == zero)
			res[strlen(res) - 1] = null;
		if (res[0] == null)
			res[0] = zero;
		*result = (char*)malloc(strlen(res) + 1);
		strncpy(*result, res, strlen(res) + 1);
		(*result)[strlen(res)] = null;
		//printf("mod : %s\n", *result);
	}
	else
	{
		Reverse(quotient);
		while (strlen(quotient) > 0 && quotient[strlen(quotient) - 1] == zero)
			quotient[strlen(quotient) - 1] = null;
		if (quotient[0] == null)
			quotient[0] = zero;
		*result = (char*)malloc(strlen(quotient) + 1);
		strncpy(*result, quotient, strlen(quotient) + 1);
		(*result)[strlen(quotient)] = null;
		//printf("quo : %s\n", *result);
	}
}

void ChangeBinary(char** bin, char* dec)
{
	clock_t start = clock();
	int i = 0;
	char res[350] = { null, };
	char* cal = (char*)calloc(strlen(dec) + 1, sizeof(char));
	strncpy(cal, dec, strlen(dec));
	
	while (cal[0] != zero || cal[1] != null)
	{
		if ((cal[0] - zero) % 2 == 0)
			res[i] = zero;
		else
			res[i] = one;
		Divide(&cal, cal, "2", false);
		//printf("cal : %s\n", cal);
		i++;
	}
	free(cal);
	if (*bin != NULL)
		free(*bin);
	
	*bin = (char*)calloc(strlen(res)+1, sizeof(char));
	strncpy(*bin, res, strlen(res));

	//printf("origin : %s\nreverse : ", *bin);
	printf("\n");
	//printf("strlen(bin) : %ld\n", strlen(*bin));
	printf("Change Bin Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}

void Operate(char** result, char* num1, char* num2, char oper)
{
	clock_t start = clock();
	switch (oper)
	{
	case plus:
		printf("plus\n");
		Plus(result, num1, num2);
		break;
	case minus:
		printf("minus\n");
		Minus(result, num1, num2);
		if (*result[0] == minus)
			*result[0] = zero;
		break;
	case multiple:
		printf("multiple\n");
		Multiple(result, num1, num2);
		printf("multiple result : %s\n", *result);
		break;
	case divide:
		printf("divide\n");
		Divide(result, num1, num2, false);
		if (*result[0] == divide)
			*result[0] = zero;
		break;
	case mod:
		printf("Mod\n");
		Divide(result, num1, num2, true);
		if (*result[0] == divide)
			*result[0] = zero;
		break;
	default:
		return;
	}
	printf("Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}
void Modular(char** result, char* num1, char* num2, char* n, char oper)
{
	clock_t start = clock();
	switch (oper)
	{
	case plus:
		//(a mod(n) + b mod(n)) mod(n) = (a + b) mod(n)
		printf("Modular plus\n");
		Plus(result, num1, num2);
		Divide(result, *result, n, true);
		break;
	case minus:
		//(a mod(n) - b mod(n)) mod(n) = (a - b) mod(n)
		printf("Modular minus\n");
		Minus(result, num1, num2);
		Divide(result, *result, n, true);
		break;
	case multiple:
		//(a mod(n) * b mod(n)) mod(n) = (a * b) mod(n)
		printf("Modular multiple\n");
		break;
	case square:
		//100 ^ 50 = 정확히 100자리 1e+100
		//((a mod(n))^ b) mod(n) = a ^ b mod(n)
		//2^90 mod 13 = (2^50 * 2^40) mod 13
		printf("Modular square\n");
		break;
	default:
		return;
	}
	printf("Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}

void ModularSquare(char** result, char* P, char* a)
{
	//printf("P : %s\n", P);
	clock_t start = clock();
	char* sqr_1 = NULL, *bin = NULL;
	char* sqrmod = (char*)calloc(strlen(a) + 1, sizeof(char));
	strncpy(sqrmod, a, strlen(a));
	char* resmod = NULL;

	Minus(&sqr_1, P, "1");
	//printf("Minus 1 : %s\n", sqr_1);
	ChangeBinary(&bin, sqr_1);
	//printf("bin : %s\n", bin);
	//mod 구하기
	Divide(&sqrmod, sqrmod, P, true);
	if (bin[0] == one)
	{
		resmod = (char*)calloc(strlen(sqrmod) + 1, sizeof(char));
		strncpy(resmod, sqrmod, strlen(sqrmod));
	}
	else
	{
		resmod = (char*)calloc(2, sizeof(char));
		resmod[0] = one;
	}
	//printf("first sqrmod : %s\n", sqrmod);
	//printf("first resmod : %s\n", resmod);
	for (int i = 1; i < strlen(bin); i++)
	{
		Multiple(&sqrmod, sqrmod, sqrmod);
		Divide(&sqrmod, sqrmod, P, true);
		//printf("[%d] sqrmod : %s\n",i , sqrmod);

		if (bin[i] == one)
		{
			Multiple(&resmod, resmod, sqrmod);
			//printf("mul res : %s\n", resmod);
			Divide(&resmod, resmod, P, true);
			//printf("resmod : %s\n", resmod);
		}
	}
	printf("binmod res : %s\n", resmod);
	printf("\n");

	*result = (char*)malloc(strlen(resmod) + 1);
	strncpy(*result, resmod, strlen(resmod) + 1);
	(*result)[strlen(resmod)] = null;

	free(sqr_1);
	free(bin);
	free(sqrmod);
	free(resmod);
	printf("SQUARE MODULAR Time : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}
