#include <string.h>

#ifndef msg_data_thrp_struct_H
#define msg_data_thrp_struct_H
typedef struct {
  double dl_sum, ul_sum;
  int dl_count, ul_count;
} thrpData;
#endif

// 函式功能: 初始化存放資料的結構。
void thtpDataInit (thrpData *td);
// 函式功能: 印出 log 檔 thrp 的平均值
void thrpDataPrint (thrpData *td);
// 函式功能: 加入一筆新的資料至結構中
void add_thrpData( thrpData *td, const char *dlul, double thrp);



