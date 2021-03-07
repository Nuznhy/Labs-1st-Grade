#include<iostream>
#include<time.h>

/* Варіант
	Дана цілочисельна квадратна матриця порядку n. 
	Знайти номери рядків всі елементи яких є парними.
*/

int main()
{
	const int n = 3;
	int j = 0, i = 0;
	int matrix[n][n], string[n];
	srand(time(NULL)); //Every number will be unique  (comment by Nuzhnyi)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = 1 + rand() % 100;
		}
	}
	printf_s("\n");
	for (int i = 0; i < n; i++)						//printing matrix
	{
		for (int j = 0; j < n; j++)
		{
			printf_s("\t%d\t", matrix[i][j]);
		}
		printf_s("\n");
	}
	
	printf_s("\n");

	bool flag;
	
	for (int i = 0; i < n; i++)						//printing matrix
	{
		flag = true;
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] % 2)
			{
				flag = false;
			}
		}
		if (flag) 
		{
			printf_s("%d\n", i+1);
		}
	}
}