#include <fstream>
#include <iostream>
#include <cstring> //for strlen
#include <cstdlib>
#include "cell_id_io.h"
namespace
{
	const char sib3[] = "\"SYSTEM_INFORMATION_BLOCK_TYPE_3\"";
	const int sib3len = strlen(sib3);
	enum { GSM, UMTS, LTE, TECHNOLOGY_COUNT};
	char technology[TECHNOLOGY_COUNT][5] = {"GSM", "UMTS", "LTE"};
}

void cellID::print() {
	std::cout << system << '\t' << channel << '\t' << count << std::endl;
}

void cellLTE::print() {
	std::cout << system << '\t' << channel << '\t' << id << '\t' << count << std::endl;
}

void cellUMTS::print() {
	std::cout << system << '\t' << channel << '\t' << id << '\t' << count << std::endl;
}

void output(cellLTE& data, std::ofstream& fileOut) {
	fileOut << data.system << ','
			<< data.channel << ',' 
			<< data.id << ',' 
			<< data.count << std::endl;
}

void output(cellUMTS& data, std::ofstream& fileOut) {
	fileOut << data.system << ','
			<< data.channel << ',' 
			<< data.id << ',' 
			<< data.count << std::endl;
}

void print_cid_data(V_UMTS_id& v_cid)
{
	V_UMTS_id::iterator p_v_cid = v_cid.begin();
	while (p_v_cid != v_cid.end()) {
		p_v_cid->print();
		++ p_v_cid;
	}
}

void print_cid_data(V_LTE_id& v_cid)
{
	V_LTE_id::iterator p_v_cid = v_cid.begin();
	while (p_v_cid != v_cid.end()) {
		p_v_cid->print();
		++ p_v_cid;
	}
}

void add_cid_data(V_UMTS_id& v_cid, cellUMTS& newone)
{
	V_UMTS_id::iterator p_v_cid = v_cid.begin();
	while (p_v_cid != v_cid.end()) {
		if (*p_v_cid == newone) {
			p_v_cid->inc_count();
			return;
		}
		++ p_v_cid;
	}
	if (p_v_cid == v_cid.end()) {
		v_cid.push_back(newone);
	}
}

void add_cid_data(V_LTE_id& v_cid, cellLTE& newone)
{
	V_LTE_id::iterator p_v_cid = v_cid.begin();
	while (p_v_cid != v_cid.end()) {
		if (*p_v_cid == newone) {
			p_v_cid->inc_count();
			return;
		}
		++ p_v_cid;
	}
	if (p_v_cid == v_cid.end()) {
		v_cid.push_back(newone);
	}
}

void output_cid_data(V_UMTS_id& v_cid, const char *filename)
{
	std::ofstream fileOut;
	try
	{
		fileOut.open(filename, std::ios::app);
		if(fileOut.fail()) throw("open fail: ");
	}
	catch(const char* perror)
	{
		std::cout << perror << filename << std::endl;
		exit(0);
	}
	
	V_UMTS_id::iterator p_v_cid = v_cid.begin();
	while (p_v_cid != v_cid.end()) {
		output(*p_v_cid, fileOut);
		++ p_v_cid;
	}
	
	fileOut.close();
}

void output_cid_data(V_LTE_id& v_cid, const char *filename)
{
	std::ofstream fileOut;
	try
	{
		fileOut.open(filename, std::ios::app);
		if(fileOut.fail()) throw("open fail: ");
	}
	catch(const char* perror)
	{
		std::cout << perror << filename << std::endl;
		exit(0);
	}
	
	V_LTE_id::iterator p_v_cid = v_cid.begin();
	while (p_v_cid != v_cid.end()) {
		output(*p_v_cid, fileOut);
		++ p_v_cid;
	}
	
	fileOut.close();
}

inline
void get_next_str_col(const std::string& str, size_t* pos)
{*pos = str.find(',' , *pos) + 1;}

inline
void get_cur_str_col_end(const std::string& str, size_t beg, size_t* end)
{*end = beg; *end = str.find(',' , *end) - 1;}

void get_cur_str_col_sub_string(const std::string& str, std::string* sub, size_t cur_col)
{
	size_t cur_col_end;
	get_cur_str_col_end(str, cur_col, &cur_col_end);
	sub->assign(str, cur_col, cur_col_end - cur_col + 1);
}


void get_combined_cid(const std::string& str, V_UMTS_id& v_umts_id, V_LTE_id& v_lte_id)
{
	char* cur_system;
	int cur_channel;
	std::string cur_id;
	size_t cur_col = 0, cur_col_end;
	std::string tmp_str;
	
	if (str.compare(0, 5, "RRCSM") == 0)  {
		//第五個 col 是 sib layer
		//如果第五個 col 是 sib3 
		//第七個 col 是 channel 
		//第九個 col 是 cellid
		
		//確認第五個 col 是不是sib3 
		for(int i = 0; i < 5; i++)
			get_next_str_col(str, &cur_col);
		if (str.compare(cur_col, sib3len, sib3) == 0) {
			cur_system = technology[UMTS];
			//取得第七個 col 的 channel 資料 (cur_col 往後移動兩個 ) 
			for(int i = 0; i < 2; i++)
				get_next_str_col(str, &cur_col);
			get_cur_str_col_sub_string(str, &tmp_str, cur_col);
			cur_channel = atoi(tmp_str.data());
			//取得第九個 col 的 cellid 資料  (cur_col 往後移動兩個 ) 
			for(int i = 0; i < 2; i++)
				get_next_str_col(str, &cur_col);
			get_cur_str_col_sub_string(str, &cur_id, cur_col);
			//std::cout << cur_system << '\t' << cur_channel << '\t' << cur_id << std::endl;
			cellUMTS cur_cid_data;
			cur_cid_data.set(cur_system, cur_channel, cur_id);
			add_cid_data(v_umts_id, cur_cid_data);
		}
	}
	if (str.compare(0, 8, "CELLSCAN") == 0) {
		//第 6 個 col 會記錄接下來有 data_count 組資料，每組六個 col 
		//從 第 8 個 col 開始 
		//接下來每組中
		// col[0]為 channel
		// col[5] 為 cid 
		
		//取得data_count 
		for (int i = 0; i < 6; i++)
			get_next_str_col(str, &cur_col);
		get_cur_str_col_sub_string(str, &tmp_str, cur_col);
		int data_count = atoi(tmp_str.c_str());
		//移動到第 8 個 col
		for (int i = 0; i < 2; i++)
			get_next_str_col(str, &cur_col);
		//讀取 data_count 次 
		for (int m = 0; m < data_count; m++) {
			// col[0]為 channel
			get_cur_str_col_sub_string(str, &tmp_str, cur_col);
			cur_channel = atoi(tmp_str.c_str());
			// col[5] 為 cid 
			for (int i = 0; i < 5; i++)
				get_next_str_col(str, &cur_col);
			get_cur_str_col_sub_string(str, &cur_id, cur_col);
			int cur_lte_id = atoi(cur_id.data());
			//移到下一組資料的開頭處 
			get_next_str_col(str, &cur_col);
			//cell_id有可能為空，只需要不為空的資料 
			if (cur_id.size() != 0) {
				//std::cout << "ch: "<< cur_channel << '\t' << "id: "<< cur_id << std::endl;
				cur_system = technology[LTE];
				
				cellLTE cur_cid_data;
				cur_cid_data.set(cur_system, cur_channel, cur_lte_id);
				add_cid_data(v_lte_id, cur_cid_data);
			}
		}
	}
}
