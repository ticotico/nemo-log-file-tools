#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#define NMF_LINE_SIZE 10000

void conbime_file_by_time(char *output, char *dest, char *source, int offest_ms)
{
	FILE *fp_dest, *fp_source, *fp_out;
	char buf_dest[NMF_LINE_SIZE], buf_source[NMF_LINE_SIZE];
	Time dest_time, source_time, offseted_time;
	
	fp_dest = fopen(dest, "r");
	if(fp_dest == NULL) {
		printf("cannot open %s\n", dest);
		exit(-1);
	}
	
	fp_source = fopen(source, "r");
	if(fp_dest == NULL) {
		printf("cannot open %s\n", source);
		exit(-1);
	}
	
	fp_out = fopen(output, "w");
	if(fp_dest == NULL) {
		printf("cannot open %s\n", output);
		exit(-1);
	}
	
	fgets(buf_dest, NMF_LINE_SIZE, fp_dest);
	fgets(buf_source, NMF_LINE_SIZE, fp_source);
	get_log_line_Time(&source_time, buf_source);
	while (!feof(fp_dest)) {
		
		if(buf_dest[0] == '#') {
			fputs(buf_dest, fp_out);
			fgets(buf_dest, NMF_LINE_SIZE, fp_dest);
			continue;
		}
		else {
			get_log_line_Time(&dest_time, buf_dest);
		}
		//put source line to output
		while(dest_time.total_ms + offest_ms >= source_time.total_ms && !feof(fp_source)) {
			offset_time(&offseted_time, &source_time, offest_ms);
			replace_new_time(buf_source, &offseted_time);
			fputs(buf_source, fp_out);
			fgets(buf_source, NMF_LINE_SIZE, fp_source);
			get_log_line_Time(&source_time, buf_source);
		}
		
		fputs(buf_dest, fp_out);
		fgets(buf_dest, NMF_LINE_SIZE, fp_dest);
	}
	
	fclose(fp_dest);
	fclose(fp_source);
	fclose(fp_out);
}
