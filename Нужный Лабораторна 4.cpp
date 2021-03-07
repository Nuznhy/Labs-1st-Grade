#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>


/*								Варіант 15 
 Дані дійсні числа а1,...,an. Якщо в результаті заміни від`ємних членів 
 послідовності а1,...,an їхніми квадратами члени будуть утворювати 
 неспадну послідовність, то отримати суму членів початкової 
 послідовності; інакше отримати їхню суму.			*/

int main()
{
	float S = 0;
	bool p = true;
	int n;
	printf_s("Enter lengh of your massive:\n");
	scanf_s("%d", &n);
	float mass[1000], mass_neg[1000];

	for (int i = 0; i < n; i++)
	{
		scanf_s("%f", &mass[i]);
	}
	for (int i = 0; i < n; i++)
	{
		if (mass[i] < 0)
		{
			mass_neg[i] = mass[i] * mass[i];
		}
		else
		{
			mass_neg[i] = mass[i];
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (mass_neg[i] > mass_neg[i + 1])  
		{
			p = false;
		}
	}


	if (p == true)
	{
		printf("nespadna\n");
		for (int i = 0; i < n; i++)
		{
			S = S + mass[i];
		}
	}
	else {
		for (int i = 0; i < n; i++)
		{
			S = S + mass_neg[i];
		}
	}

	printf_s("Sum = %.1f\n", S);
	printf_s("mass:\n");

	for (int i = 0; i < n; i++)
	{
		printf_s("%.1f\t", mass[i]);
	}
	
	printf_s("\nmass_neg:\n");
	
	for (int i = 0; i < n; i++)
	{
		printf_s("%.1f\t ", mass_neg[i]);
	}
}