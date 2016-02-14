
typedef struct {
	int hour;
	int minute;
	int second;
	int millisec;
	int total_ms;
	char string[16];
	
}Time;

typedef struct {
	char *filename;
	Time start;
}NMF_info;

void countTotalMs (Time *t);
void countHMS (Time *t);
void strtoTime (Time *t);
void Timetostr (Time *t);
void get_log_line_Time (Time *t, char *str);
void get_start_Time (Time *t, char *filename);
void offset_time (Time *offseted_t, Time *source_t, int offset_ms);
void replace_new_time (char *log_line, Time *new_time);
