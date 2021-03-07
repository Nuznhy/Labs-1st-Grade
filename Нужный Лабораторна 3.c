#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <conio.h>

/*  
        Варіант 15
    S = 1/((1+x)^3)
    1 - ((2*3)/2)*x + ((3/4)/2)*x^2...    
        
        */
        

int main()
{
    double eps, a = 1, x = 0, S = 1, ST = 0;
    int n = 2;
    printf("Enter eps\n");
    scanf("%lf", &eps);
    printf("Enter x\t|x| < 1\n");
    scanf("%lf", &x);
    

    ST = 1 / ((1 + x) * (1 + x) * (1 + x));
    S = 1;
    a = 1;
    while (fabs(S - ST) > eps)
    {
        a = -(a / (n - 1) * (n + 1) * x);
        S += a;
        n++;
    } 
    printf("ST=%lf S=%lf eps=%lf\n", ST, S, eps);
}
