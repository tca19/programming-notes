#include <stdio.h>

static char days[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: return day of year from year/month/day; handle bad inputs */
int day_of_year(int year, int month, int day)
{
	int i, leap;

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

	for (i = 1; i < month; ++i)
		day += days[leap][i];

	return day;
}

/* month_day: set month/day from day of year; handle bad input */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	if (yearday < 1 || yearday > (365+leap))
	{
		printf("error: yearday must be between 1 and %d\n", 365+leap);
		pmonth = NULL;
		pday   = NULL;
	}
	for (i = 1; yearday > days[leap][i]; ++i)
		yearday -= days[leap][i];
	*pmonth = i;
	*pday = yearday;
}

int main()
{
	int year, month, day, yearday;

	year = 1993;
	month = 10;
	day = 22;
	yearday = 167;
	printf("Yearday of %d/%d/%d : %d\n", day, month, year,
	       day_of_year(year, month, day));
	month_day(year, yearday, &month, &day);
	printf("%d-th day of year %d : %d/%d\n", yearday, year, day, month);
	return 0;
}
