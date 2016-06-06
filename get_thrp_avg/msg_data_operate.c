#include <stdio.h>
#include "msg_data_operate.h"

// 函式功能: 初始化存放資料的結構。
void thtpDataInit (thrpData *td)
{
  td->dl_sum = 0.0;
  td->dl_count = 0;
  td->ul_sum = 0.0;
  td->ul_count = 0;
  return;
}

// 函式功能: 印出 log 檔 thrp 的平均值
void thrpDataPrint (thrpData *td)
{
  if ( td->dl_count == 0 && td->ul_count == 0 )
    printf("no thrpoughput data.\n");
  else {
    if ( td->dl_count > 0 )
	  printf("app_thrp_dl avg = %.3f\n", td->dl_sum / td->dl_count);
    if ( td->ul_count > 0 )
	  printf("app_thrp_ul avg = %.3f\n", td->ul_sum / td->ul_count);
  }
  return ;
}

// 函式功能: 加入一筆新的資料至結構中
void add_thrpData( thrpData *td, const char *dlul, double thrp)
{
  if ( strcmp(dlul, "dl") == 0 ) {
    td->dl_sum += thrp;
    td->dl_count++;
  }
  if ( strcmp(dlul, "ul") == 0 ) {
    td->ul_sum += thrp;
    td->ul_count++;
  }
}
