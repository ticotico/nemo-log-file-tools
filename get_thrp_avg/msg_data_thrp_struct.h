#ifnedf msg_data_thrp_struct_H
#define msg_data_thrp_struct_H
typedef struct {
  double dl_sum, ul_sum;
  int dl_count, ul_count;
} thrpData;
#endif
