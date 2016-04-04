#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "msg_data_operate.h"

#ifndef NMF_LOG_MAX_LEN
#define NMF_LOG_MAX_LEN 20000
#endif

// 函式功能: 回傳 log_line 第 nth 欄 的開始地址
// 給之後的 atol 用
char *getcol (char * log_line, int nth)
{
  char *pt_n_col = log_line;
  int n = 0;
  while ( n < nth ) {
    if ( *pt_n_col == '\0' )  return NULL;
    if ( *pt_n_col == ',' )  { n++; }
	pt_n_col++;
  }
  return pt_n_col;
}

void read_nmf_thrp_data (const char *cur_filename, thrpData *combine_result)
{
  FILE *fp_nmf_in = fopen(cur_filename, "r");
  if (fp_nmf_in == NULL) {
    printf("open %s fail.\n", cur_filename);
    return ;
  }
  char log_line[NMF_LOG_MAX_LEN];
  char *dl_data_pos, *ul_data_pos;
  long int get_thrp;
  double get_thrp_in_MB;
  thrpData cur_file_thrpData;
  thtpDataInit( &cur_file_thrpData );
  
  fgets( log_line, NMF_LOG_MAX_LEN, fp_nmf_in );
  while ( !feof(fp_nmf_in) ) {
    if ( strncmp( log_line, "DRATE", 5) == 0 ) {
      dl_data_pos = getcol( log_line, 6 );
	  ul_data_pos = getcol( log_line, 5 );
	  
	  if ( dl_data_pos != NULL && isdigit(*dl_data_pos) ) {
		  get_thrp = atol( dl_data_pos );
		  get_thrp_in_MB = (double)get_thrp / 1000.0;
		  add_thrpData( combine_result, "dl", get_thrp_in_MB );
		  add_thrpData( &cur_file_thrpData, "dl", get_thrp_in_MB );
	  }
	  
	  if ( ul_data_pos != NULL && isdigit(*ul_data_pos) ) {
		  get_thrp = atol( ul_data_pos );
		  get_thrp_in_MB = (double)get_thrp / 1000.0;
		  add_thrpData( combine_result, "ul", get_thrp_in_MB);
		  add_thrpData( &cur_file_thrpData, "ul", get_thrp_in_MB);
	  }
	}
	fgets( log_line, NMF_LOG_MAX_LEN, fp_nmf_in );
  }
  
  thrpDataPrint( &cur_file_thrpData );
  
  fclose(fp_nmf_in);
  return ;
}
