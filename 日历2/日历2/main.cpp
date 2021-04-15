#include <stdio.h>

int main() {

	int isLeapYear(int);
	int monthDays(int, int);
	int getWeekDay(int, int, int);
	void outMonthDays(int, int);

	int Year, Month;
	printf("���������:");
	scanf("%d", &Year);
	printf("%d������Ϊ:\n", Year);
	printf("----------------------------------------------\n");
	for (Month = 1; Month <= 12; Month++) {
		outMonthDays(Year, Month);
	}
	return 0;
}

int isLeapYear(int Year) {
	if (Year % 4 == 0 && Year % 100 != 0 || Year % 400 == 0)
		return 1;
	return 0;
}

int monthDays(int Year, int Month) {
	if (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12) {
		return 31;
	}
	else if (Month == 4 || Month == 6 || Month == 9 || Month == 11) {
		return 30;
	}
	else {
		if (isLeapYear(Year))
			return 29;
		return 28;
	}
}
/*�ж�ĳ��ĳ��ĳ�����ܼ��ľ���ʵ��*/
int getWeekDay(int Year, int Month, int Day) {
	int i, temp, weekday, Days = 0;
	for (i = 1; i <= Month - 1; i++) {
		Days += monthDays(Year, i);
	}
	Days = Days + Day;
	temp = (Year - 1) + (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400 + Days;
	weekday = temp % 7;
	return weekday;
}

void outMonthDays(int Year, int Month) {
	int i, j, weekday;
	printf("%d��%d������\n", Year, Month);
	printf("  ��  һ  ��  ��  ��  ��  ��\n");
	weekday = getWeekDay(Year, Month, 1);
	for (i = 0; i<weekday; i++) {
		printf("    ");
	}
	for (j = 1; j <= monthDays(Year, Month); j++) {
		printf("%4d", j);
		if ((j + weekday) % 7 == 0) {
			printf("\n");
		}
	}
	printf("\n");
	printf("--------------------------------------------------------\n");
}