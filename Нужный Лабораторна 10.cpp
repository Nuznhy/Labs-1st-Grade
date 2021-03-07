#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <cstdio>
#include <conio.h>
#include <ctype.h>
#include <string.h>

/* 12 Варіант
Обчислити і запам'ятати кількість 
від’ємних елементів кожного стовпця для матриць А (5,5), В (4,5)*/


void allocateMatrix(int*** A, int row, int column)
{
	int** mem = *A;
	*A = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++)
	{
		(*A)[i] = (int*)malloc(column * sizeof(int));	
	}
	
}

void allocateCounters(int** counter, int column) 
{
	 *counter = (int*)malloc(sizeof(int) * column);
}

void matrixCreation(int** matrix, int row, int column)		
{
	srand(time(0));
	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			(matrix)[i][j] = rand() % 100 - 49;
		}
	}	
}

void Comparison(int*** matrix, int** counters, int row, int column)
{
	int** A = *matrix;
	int* counter = *counters;
	
	for (int i = 0; i < column; i++)
	{
		counter[i] = 0;
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (A[i][j] < 0)
			{
				counter[j]++;
			}
		}
	}
	*matrix = A;
	*counters = counter;
}

void printing(int*** matrix, int** counters, int row, int column)
{
	int* counter = *counters;
	int** A = *matrix;
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < column; i++)
		{
			printf("%d\t", A[j][i]);
		}
		printf("\n");
	}
	printf("\n");
	for (int j = 0; j < column; j++)
	{
		
		printf("%d\t", counter[j]);
	}
	printf("\t - result");
}

int main()
{
	int  row, column;
	int* counter;
	int** matrix;
	
	printf("Enter number of columns and rows\n");
	scanf_s("%d %d", &row, &column);
	printf("\n");
	
	allocateMatrix(&matrix, row, column);
	allocateCounters(&counter, column);
	matrixCreation(matrix, row, column);
	Comparison(&matrix, &counter, row, column);
	printing(&matrix, &counter, row, column);
}