#include <stdio.h>

static char non_leap[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char leap[]     = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char *days[]    = {non_leap, leap};

/* day_of_year: get yearday from year/month/day; pointer version */
int day_of_year(int year, int month, int day)
{
	char *pmonth;
	int leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

	for (pmonth = days[leap]; pmonth != days[leap] + month; ++pmonth)
		day += *pmonth;
	return day;
}

/* month_day: set month/day from year and yearday; pointer version */
void month_day(int year, int yearday, int *month, int *day)
{
	char *pmonth;
	int leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

	for (pmonth = days[leap]; yearday > *pmonth; ++pmonth)
		yearday -= *pmonth;
	*month = pmonth - days[leap];
	*day = yearday;
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

