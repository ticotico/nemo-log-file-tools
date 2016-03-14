#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cid_io.h"

#define LOG_LINE_MAX_LEN 20000
void if_add_UMTS(char *RRCSM_log_line, UMTS_cid *UMTS_cid_struct_ptr);
void if_add_LTE(char *CELLSCAN_log_line, LTE_cid *LTE_cid_struct_ptr);

void read_file_by_line_and_add_cid
	(const char *filename, UMTS_cid *UMTS_cid_struct_ptr, LTE_cid *LTE_cid_struct_ptr)
{
	FILE *fp_in_nmf = fopen(filename, "r");
	assert(fp_in_nmf != NULL);
	
	char log_line[LOG_LINE_MAX_LEN];
	
	fgets(log_line, LOG_LINE_MAX_LEN, fp_in_nmf);
	while(!feof(fp_in_nmf)) {
		if (strncmp(log_line, "RRCSM", 5) == 0)
			if_add_UMTS(log_line, UMTS_cid_struct_ptr);
		if (strncmp(log_line, "CELLSCAN", 8) == 0)
			if_add_LTE(log_line, LTE_cid_struct_ptr);
		
		fgets(log_line, LOG_LINE_MAX_LEN, fp_in_nmf);
	}
	fclose(fp_in_nmf);
	return ;
}

void if_add_UMTS(char *RRCSM_log_line, UMTS_cid *UMTS_cid_struct_ptr)
{
	const char sib3[] = "\"SYSTEM_INFORMATION_BLOCK_TYPE_3\"";
	char *mark = RRCSM_log_line;
	char *col[12];
	int i;
	// 把行尾的 \n 去掉 
	*strrchr(RRCSM_log_line, '\n') = '\0';
	// col[5] 指向 sib 的 layer
	// col[7] 指向 channel
	// col[9] 指向 RRSCM 的資訊  (如果是 sib3 就是 cid) 
	col[0] = RRCSM_log_line;
	mark = strchr(mark+1, ',');
	for (i = 1; mark != NULL; i++) {
		col[i] = mark + 1;
		*mark = '\0';
		mark = strchr(mark+1, ',');
	}
	// 如果 RRCSM 是存放 sib3 的 log line 
	if (strcmp(sib3, col[5]) == 0)
		add_UMTS_cid (UMTS_cid_struct_ptr, atoi(col[7]), col[9]);
	
	#ifdef DEBUG
	printf("%s:%d\n", __FILE__, __LINE__);	
	printf("%s\t%s\t%s\n", col[4], col[6], col[8]);
	#endif //DEBUG
	return ;
}

void if_add_LTE(char *CELLSCAN_log_line, LTE_cid *LTE_cid_struct_ptr)
{
	char *mark = CELLSCAN_log_line;
	char *col[6];
	char channel[8], cid[12];
	int data_count, i, j;
	// 把行尾的 \n 去掉 
	*strrchr(CELLSCAN_log_line, '\n') = '\0';
	// 取得  data_count (在 CELLSCAN line 的第六個 ',' 之後 
	for (i = 0; i < 6; i++)
		mark = strchr(mark+1, ',');
	sscanf(mark, ",%d,%*s", &data_count);
	// shift col
	for (i = 0; i < 2; i++)
		mark = strchr(mark+1, ',');
	// 接下來每六個 col 為一組 data 
	// col[0]為 channel
	// col[5] 為 cid 
	for (i = 0; i < data_count; i++) {
		for (j = 0; j < 6; j++) {
			col[j] = mark + 1;
			*(mark) = '\0' ;
			mark = strchr(mark + 1, ',');
		}
		// 如果 col[5] 有存放資料 (不是 ',' or '\0') 
		if (*col[5] !=',' && *col[5] != '\0')  {
			add_LTE_cid (LTE_cid_struct_ptr, atoi(col[0]), atol(col[5]));
		}
		#ifdef DEBUG
		printf("%s:%d\n", __FILE__, __LINE__);	
		printf("%dth data: %d, %ld\n", i, atoi(col[0]), atol(col[5]));
		#endif //DEBUG
	}
	return ;
}
