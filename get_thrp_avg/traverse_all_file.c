#include <stdio.h>
#include <string.h>
#include <io.h> // for c_file
#include "msg_data_operate.h"

#ifndef FILENAME_MAX_LEN
#define FILENAME_MAX_LEN 256
#endif // FILENAME_MAX_LEN

void read_nmf_thrp_data (const char *cur_filename, thrpData *combine_result);

void traverse_all_file (void)
{
  char filter[FILENAME_MAX_LEN];
  struct _finddata_t c_file;
  long hFile;
  thrpData combine_result;
  thtpDataInit (&combine_result);
  
  
  strcpy( filter, "*.nmf" );

  hFile = _findfirst( filter, &c_file);
  if ( hFile == -1) {
    printf("cannot find nemo log file.\n");
    return ;
  }

  do {
    printf("filename: %s\n", c_file.name);
	read_nmf_thrp_data( c_file.name, &combine_result );
	printf("-------------------------------------\n");
  } while ( _findnext( hFile, &c_file ) == 0);
  
  printf("\nabove log file total result:\n");
  thrpDataPrint( &combine_result );
  
  return;
}
