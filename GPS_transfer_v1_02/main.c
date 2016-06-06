#include <stdio.h>
#include "Time.h"
#include "log_line_io.h"

#define FILENAME_SIZE 128

void conbime_file_by_time(char *output, char *dest, char *source, int offest_ms);

int main (int argc, char *argv[])
{
	if(argc < 3) return 0;
	
	NMF_info source, destination;
	int time_offset_ms;
	char insert_message[] = {'G', 'P', 'S', '\0'};
	char remove_message_dest[FILENAME_SIZE];
	char only_message_source[FILENAME_SIZE];
	FILE *test_fp;
	
	source.filename = argv[3];
	destination.filename = argv[2];
	
	getnll(destination.filename, insert_message, remove_message_dest);
	getall(source.filename, insert_message, only_message_source);
	
	//get start time offset
	get_start_Time(&destination.start, destination.filename);
	get_start_Time(&source.start, source.filename);
	time_offset_ms = destination.start.total_ms - source.start.total_ms;
	
	//printf("source.start = %s\n", source.start.string);
	//printf("dest.start = %s\n", destination.start.string);
	//printf("offset time (ms) = %d\n", time_offset_ms);
	
	printf("have %s: %s\n", insert_message, argv[3]);
	printf("no %s: %s\n", insert_message, argv[2]);
	conbime_file_by_time(argv[1], remove_message_dest, only_message_source, time_offset_ms);
	test_fp = fopen(argv[1], "r");
	if(test_fp != NULL) printf("new log: %s\n\n", argv[1]);
	else printf("Transfer fail. Please cheak your log file or file path.\n");
	fclose(test_fp);
	
	remove(remove_message_dest);
	remove(only_message_source);
	
	return 0;
}
