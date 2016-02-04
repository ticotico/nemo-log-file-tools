#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FileIoParameter.h"

typedef struct {
	int strength_total_count;
	int noise_total_count;
	int strength_upper_count;
	int noise_upper_count;
	double strength_upper_percentage;
	double noise_upper_percentage;
}StrengthNoiseParameter;

void file_io(char *filename, int nmf_count, FileIoParameter file_io_parameter)
{
	StrengthNoiseParameter str_noi_par[21];
	int i;
	char input_file[256];
	char output_buf[8196] = "\0";
	char output_col[256];
	char read_line[4096];
	const char dot[2] = ",";
	const char newl[2] = "\n";
	int dot_count;
	char *pt_read_line;
	int col_len;
	
	
	//initialize str_noi_par
	for (i = 1; i <= nmf_count; i++) {
		str_noi_par[i].strength_total_count = 0;
		str_noi_par[i].noise_total_count = 0;
		str_noi_par[i].strength_upper_count = 0;
		str_noi_par[i].noise_upper_count = 0;
	}
	
	//read filename.*.nmf ot get strength and noise count
	for (i = 1; i <= nmf_count; i++) {
		sprintf(input_file, "%s.%d.nmf\0", filename, i);
		FILE *ptr_fin = fopen(input_file, "r");
		
		if (ptr_fin == NULL) {
			printf("cannot open %s\n", input_file);
			return;
		}
		
		//get count here
		while (!feof(ptr_fin)) {
			fgets(read_line, 4096, ptr_fin);
			
			//get strength
			if (strncmp(read_line, file_io_parameter.strengh_head, file_io_parameter.len_strengh_head) == 0) {
				//get col
				pt_read_line = read_line;
				dot_count = 0;
				col_len = 0;
				while (dot_count < file_io_parameter.strength_col)
					if (*pt_read_line++ == ',')
						dot_count++;
				while (*(pt_read_line + col_len) != ',')
					col_len++;
				strncpy(output_col, pt_read_line, col_len);
				
				//atof colunm and compare
				if(atof(output_col) >= file_io_parameter.gived_strength)
					str_noi_par[i].strength_upper_count++;
				str_noi_par[i].strength_total_count++;
			}
			
			//get noise
			if (strncmp(read_line, file_io_parameter.noise_head, file_io_parameter.len_noise_head) == 0) {
				//get col
				pt_read_line = read_line;
				dot_count = 0;
				col_len = 0;
				while (dot_count < file_io_parameter.noise_col)
					if (*pt_read_line++ == ',')
						dot_count++;
				while (*(pt_read_line + col_len) != ',')
					col_len++;
				strncpy(output_col, pt_read_line, col_len);
				
				//atof colunm and compare
				if(atof(output_col) >= file_io_parameter.gived_noise)
					str_noi_par[i].noise_upper_count++;
				str_noi_par[i].noise_total_count++;
			}
		}
		
		fclose (ptr_fin);
	}
	
	//do output here (filename: Newfile.csv)
	FILE *ptr_out = fopen("Newfile.csv", "a");
	if (ptr_out == NULL) {
		printf("cannot open Newfile.csv\n");
		return ;
	}
	
	strcpy(output_buf, filename);
	//set strength output string
	for (i = 1; i <= nmf_count; i++) {
		sprintf(output_col, ",=%d/%d", str_noi_par[i].strength_upper_count, str_noi_par[i].strength_total_count);
		strcat(output_buf, output_col);
	}
	strcat(output_buf, dot);
	strcat(output_buf, filename);
	//set noise output string
	for (i = 1; i <= nmf_count; i++) {
		sprintf(output_col, ",=%d/%d", str_noi_par[i].noise_upper_count, str_noi_par[i].noise_total_count);
		strcat(output_buf, output_col);
	}
	strcat(output_buf, newl);
	
	//output strung to target file
	fputs(output_buf, ptr_out);
	
	
	fclose (ptr_out);
	
	return;
}
