#include<iostream>

/* Варінт 15
	Задані матриця А(N,N) і число K (1<=К<=N). 
	Рядок з максимальним по модулю елементом в К-ому стовпці 
	переставити з К-й рядком.*/

int main() 
{
	int N, number =0;
	scanf_s("%d", &N);
	printf_s("\n");
	while (N > 0)
	{
		int last_number = N % 10;
		//printf_s("%d", last_number);
		N /= 10;
		number *= 10;
		number += last_number;
	}
	printf_s("\n");
	printf_s("%d", number);
}