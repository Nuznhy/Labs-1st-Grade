#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>

/*		Варіант 15
	Варінт Задані матриця А(N,N) і число K (1<=К<=N). 
	Рядок з максимальним по модулю елементом в К-ому 
	стовпці переставити з К-й рядком.*/

int main() 
{	
	int N, K, max = 0, index_max = 0;
	int j = 0, i = 0;;
	int A[100][100];
	printf_s("Enter n - size of matrix (n x n matrix): ");
	scanf_s("%d", &N);
	printf_s("Enter K column: ");
	scanf_s("%d", &K);
	for (i = 0; i < N; i++)										//entering matrix
	{
		for (j = 0; j < N; j++) 
		{
			printf_s("Enter value for A[%d][%d]: ", i, j);
			scanf_s("%d", &A[i][j]);
		}
	}
	
	printf_s("Start matrix: \n");
	
	for (int i = 0; i < N; i++)						//printing matrix
	{
		for (int j = 0; j < N; j++)
		{
			printf_s("%d\t", A[i][j]);
			if (j % 2 == 0 && j != 0)
			{
				printf_s("\n");
			}
		}
	}
	
	for (i = 0; i < N; i++)
	{
		if (fabs(A[i][K]) > fabs(max))
		{
			max = A[i][K];
			index_max = i;
		}
	}
	
	for(i = 0; i < N; i++)
	{
		int temp = A[index_max][i];
		A[index_max][i] = A[K][i];
		A[K][i] = temp;
	}
	
	printf_s("max = %d \n", max);
	printf_s("Exit matrix: \n");
	
	for (int i = 0; i < N; i++)						//printing matrix
	{
		for (int j = 0; j < N; j++)
		{
			printf_s("%d ", A[i][j]);
			if (j % 2 == 0 && j != 0)
			{
				printf_s("\n");
			}
		}
	}
}
