#include "./Headers/CharCalculator.h"
#include "./Headers/CreatePrime.h"

int main()
{
	/*char* make = NULL;
	GeneratorPrime(&make);
	return 0;*/
	char buf[103] = { null, };
	char num1[102] = { null, };
	char num2[102] = { null, };
	printf("input number1 : ");
	fgets(buf, 102, stdin);
	
	buf[strlen(buf) - 1] = null;
	Eliminate(buf);
	Reverse(buf);
	strncpy(num1, buf, 100);
	memset(buf, null, strlen(buf)+1);
	printf("strlen(num1) : %ld\n", strlen(num1));

	printf("input number2 : ");
	fgets(buf, 102, stdin);

	buf[strlen(buf) - 1] = null;
	Eliminate(buf);
	Reverse(buf);
	strncpy(num2, buf, 100);
	memset(buf, null, strlen(buf)+1);

	printf("|%s|\n", num1);
	printf("|%s|\n", num2);

	printf("input operator : ");
	fgets(buf, 102, stdin);
	buf[strlen(buf) - 1] = null;

	char* result = null;
	if (!strncmp(buf, "+", 1))
		Operate(&result, num1, num2, plus);
	else if (!strncmp(buf, "-", 1))
		Operate(&result, num1, num2, minus);
	else if (!strncmp(buf, "*", 1))
		Operate(&result, num1, num2, multiple);
	else if (!strncmp(buf, "/", 1))
		Operate(&result, num1, num2, divide);
	else if (!strncmp(buf, ".", 1))
		Operate(&result, num1, num2, mod);
	else if (!strncmp(buf, "b", 1))
	{
		clock_t start = clock();
		char* gen = NULL;
		long long int rancnt = 0;
		while (true)
		{
			GeneratorPrime(&gen);
			printf("gen : %s\n", gen);
			ReversePrint("rev gen", gen);
			printf("strlen(gen) : %ld\n", strlen(gen));
			/*char scan[10] = { null, };
			fgets(scan, sizeof(scan), stdin);*/
			ModularSquare(&result, gen, num2);
			//ModularSquare(&result, num1, num2);
			printf("strlen(result) : %ld\n", strlen(result));
			if (!strncmp(result, "1", strlen(result)))
			{
				//printf("gen(rev) : %s\n", gen);
				ReversePrint("gen", gen);
				printf("시도 횟수 : %ld\n", rancnt);
				printf("걸린 시간 : %.5lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);
				free(gen);
				break;
			}
			else
			{
				printf("재시도...\n");
				free(result);
				result = NULL;
				rancnt++;
			}
			free(gen);
			gen = NULL;
		}
		//GeneratorPrime(&gen);
		//printf("gen : %s\n", gen);
		//ReversePrint("rev gen", gen);
		//printf("strlen(gen) : %ld\n", strlen(gen));
		//char scan[10] = { null, };
		//fgets(scan, sizeof(scan), stdin);
		//ModularSquare(&result, gen, num2);
		////ModularSquare(&result, num1, num2);
		//printf("strlen(result) : %ld\n", strlen(result));
		//free(gen);
	}
	else if (!strncmp(buf, "v", 1))
	{
		ModularSquare(&result, num1, num2);
		printf("strlen(result) : %ld\n", strlen(result));
	}
	else
		return 0;


	memset(buf, null, sizeof(buf));

	ReversePrint("main result", result);
	free(result);
	return 0;

}
/*
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./
*/