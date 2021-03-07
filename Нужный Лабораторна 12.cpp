#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

/* Варіант 12
Перевірити, чи є заданий рядок зашифрований за алгоритмом, що наведено 
у варіанті 11. Якщо так - видати розшифрований рядок, якщо ні - 
вивести повідомлення про помилку і вивести перше помилкове слово.

Можливі символи - прописні українські букви; символ-роздільник '_'. */

using namespace std;

int BinomialCoefficient(int n, int k)
{
	if (k == 0 || k == n)
	{
		return 1;
	}
	if (n == 0)
	{
		return 0;
	}
	return (BinomialCoefficient(n - 1, k - 1) + BinomialCoefficient(n - 1, k));
}

int main()
{
	int MaxLength;
	int* counter;
	char *str, *buff;
	bool flag = false;
	cout << "Enter Max lenght of string ";
	cin >> MaxLength;
	
	buff = new char[MaxLength];

	cout << "Enter your text\n";
	cin >> buff;
	
	str = new char[strlen(buff)+1];
	memcpy(str, buff, sizeof(char) * (strlen(buff)+1));
	delete[] buff;
	buff = nullptr;

	cout << str << endl;
	char* str_copy = new char[strlen(str)];
	memcpy(str_copy, str, sizeof(char) * (strlen(str) + 1));
	
	char* stringPart = strtok(str, "_");
	while (stringPart != NULL)
	{
		int counter = 1;
		int coeff = 0;
		int n = strlen(stringPart), degree = 0;

		int i = 0, j = 0;
		do
		{
			i++;
			counter = 1;
			
			while (stringPart[i-1] == stringPart[i])
			{
				counter++;
				i++;
			}
			
			if (n % 2 == 0)
			{
				do
				{
					degree++;
					n = n / 2;
				} while (n % 2 == 0);
			}

			int f = j;
			coeff = BinomialCoefficient(degree, f);
			
			if (counter != coeff)
			{
				cout << "not cipher " << stringPart;
				flag = true;
				goto break1;
			}
			else if (coeff == 0)
			{
				flag = true;
				goto break1;
			}
			j++;
			cout << counter << endl;
		} while (stringPart[i] != NULL);
		
		cout << stringPart << endl;
		stringPart = strtok(NULL, "_");
	}
	
	delete[] str;
	str = nullptr;
	
	if (flag == false)
	{
		char* result;
		result = (char*)malloc(sizeof(char) * strlen(str_copy));	// new char[strlen(str_copy)];
		int i = 0, j = 0;
		do
		{
			i++;
			while (str_copy[i-1] == str_copy[i])
			{
				i++;
			}
			result[j] = str_copy[i-1];
			j++;
		} while (str_copy[i] != NULL);
		int count = 0;
		result[j] = '\0';
		cout << result;
		
	}
	
	while(flag)
	{	
		delete[] str_copy;
		str_copy = nullptr;
		break1:
		break;
	}
}

// IAAASSSA_IS_THHE_BEEESSST  IASA_IS_THE_BEST\0  --- 17
// I_LOOOVVVE_MAAATTTH
// WEEELLL_DOOONNNE