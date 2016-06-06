#ifndef CELL_ID_IO_H
#define CELL_ID_IO_H
#include "V_cid.h"
void print_cid_data(V_UMTS_id& v_umts_id);
void print_cid_data(V_LTE_id& v_lte_id);
void add_cid_data(V_UMTS_id& v_umts_id, V_UMTS_id& newone);
void add_cid_data(V_LTE_id& v_umts_id, V_LTE_id& newone);
void output_cid_data(V_UMTS_id& v_umts_id, const char *filename);
void output_cid_data(V_LTE_id& v_lte_id, const char *filename);
void get_next_str_col(const std::string& str, size_t* pos);
void get_cur_str_col_end(const std::string& str, size_t beg, size_t* end);
void get_cur_str_col_sub_string(const std::string& str, std::string* sub, size_t cur_col);
void get_combined_cid(const std::string& str, V_UMTS_id& v_umts_id, V_LTE_id& v_lte_id);
#endif
