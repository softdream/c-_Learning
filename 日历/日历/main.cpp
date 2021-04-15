#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
int monthDay[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
int isLeap(int year)
{
	if (year % 4) return 0;//��ͨ���ܱ�4�����Ҳ��ܱ�100������Ϊ����
	if (year % 400) return 1;//�������ܱ�400������������
	if (year % 100) return 0;
	return 1;
}

int getWeek(int year, int month, int day)
{
	int c, y, week;
	if (month == 1 || month == 2) { //�ж�month�Ƿ�Ϊ1��2��
		year--;
		month += 12;
	}
	c = year / 100;
	y = year - c * 100;
	week = (c / 4) - 2 * c + (y + y / 4) + (13 * (month + 1) / 5) + day - 1;
	while (week < 0) { week += 7; }
	week %= 7;
	return week;
}

void display(int year, int month, int x)
{
	int monthDays, weekFirst, i;
	monthDays = monthDay[month] + (month == 2 ? isLeap(year) : 0);
	weekFirst = getWeek(year, month, 1);
	system("cls");
	time_t t;
	struct tm * lt;
	time(&t);//��ȡUnixʱ�����
	lt = localtime(&t);//תΪʱ��ṹ��
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);  //���������
	SetConsoleTextAttribute(handle, 0x0f);  //Ĭ�Ϻڵװ���
	printf("%d/%d/%d \n\n", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);
	printf("1����wasd�������������ҷ��ʵ������ڡ�\n\n2���������������Է������¡� \n\n3����c���Բ�ѯ���£������֮���ÿո�����������Զ�β�ѯ���¡�\n\n");
	printf("             -------%4d��----%2d��-------\n", year, month);
	printf("������\t����һ\t���ڶ�\t������\t������\t������\t������\n");
	for (i = 0; i<weekFirst; i++) printf("\t");
	for (i = 1; i <= monthDays; i++)
	{
		if ((i == lt->tm_mday + x) && (month == lt->tm_mon + 1) && (year == lt->tm_year + 1900)) {
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		}
		else if (weekFirst == 0 || weekFirst == 6) {   //��6������ɺ�ɫ     0,1,2,3,4,5,6  ��Ӧ�����յ���
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
		}
		else {
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		}
		printf("%d\t", i);
		weekFirst++;
		if (weekFirst >= 7) { printf("\n"); weekFirst = 0; }
	}
}

int main()
{
	int year, month, chr, i = 0;
	time_t timer;
	struct tm *tblock;
	timer = time(NULL);
	tblock = localtime(&timer);
	year = tblock->tm_year + 1900;
	month = tblock->tm_mon + 1;
	while (1)
	{
		display(year, month, 0);
	A:chr = getch();
		if (chr == 0x4b) {
			month--;
			if (month<1) { month = 12; year--; }
		}
		if (chr == 0x4d) {
			month++;
			if (month>12) { month = 1; year++; }
		}
		if (chr == 0x50) {
			year--;
		}
		if (chr == 0x48) {
			year++;
		}
		if (chr == 'c') {
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("\n\n����������£�");
			scanf("%d%d", &year, &month);
		}
		if (chr == 'w') {
			i = i - 7; display(year, month, i); goto A;
		}
		if (chr == 's') {
			i = i + 7; display(year, month, i); goto A;
		}
		if (chr == 'a') {
			i--; display(year, month, i); goto A;
		}
		if (chr == 'd') {
			i++; display(year, month, i); goto A;
		}
	}
	return 0;
}