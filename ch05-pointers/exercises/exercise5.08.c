#include <stdio.h>

static char days[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: return day of year from year, month and day */
int day_of_year(int year, int month, int day)
{
	int i, yearday, leap;

	if (month < 1 || month > 12)
	{
		printf("error: month should be between 1 and 12.\n");
		return -1;
	}

	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	if (day < 1 || day > days[leap][month])
	{
		printf("error: day should be between 1 and %d for month %d.\n",
		       days[leap][month], month);
		return -1;
	}

	for (i = 0, yearday = 0; i < month; ++i)
		yearday += days[leap][i];

	return yearday + day;
}

int main()
{
	printf("%d\n", day_of_year(2020, 4, -18));
	return 0;
}
