#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* 12 Варіант
Задано натуральне число n, символи S1, .., Sn. 
Виключити з цієї послідовності усі групи букв виду "abсd". */

void allocateChar(char** stringMem, int n)
{
	*stringMem = (char*)malloc(sizeof(char)*n);
}

void createChar(char** string, int n)
{
	srand(time(0));
	
	for (int i = 0; i < n; i++)
	{
		(*string)[i] = rand() % (122 + 1 - 97) + 97;
	}
	
	for (int i = 0; i < n; i++)
	{
		printf("%c", (*string)[i]);
	}
	printf("\n");
}

void function(char* string, char* userString, int n)
{
	char* temploop;
	temploop = strstr(string, userString); 
	if (temploop != NULL)
	{
		for (int i = 0; i < n; i++)
		{
			temploop[i] = temploop[i + strlen(userString)];		
		}
		
		for (int i = 0; i <= strlen(userString); i++)
		{
			string[n - i] = NULL;
		}
		printf("found\n");
		
		for (int i = 0; i < n - strlen(userString); i++)
		{
			printf("%c", string[i]);
		}
		printf("\n");
	}	
	else 
	{
		printf("Not found");
		printf("\n");
	}
	
}

int main()
{
	printf("\n");
	printf("Enter the length of the string:\n");
	
	int n;
	char* strRandom;
	char strEntered[100];
	//char strRandom[10] = "fgfdpn";
	
	scanf_s("%d\n", &n);

	allocateChar(&strRandom, n);
	createChar(&strRandom, n);
	gets_s(strEntered);
	function(strRandom, strEntered, n);
}