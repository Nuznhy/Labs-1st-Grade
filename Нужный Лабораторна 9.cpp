#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

/* 15 Варіант
Заданий масив записів, який містить відомості-прізвища і назви груп. 
Масив впорядкований за прізвищами. 
Програма видаляє записи, які містять задане прізвище, 
зрушуючи нижні елементи вгору (заповнюючи ними порожнє місце). */

typedef struct
{
	const char* group;
	const char* person;
} Mystruct;

Mystruct* create(const char* group, const char* person)
{
	Mystruct* s = (Mystruct*)malloc(sizeof(Mystruct));
	s->group = group;
	s->person = person;
	return s;
}

int main()
{
	Mystruct* table[] = { create("DA-91", "Andrey"), create("DA-91", "Nikita"), create("DA-91", "Lera"), create("DA-92", "Alex"), create("DA-92", "Max"),
		create("DA-92", "Tom") };
	int n = sizeof(table) / sizeof(table[0]);
		
	while (1) 
	{
		for (Mystruct** p = table; p < table + n; p++)
		{
			printf("Group: %s \t Name: %s \n", (*p)->group, (*p)->person);
		}

		char* name = (char*)malloc(30*sizeof(char));
		scanf("%s", name);

		int index = 0;

		for (int i = 0; i < n; i++)
		{
			if (strcmp(table[i]->person, name) == 0)
			{
				index = i;
				for (int i = index + 1; i < n; i++)
				{
					table[i - 1] = table[i];
				}
				n--;
				table[n] = nullptr;
			}
		}

		printf("\n");

		printf("%s", name);

		printf("\n");
		
		if (n == 0)
		{
			break;
		}
	}
}
