#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Time.h"
#include "log_line_io.h"

#define NMF_LNE_SIZE 10000

void countTotalMs (Time *t)
{
	t->total_ms = t->hour * 3600000 + t->minute * 60000
				+ t->second * 1000 + t->millisec;
}

void countHMS (Time *t)
{
	int temp = t->total_ms;
	
	t->millisec = temp % 1000;
	temp /= 1000;
	t->second = temp % 60;
	temp /= 60;
	t->minute = temp % 60;
	temp /= 60;
	t->hour = temp % 24;
}

void strtoTime (Time *t)
{
	sscanf(t->string, "%02d:%02d:%02d.%03d\0", &t->hour, &t->minute, &t->second, &t->millisec);
}

void Timetostr (Time *t)
{
	sprintf(t->string, "%02d:%02d:%02d.%03d\0", t->hour, t->minute, t->second, t->millisec);
}

void get_log_line_Time (Time *t, char *log_line)
{
	getCol(t->string, log_line, 2);
	strtoTime(t);
	countTotalMs(t);
}

void get_start_Time (Time *t, char *filename)
{
	char buf[NMF_LNE_SIZE];
	getfll(buf, filename, "#START");
	get_log_line_Time(t, buf);
}

void offset_time (Time *offseted_t, Time *source_t, int offset_ms)
{
	offseted_t->total_ms = source_t->total_ms + offset_ms;
	countHMS(offseted_t);
	Timetostr(offseted_t);
}

void replace_new_time (char *log_line, Time *new_time)
{
	char *start = log_line;
	while (*start != '\0' && *start != ',') {
		start++;
	}
	if (*start != '\0')
		strncpy(start + 1, new_time->string, 12);
}
