#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <conio.h>

/*              Варіант 15
    y = { ax^2 + bx;                    x < 1.2
        { a/x + (x^2 + 1)^1/2           x = 1.2  
        { (a + bx) / ((x^2 + 1)^1/2)    x > 1.2
        
        a = 2.8, b = -0.3, x є [1, 2], delta(x) = 0.1
        */
        

int main()
{
    float a = 2.8, b = -0.3, y, x = 1;
    printf("a = 2.8, b = -0.3, x є[1, 2], delta(x) = 0.1\n\n");
    while (x <= 2.1)
    {
        if (x < 1.2)
        {
            y = a * x * x + b * x;
        }
        if (x == 1.2)
        {
            y = a / x + pow((x * x) + 1, 1 / 2);
        }
        if (x > 1.2)
        {
            y = (a + b * x) / (pow((x * x) + 1, 1 / 2));
        }
        printf("y = %f\n", y);
        printf("x = %f\n", x);
        x += 0.1;
        printf("\n");
    }
    
}