#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <string>
#include <conio.h>
FILE *textIn, *textOut;
int randLenS, randLenNum;

/* 12 Варіант Створити текстовий файл, 
який містить додатні, від’ємні, нульові числа та довільні символи. 
Визначити кількість додатних, від’ємних, нульових чисел та слів у 
кожному рядку файлу. Записати отримані значення з 
відповідними коментарями в інший текстовий файл. */


                /* Creates random numbers */
void numbers_generator(int** num)
{
    srand(time(0));
    randLenNum = rand() % 25;
    *num = (int*)malloc(sizeof(int) * randLenNum);
    for (int i = 0; i < randLenNum; i++)
    {
        (*num)[i] = (rand() % 101 - 50);
    }
}

                /* Creates random string */
void words_generator(char** randomstr)
{
    const char alphabet[28] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int sizeA = 28;

    srand(time(0));
    randLenS = rand() % 50;
    *randomstr = (char*)malloc(sizeof(char) * randLenS + 2);
    for (int i = 0; i < randLenS; i++)
    {
        (*randomstr)[i] = alphabet[rand() % sizeA - 1];
    }
}

                /* Create two files - user and result */
void files_creation()
{
    textIn = fopen("user.txt", "a");       //а - append
    if (textIn == NULL)                     //if file does not exist, create it
    {
        textIn = fopen("user.txt", "w+");   //w == writes a file for write/update
    }
    
    textOut = fopen("result.txt", "a");
    if (textOut == NULL)
    {
        textOut = fopen("result.txt", "w+");
    } 
}

int main()
{
    files_creation();
    char* userstr, *buff, *randomstr, * userNum;
    int key, keyLoop;
    int* num;
    bool flag = true;

    while (flag)
    {
        printf("\n");
        printf("               MENU\n");
        printf("Choose type of data you want to write down:\n");
        printf("1. Random Number\n");
        printf("2. Random String\n");
        printf("3. Type Number\n");
        printf("4. Type String\n");
        printf("Or:\n");
        printf("5. Calculate a<0, a>0, a=0 and number of words in strings\n");
        printf("6. Exit\n");
        printf("(Type ony one number and press Enter)\n");
        printf("\n");
        scanf("%d", &key);
        switch (key)
        {
            case 1: 
            {   
                do
                {
                    numbers_generator(&num);
                    for (int i = 0; i < randLenNum; i++)
                    {
                        fprintf(textIn, "%d ", num[i]);
                    }
                    fprintf(textIn, "\n");
                    printf("Want to continue? [1 = Yes / Any other = Back to MENU]\n");
                    scanf("%d", &keyLoop);
                } while (keyLoop == 1);
                break; 
            };
            case 2: 
            {
                do
                {
                    words_generator(&randomstr);
                    for (int i = 0; i < randLenS + 2; i++)
                    {
                        fprintf(textIn, "%c", randomstr[i]);
                    }
                    fprintf(textIn, "\n");
                    printf("Want to continue? [1 = Yes / Any other = Back to MENU]\n");
                    scanf("%d", &keyLoop);
                } while (keyLoop == 1);
                break; 
            };
            case 3: 
            {
                do
                {
                    userNum = (char*)malloc(sizeof(char) * 30);
                    fflush(stdin);
                    getchar();
                    fgets(userNum, 499, stdin);
                    fputs(userNum, textIn);
                    printf("Want to continue? [1 = Yes / Any other = Back to MENU]\n");
                    scanf("%d", &keyLoop);
                } while (keyLoop == 1);
                break;
            };
            case 4: 
            {
                do
                {          
                    userstr = (char*)malloc(sizeof(char)*500);
                    fflush(stdin);
                    getchar();
                    fgets(userstr, 499, stdin);
                    int size = sizeof(userstr) / sizeof(char);
                    fputs(userstr, textIn);
                    printf("Want to continue? [1 = Yes / Any other = Back to MENU]\n");
                    scanf("%d", &keyLoop);
                } while (keyLoop == 1);
                break; 
            };
            case 5: 
            {
                do
                {
                    fclose(textIn);
                    textIn = fopen("user.txt", "rb");           //Этот кусок, чтобы посчитать количество символов в txt и \n
                    fseek(textIn, 0, SEEK_END);                //И выделить память под буффер
                    long int fileSize = ftell(textIn);
                    char* str = (char*)malloc(sizeof(char)*fileSize);
                    fclose(textIn);

                    textIn = fopen("user.txt", "r");
                    int check = getc(textIn);
                    int less = 0, more = 0, zero = 0;
                    int stringCount = 0, wordCounter = 0;
                    char buff[2];
                    char* buffer;

                    while (check != EOF)
                    {
                        fscanf(textIn, "%c[^\n]", buff);                //Считает кол-во строк в файле
                        if (buff[0] == '\n')
                        {
                            stringCount++;
                            check = fgetc(textIn);
                        }
                    }
                    fclose(textIn);
                    
                    textIn = fopen("user.txt", "r");
                    for (int i = 0; i < stringCount; i++)
                    {
                        fgets(str, fileSize, textIn);
                        
                        int j = 0, checking = 0;
                        do
                        {
                            if (str[0] == '-' || isdigit(str[0]))
                            {
                                checking--;
                                break;
                            }
                            else
                            {
                                if (str[j] == ' ')
                                {
                                    wordCounter++;
                                }
                            }
                            j++;
                        } while (str[j] != '\n');
                        
                        if (checking == 0)
                        {
                            fprintf(textOut, "There is %d words in string %d\n", wordCounter + 1, i + 1);
                        }
                        checking = 0;
                        wordCounter = 0;
                    }
                    fclose(textIn);

                    textIn = fopen("user.txt", "r");
                    for (int i = 0; i < stringCount; i++)
                    {
                        fgets(str, fileSize, textIn);
                        char* stringPart = strtok(str, " ");
                        do
                        {
                            if (stringPart[0] == '-')
                            {
                                less++;
                            }
                            if (isdigit(stringPart[0]) && stringPart[0] != '0' && stringPart[0] != '-')
                            {
                                more++;
                            }
                            if (stringPart[0] == '0')
                            {
                                zero++;
                            }
                            stringPart = strtok(NULL, " ");
                        } while (stringPart != NULL);
                        if (isdigit(str[0]) && str[0] != '-')
                        {
                            fprintf(textOut, "Count A<0 == %d, A=0 == %d, A>0 == %d, in string %d\n", less, zero, more, i+1);
                        }
                        more = zero = less = 0;
                    }
                    printf("Want to continue? [1 = Yes / Any other = Back to MENU]\n");
                    scanf("%d", &keyLoop);
                } while (keyLoop == 1);
                break;
            };
            case 6:
            {
                fclose(textIn);
                fclose(textOut);
                flag = false;
                break;
            }
            default:
            {
                printf("Wrong data given, please retry :)\n"); 
                break;
            }
        }
    }
}