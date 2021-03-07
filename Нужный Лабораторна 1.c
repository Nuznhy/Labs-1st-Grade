#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <conio.h>

/*      Варіант 15
    x = ln(a + c^2) + (sin(c / b))^2;
   y = e^(-k * c) * (c + (c + a)^1/2) / (c - (|c - a|)^1/2) 
   При а = 9.6; b = 8.2; c = 2; k = 0.7                 */

int main()
{
    float a = 9.6, b = 8.2, k = 0.7, c = 2, x, y;

    x = log(a + (c * c)) + (sin(c / b)) * (sin(c / b));
    y = exp(-k * c) * (c + pow((c + a), 1/2) / (c - pow(abs(c - a), 1/2)));


    printf("а = 9.6    b = 8.2    c = 2    k = 0.7\n");
    printf("x = %f\n", x);
    printf("y = %f\n", y);
}