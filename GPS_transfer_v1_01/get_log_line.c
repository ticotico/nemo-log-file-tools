#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_SIZE 128
#define NMF_LNE_SIZE 10000

int getCol(char *dest, char *source, int n)
{
	char *ptr_s = source;
	char *ptr_d = dest;
	int dot_count = 1;
	
	while (dot_count < n) {
		if(*ptr_s++ == ',')
			dot_count++;
		
		if(*ptr_s == '\0')
			return 0;
	}
	
	while(*ptr_s != ',') {
		*ptr_d = *ptr_s;
		ptr_d++;
		ptr_s++;
	}
	
	*ptr_d = '\0';
	
	return ptr_d - dest; //this is len exclude terminal chr \0
}

void getfll(char *dest, const char *source_file, const char *message)
{
	FILE *fpin;
	char buf[NMF_LNE_SIZE];
	int message_len = strlen(message);
	fpin = fopen(source_file, "r");
	
	if (fpin == NULL) {
		printf("cannot open %s.\n", source_file);
		exit(-1);
	}
	
	fgets(buf, NMF_LNE_SIZE, fpin);
	while (!feof(fpin)) {
		if (strncmp(buf, message, message_len) == 0) {
			strcpy(dest, buf);
			break;
		}
		
		fgets(buf, NMF_LNE_SIZE, fpin);
	}
	
	fclose(fpin);
}

void getall (const char *source_file, const char *message, char *dest_file)
{
	FILE *fpin, *fpout;
	char buf[NMF_LNE_SIZE];
	int message_len = strlen(message);
	
	sprintf(dest_file, "Only_%s", message);
	//strcpy(dest_file, "only_GPS");
	
	fpin = fopen(source_file, "r");
	if (fpin == NULL) {
		printf("cannot open %s.\n", source_file);
		exit(-1);
	}
	
	fpout = fopen(dest_file, "w");
	if (fpin == NULL) {
		printf("cannot open %s.\n", dest_file);
		exit(-1);
	}
	
	fgets(buf, NMF_LNE_SIZE, fpin);
	while (!feof(fpin)) {
		if (strncmp(buf, message, message_len) == 0) {
			fputs(buf, fpout);
		}
		fgets(buf, NMF_LNE_SIZE, fpin);
	}
	
	fclose(fpin);
	fclose(fpout);
}

void getnll (const char *source_file, const char *message, char *dest_file)
{
	FILE *fpin, *fpout;
	char buf[NMF_LNE_SIZE];
	int message_len = strlen(message);
	
	sprintf(dest_file, "Remove_%s", message);
	//strcpy(dest_file, "remove_GPS");
	
	fpin = fopen(source_file, "r");
	if (fpin == NULL) {
		printf("cannot open %s.\n", source_file);
		exit(-1);
	}
	
	fpout = fopen(dest_file, "w");
	if (fpin == NULL) {
		printf("cannot open %s.\n", dest_file);
		exit(-1);
	}
	
	fgets(buf, NMF_LNE_SIZE, fpin);
	while (!feof(fpin)) {
		if (strncmp(buf, message, message_len) != 0) {
			fputs(buf, fpout);
		}
		fgets(buf, NMF_LNE_SIZE, fpin);
	}
	
	fclose(fpin);
	fclose(fpout);
}
