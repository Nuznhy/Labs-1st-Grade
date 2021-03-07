#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <conio.h>

/*12. Створити масив структур, кожна з яких складається з таких елементів: факультет, курс, студент. 
Для факультету задати його назву та номер групи. Для студента задати прізвище студентів, екзаменаційні оцінки. 
Створений масив записати до бінарного файлу. Передбачити можливість доповнити файл, замінити дані в файлі, 
видалити дані з файлу. Реалізувати запити: 
1) визначити прізвища студентів, групу і факультет, де середній бал студентів 4.5; 
2) вилучити прізвища студентів першого курсу, які мають три двійки; 
3) відсортувати назви факультетів за умови зростання успішності студентів. */

typedef struct
{
	char student_name[32];
	int math_mark, prog_mark, science_mark;
	int year;
} Student;

typedef struct
{
	char faculty_name[16];
	char group_name[16];
	int student_num;
	Student* student_list;
} Faculty;

void add_faculty(FILE*);
void add_student(FILE*);
void display_all(FILE*);
void delete_f(FILE*);
void delete_s(FILE*);
void exellent(FILE*);
void del_bad(FILE* fp);
void print_fac(FILE*, int);
void f_search(FILE*, int);
void print_stud(FILE*, int);
void stud_seek(FILE*, int);

int main()
{
	FILE* fp;
	char case_switch_one[16] = { '\0' }, case_switch_two[16] = { '\0' };
	while (1)
	{
		system("cls");
		printf("\t\tMenu\t\n");
		printf("1. Add a Record\t\t\t\t'add'\n");
		printf("2. Display all from file\t\t'display'\n");
		printf("3. Delete Faculty\t\t\t'fdelete'\n");
		printf("3. Delete Student\t\t\t'sdelete'\n");
		printf("4. Print makrs > 4.5\t\t\t'exellent'\n");
		fflush(stdin);
		fgets(case_switch_one, 16, stdin);
		//getchar();
		if (!strcmp("add\n", case_switch_one))
		{
			fp = fopen("text.bin", "rb+");
			if (!fp)
			{
				printf("Failed to open file\n Creating a new one...\n");
				fp = fopen("text.bin", "wb+");
				fclose(fp);
				fp = fopen("text.bin", "rb+");
			}
			printf("What do you wanna add?\n");
			printf("'faculty'\n");
			printf("'student'\n");
			fflush(stdin);
			fgets(case_switch_two, 16, stdin);
			//getchar();

			if (!strcmp("faculty\n", case_switch_two))
			{
				add_faculty(fp);
				fclose(fp);
			}
			if (!strcmp("student\n", case_switch_two))
			{
				add_student(fp);
				fclose(fp);
			}
		}
		if (!strcmp("display\n", case_switch_one))
		{
			fp = fopen("text.bin", "rb+");
			display_all(fp);
			fclose(fp);
			printf("Press any button to continue");
		}
		if (!strcmp("sdelete\n", case_switch_one))
		{
			fp = fopen("text.bin", "rb+");
			delete_s(fp);
			fclose(fp);
		}
		if (!strcmp("fdelete\n", case_switch_one))
		{
			fp = fopen("text.bin", "rb+");
			delete_f(fp);
			fclose(fp);
		}
		if (!strcmp("exellent\n", case_switch_one))
		{
			fp = fopen("text.bin", "rb+");
			exellent(fp);
			fclose(fp);
		}
		if (!strcmp("deletebad\n", case_switch_one))
		{
			fp = fopen("text.bin", "rb+");
			del_bad(fp);
			fclose(fp);
		}
	}
}

void add_faculty(FILE* fp)
{
	int faculty_num = 0;
	char mark, num_of_students, course;
	Faculty* fac = NULL;
	printf("Adding new Faculty\n");

	fseek(fp, 0, SEEK_SET);
	fread(&faculty_num, sizeof(int), 1, fp);
	faculty_num++;
	fseek(fp, -4, SEEK_CUR);
	fwrite(&faculty_num, sizeof(int), 1, fp);
	f_search(fp, faculty_num);
	fac = (Faculty*)calloc(1, sizeof(Faculty));
	if (fac == NULL)
	{
		printf("Failed to allocate memory\nExit...");
		exit(0);
	}
	printf("Enter the name of the  Faculty\n");
	fflush(stdin);
	fgets(fac->faculty_name, 16, stdin);
	printf("You have entered the name of Faculty - %s\n", fac->faculty_name);

	printf("Enter the name of group\n");
	fflush(stdin);
	fgets(fac->group_name, 16, stdin);
	printf("You have entered the name of group - %s\n", fac->group_name);

	printf("How many students do you wish do add?\n");
	num_of_students = getc(stdin);
	gets();
	fac->student_num = num_of_students - '0';

	fflush(stdin);
	fac->student_list = (Student*)calloc(fac->student_num, sizeof(Student));
	if (fac->student_list == NULL)
	{
		printf("Failed to allocate memory\nExit...");
		exit(0);
	}
	for (int i = 0; i < fac->student_num; i++)
	{
		printf("Enter Student's name\n");
		printf("----%p----\n", fac->student_list[i].student_name);
		fflush(stdin);
		fgets(fac->student_list[i].student_name, 32, stdin);

		printf("Enter the course for this student\n");
		course = getc(stdin);
		fac->student_list[i].year = course - '0';
		gets();

		printf("Enter math mark for %s", fac->student_list[i].student_name);
		mark = getc(stdin);
		fac->student_list[i].math_mark = mark - '0';
		gets();

		printf("Enter programmin mark for %s", fac->student_list[i].student_name);
		mark = getc(stdin);
		fac->student_list[i].prog_mark = mark - '0';
		gets();

		printf("Enter science mark for %s", fac->student_list[i].student_name);
		mark = getc(stdin);
		fac->student_list[i].science_mark = mark - '0';
		gets();
	}

	fwrite(fac->faculty_name, sizeof(char) * 16, 1, fp);
	fwrite(fac->group_name, sizeof(char) * 16, 1, fp);
	fwrite(&fac->student_num, sizeof(int), 1, fp);
	for (int i = 0; i < fac->student_num; i++)
	{
		fwrite(fac->student_list[i].student_name, sizeof(char) * 32, 1, fp);
		fwrite(&fac->student_list[i].year, sizeof(int), 1, fp);
		fwrite(&fac->student_list[i].math_mark, sizeof(int), 1, fp);
		fwrite(&fac->student_list[i].prog_mark, sizeof(int), 1, fp);
		fwrite(&fac->student_list[i].science_mark, sizeof(int), 1, fp);
	}
	printf("Add has been completed\n");
}

void add_student(FILE* fp)
{
	int fac_num, student_num, int_add, new_student_num, old_student_num, offset = 0, shift_data_size = 0;
	char fac_name[16], add[2] = { 0 }, mark, course;
	Student* newstudent;

	printf("To which faculty do you wish to add Student?\n");
	fseek(fp, 0, SEEK_SET);
	fread(&fac_num, sizeof(int), 1, fp);
	print_fac(fp, fac_num);
	fflush(stdin);

	fgets(add, 2, stdin);
	int_add = atoi(add);

	fseek(fp, sizeof(int), SEEK_SET);
	f_search(fp, int_add);
	fseek(fp, sizeof(char) * 32, SEEK_CUR);											//Пропускаем имя факультета и группы
	fread(&old_student_num, sizeof(int), 1, fp);
	
	student_num = 1 + old_student_num;
	fseek(fp, -4, SEEK_CUR);
	fwrite(&student_num, sizeof(int), 1, fp);										//Переписываем новое количество студентов
	stud_seek(fp, student_num);

	newstudent = (Student*)calloc(1, sizeof(Student));
	if (newstudent == NULL)
	{
		printf("Failed to allocate memory\nExit...");
		exit(0);
	}
	
	printf("Enter Student's name\n");
	printf("----%p----\n", newstudent->student_name);
	fflush(stdin);
	gets();
	fgets(newstudent->student_name, 32, stdin);


	printf("Enter the course for this student\n");
	course = getc(stdin);
	newstudent->year = course - '0';
	gets();

	printf("Enter math mark for %s", newstudent->student_name);
	mark = getc(stdin);
	newstudent->math_mark = mark - '0';
	gets();

	printf("Enter programmin mark for %s", newstudent->student_name);
	mark = getc(stdin);
	newstudent->prog_mark = mark - '0';
	gets();

	printf("Enter science mark for %s", newstudent->student_name);
	mark = getc(stdin);
	newstudent->science_mark = mark - '0';
	gets();
	fflush(stdin);
	
	offset = (sizeof(char) * 32 + sizeof(int) * 4);
	fseek(fp, (sizeof(char) * 32 + sizeof(int) * 4), SEEK_CUR);			//Размер одного студента + оценки
	for (int i = 0; i < fac_num - int_add; i++)							//Считаем сколько данных нужно сдвинуть
	{
		fseek(fp, sizeof(char) * 32, SEEK_CUR);
		shift_data_size += sizeof(char) * 32;
		fread(&student_num, sizeof(int), 1, fp);
		shift_data_size += sizeof(int);
		fseek(fp, offset * student_num, SEEK_CUR);
		shift_data_size += offset * student_num;
	}

	for (int i = 0; i < shift_data_size; i++)
	{
		char temp;
		fseek(fp, -offset - 1, SEEK_CUR);
		fread(&temp, sizeof(char), 1, fp);
		fseek(fp, offset - 1, SEEK_CUR);
		fwrite(&temp, sizeof(char), 1, fp);
		fseek(fp, -1, SEEK_CUR);
	}
	fseek(fp, -offset, SEEK_CUR);
	
	fwrite(newstudent->student_name, sizeof(char) * 32, 1, fp);
	fwrite(&newstudent->year, sizeof(int), 1, fp);
	fwrite(&newstudent->math_mark, sizeof(int), 1, fp);
	fwrite(&newstudent->prog_mark, sizeof(int), 1, fp);
	fwrite(&newstudent->science_mark, sizeof(int), 1, fp);
}

void display_all(FILE* fp)
{
	int fac_num, student_num, course, mark1, mark2, mark3;
	char fac_name[16], group_name[16], student_name[32];
	fseek(fp, 0, SEEK_SET);
	fread(&fac_num, sizeof(int), 1, fp);
	for (int i = 1; i <= fac_num; i++)
	{
		fread(&fac_name, sizeof(char) * 16, 1, fp);
		fread(&group_name, sizeof(char) * 16, 1, fp);
		fread(&student_num, sizeof(int), 1, fp);
		printf("Faculty: %s\nGroup: %s\n", fac_name, group_name);
		for (int j = 0; j < student_num; j++)
		{
			fread(&student_name, sizeof(char) * 32, 1, fp);
			fread(&course, sizeof(int), 1, fp);
			fread(&mark1, sizeof(int), 1, fp);
			fread(&mark2, sizeof(int), 1, fp);
			fread(&mark3, sizeof(int), 1, fp);
			printf("Name: %s", student_name);
			printf("\tCourse: %d", course);
			printf("\t\tMath mark: %d", mark1);
			printf("\t\tProgrammin mark: %d", mark2);
			printf("\t\tScience mark: %d\n", mark3);
		}
	}
	printf("\n");
	printf("Press any button to continue...");
	gets();

}

void delete_f(FILE* fp)
{
	int int_del, int_del_stud, fac_num, old_fac_num, student_num, key, offset = 0, shift_data_size = 0, new_stud_num;
	char del[2] = { 0 }, del_stud[2] = { 0 }, empty = 0;
	fseek(fp, 0, SEEK_SET);
	fread(&fac_num, sizeof(int), 1, fp);
	printf("You want to delete:\n1: Faculty\n");
	printf("2:Student\n");
	
	printf("Choose faculty to delete:\n");
	print_fac(fp, fac_num);
	fseek(fp, 0, SEEK_SET);
	old_fac_num = fac_num;
	fac_num--;
	fwrite(&fac_num, sizeof(int), 1, fp);
	fflush(stdin);
	gets();
	fgets(del, 2, stdin);
	int_del = atoi(del);

	f_search(fp, int_del);
	fseek(fp, sizeof(char) * 32, SEEK_CUR);
	offset += sizeof(char) * 32;
	fread(&student_num, sizeof(int), 1, fp);
	offset += sizeof(int);
	for (int i = 0; i < student_num; i++)
	{
		fseek(fp, sizeof(char) * 32, SEEK_CUR);
		offset += sizeof(char) * 32;
		fseek(fp, sizeof(int) * 4, SEEK_CUR);
		offset += sizeof(int) * 4;
	}

	for (int i = 0; i < old_fac_num - int_del; i++)
	{
		shift_data_size += sizeof(char) * 32;
		fseek(fp, sizeof(char) * 32, SEEK_CUR);
		shift_data_size += sizeof(int);
		fread(&student_num, sizeof(int), 1, fp);
		shift_data_size += student_num * (sizeof(char) * 32 + sizeof(int) * 4);
		fseek(fp, student_num * (sizeof(char) * 32 + sizeof(int) * 4), SEEK_CUR);
	}

	fseek(fp, -shift_data_size, SEEK_CUR);															
	for (int i = 0; i < shift_data_size; i++)
	{
		char t;
		fread(&t, sizeof(char), 1, fp);
		fseek(fp, -offset - 1, SEEK_CUR);
		fwrite(&t, sizeof(char), 1, fp);
		fseek(fp, offset, SEEK_CUR);
	}																						
	fseek(fp, -offset, SEEK_CUR);
	for (int i = 0; i < offset; i++)															
	{
		fwrite(&empty, sizeof(char), 1, fp);
	}	
}

void delete_s(FILE* fp)
{
	int int_del, int_del_stud, fac_num, old_fac_num, student_num, key, offset = 0, shift_data_size = 0, new_stud_num;
	char del[2] = { 0 }, del_stud[2] = { 0 }, empty = 0;
	fseek(fp, 0, SEEK_SET);
	fread(&fac_num, sizeof(int), 1, fp);
	printf("You want to delete:\n1: Faculty\n");
	printf("2:Student\n");
	
	printf("Choose from whitch faculty to delete:\n");
	print_fac(fp, fac_num);
	fseek(fp, sizeof(int), SEEK_SET);

	fflush(stdin);
	gets();
	fgets(del, 2, stdin);
	int_del = atoi(del);

	f_search(fp, int_del);
	fseek(fp, sizeof(char) * 32, SEEK_CUR);
	fread(&student_num, sizeof(int), 1, fp);

	new_stud_num = student_num - 1;
	fseek(fp, -4, SEEK_CUR);
	fwrite(&new_stud_num, sizeof(int), 1, fp);
	print_stud(fp, student_num);

	fseek(fp, sizeof(int), SEEK_SET);
	f_search(fp, int_del);
	fseek(fp, sizeof(char) * 32, SEEK_CUR);
	fseek(fp, sizeof(int), SEEK_CUR);

	fflush(stdin);
	gets();
	fgets(del_stud, 2, stdin);
	int_del_stud = atoi(del_stud);
	if (int_del_stud != 1)
	{
		stud_seek(fp, int_del_stud);
	}

	offset += sizeof(char) * 32;
	offset += sizeof(int) * 4;
	fseek(fp, sizeof(char) * 32, SEEK_CUR);
	fseek(fp, sizeof(int) * 4, SEEK_CUR);
	for (int i = 0; i < student_num - int_del_stud; i++)
	{
		shift_data_size += sizeof(char) * 32;
		shift_data_size += sizeof(int) * 4;
		fseek(fp, sizeof(char) * 32, SEEK_CUR);
		fseek(fp, sizeof(int) * 4, SEEK_CUR);
	}
	for (int i = 0; i < fac_num - int_del; i++)
	{
		shift_data_size += sizeof(char) * 32;
		fseek(fp, sizeof(char) * 32, SEEK_CUR);
		shift_data_size += sizeof(int);
		fread(&student_num, sizeof(int), 1, fp);
		for (int i = 0; i < student_num; i++)
		{
			shift_data_size += sizeof(char) * 32;
			fseek(fp, sizeof(char) * 32, SEEK_CUR);
			shift_data_size += sizeof(int) * 4;
			fseek(fp, sizeof(int) * 4, SEEK_CUR);
		}
	}

	fseek(fp, -shift_data_size, SEEK_CUR);
	for (int i = 0; i < shift_data_size; i++)
	{
		char temp;
		fread(&temp, sizeof(char), 1, fp);
		fseek(fp, -offset - 1, SEEK_CUR);
		fwrite(&temp, sizeof(char), 1, fp);
		fseek(fp, offset, SEEK_CUR);
	}
	fseek(fp, -offset, SEEK_CUR);
	for (int i = 0; i < offset; i++)
	{
		fwrite(&empty, sizeof(char), 1, fp);
	}
}

void exellent(FILE* fp)
{
	int counter, mark, fac_num, stud_num, offset;
	char fac_name[16], group_name[16], stud_name[32];
	float sum = 0;
	
	fseek(fp, 0, SEEK_SET);
	fread(&fac_num, sizeof(int), 1, fp);
	for (int i = 0; i < fac_num; i++)
	{
		fread(&fac_name, sizeof(char) * 16, 1, fp);
		fread(&group_name, sizeof(char) * 16, 1, fp);
		fread(&stud_num, sizeof(int), 1, fp);
		counter = stud_num * 3;
		offset = (sizeof(char) * 32 + sizeof(int) * 4) * stud_num;
		for (int i = 0; i < stud_num; i++)
		{
			fread(&stud_name, sizeof(char) * 32, 1, fp);
			fseek(fp, sizeof(int), SEEK_CUR);
			fread(&mark, sizeof(int), 1, fp);
			sum += mark;
			fread(&mark, sizeof(int), 1, fp);
			sum += mark;
			fread(&mark, sizeof(int), 1, fp);
			sum += mark;
		}
		fseek(fp, -offset, SEEK_CUR);
		if ((sum / counter) > 4.5) 
		{
			printf("Group: %s\n", fac_name);
			printf("Faculty: %s\n", group_name);
			for (int i = 0; i < stud_num; i++)
			{
				fread(&stud_name, sizeof(char) * 32, 1, fp);
				printf("%s", stud_name);
				fseek(fp, sizeof(int) * 4, SEEK_CUR);
			}
		}
		sum = 0;
	}
	printf("\n");
	printf("Press any button to continue...");
	gets();
}

void del_bad(FILE* fp)
{
	int fac_num, student_num, mark1, mark2, mark3, course, offset = 0, shift_data_size = 0;
	char stud_name[16], empty = 0;
	fseek(fp, 0, SEEK_SET);
	fread(&fac_num, sizeof(int), 1, fp);
	for (int j = 0; j < fac_num; j++)
	{
		fseek(fp, sizeof(char) * 32, SEEK_CUR);
		fread(&student_num, sizeof(int), 1, fp);
		for (int f = 0; f < student_num; f++)
		{
			fseek(fp, sizeof(char) * 32, SEEK_CUR);
			fread(&course, sizeof(int), 1, fp);
			fread(&mark1, sizeof(int), 1, fp);
			fread(&mark2, sizeof(int), 1, fp);
			fread(&mark3, sizeof(int), 1, fp);
			if (course == 1 && mark1 < 3 && mark2 < 3 && mark3 < 3)
			{
				offset += sizeof(char) * 32;
				offset += sizeof(int) * 4;
				for (int i = 0; i < student_num - f; i++)
				{
					shift_data_size += sizeof(char) * 32;
					shift_data_size += sizeof(int) * 4;
					fseek(fp, sizeof(char) * 32, SEEK_CUR);
					fseek(fp, sizeof(int) * 4, SEEK_CUR);
				}
				for (int i = 0; i < fac_num - j; i++)
				{
					shift_data_size += sizeof(char) * 32;
					fseek(fp, sizeof(char) * 32, SEEK_CUR);
					shift_data_size += sizeof(int);
					fread(&student_num, sizeof(int), 1, fp);
					for (int i = 0; i < student_num; i++)
					{
						shift_data_size += sizeof(char) * 32;
						fseek(fp, sizeof(char) * 32, SEEK_CUR);
						shift_data_size += sizeof(int) * 4;
						fseek(fp, sizeof(int) * 4, SEEK_CUR);
					}
				}

				fseek(fp, -shift_data_size, SEEK_CUR);
				for (int i = 0; i < shift_data_size; i++)
				{
					char temp;
					fread(&temp, sizeof(char), 1, fp);
					fseek(fp, -offset - 1, SEEK_CUR);
					fwrite(&temp, sizeof(char), 1, fp);
					fseek(fp, offset, SEEK_CUR);
				}
				fseek(fp, -offset, SEEK_CUR);
				for (int i = 0; i < offset; i++)
				{
					fwrite(&empty, sizeof(char), 1, fp);
				}
			}
		}
	}
}

void f_search(FILE* fp, int point)
{
	int student_num;
	for (int i = 1; i < point; i++)
	{
		fseek(fp, sizeof(char) * 32, SEEK_CUR);
		fread(&student_num, sizeof(int), 1, fp);
		fseek(fp, (sizeof(char) * 32 + 4 * sizeof(int)) * student_num, SEEK_CUR);
	}
}

void print_fac(FILE* fp, int fac_num)
{
	int student_num;
	char fac_name[16];
	for (int i = 1; i <= fac_num; i++)
	{
		fread(&fac_name, sizeof(char) * 16, 1, fp);
		printf("'%d': %s\n", i, fac_name);
		fseek(fp, sizeof(char) * 16, SEEK_CUR);
		fread(&student_num, sizeof(int), 1, fp);
		fseek(fp, (sizeof(char) * 32 + 4 * sizeof(int)) * student_num, SEEK_CUR);
	}
}

void print_stud(FILE* fp, int student_num)
{
	char student_name[32];
	int offset;
	offset = sizeof(int) * 4 + sizeof(char) * 32;
	for (int i = 0; i < student_num; i++)
	{
		fread(&student_name, sizeof(char) * 32, 1, fp);
		printf("'%d' %s", i + 1, student_name);
		fseek(fp, sizeof(int) * 4, SEEK_CUR);
	}
}

void stud_seek(FILE* fp, int point)
{
	fseek(fp, (point-1) * sizeof(char) * 32, SEEK_CUR);
	fseek(fp, (point-1) * sizeof(int) * 4, SEEK_CUR);
}