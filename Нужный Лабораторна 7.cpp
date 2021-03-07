#include<iostream>
#include<time.h>

/* Варіант 15
	Дано натуральне число n, дійсні числа а1,...,an . 
	Отримати всі натуральні i
	(2 < = i < = n-1), для яких ai-1<ai<ai+1.
*/

int main()
{
	const int n = 10;
	float a[n];
	srand(time(NULL)); //Every number will be unique  (comment by Nuzhnyi)
	for (int i = 0; i < n; i++)
	{
		a[i] = 1 + rand() % 100;
		printf_s("%.1f\t", a[i]);
	}
	printf_s("\n");
	

	for (int j = 1; j < n-1; j++)
	{
		if (a[j - 1] < a[j] && a[j] < a[j + 1])
		{
			printf_s("%d ", j);
			if (j == n-1) 
			{
				printf_s("\n");
			}	
		}
	}
}		