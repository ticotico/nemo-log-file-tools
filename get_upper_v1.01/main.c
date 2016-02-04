#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIoParameter.h"
void useage(void);
void file_io(char *filename, int nmf_count, FileIoParameter file_io_parameter);

int main (int argc, char *argv[])
{
	if (argc != 6) {
		useage();
		return 0;
	}
	
	int nmf_count = atoi(argv[2]);
	double gived_strength = atof(argv[4]);
	double gived_noise = atof(argv[5]);
	FileIoParameter file_io_parameter;
		
	if (!(nmf_count > 0 && nmf_count <= 20)) {
		printf("invalid file count.\n");
		return -1;
	}
	
	if (strcmp(argv[3], "3G") != 0 && strcmp(argv[3], "4G") != 0) {
		printf("invalid iuput: %s\n", argv[3]);
		return -1;
	}
	
	//set file_io_parameter
	if (strcmp(argv[3], "3G") == 0) {
		
		strcpy(file_io_parameter.strengh_head, "CELLMEAS\0");
		file_io_parameter.strength_col = 18;
		file_io_parameter.gived_strength = gived_strength;
		file_io_parameter.len_strengh_head = 8;
		
		strcpy(file_io_parameter.noise_head, "CELLMEAS\0");
		file_io_parameter.noise_col = 16;
		file_io_parameter.gived_noise = gived_noise;
		file_io_parameter.len_noise_head = 8;
		
	}
	if (strcmp(argv[3], "4G") == 0) {
		
		strcpy(file_io_parameter.strengh_head, "CELLMEAS\0");
		file_io_parameter.strength_col = 12;
		file_io_parameter.gived_strength = gived_strength;
		file_io_parameter.len_strengh_head = 8;
		
		strcpy(file_io_parameter.noise_head, "CI\0");
		file_io_parameter.noise_col = 5;
		file_io_parameter.gived_noise = gived_noise;
		file_io_parameter.len_noise_head = 2;
		
	}
	
	//do nmf log file io
	file_io(argv[1], nmf_count, file_io_parameter);
	
	return 0;
}

