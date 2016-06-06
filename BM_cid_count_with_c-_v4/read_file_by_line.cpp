#include <fstream>
#include <iostream>
#include "read_file_by_line.h"
#include "cell_id_io.h"


void read_file_by_line(V_UMTS_id& v_umts_id, V_LTE_id& v_lte_id, const char* filename)
{
	std::ifstream fileIn;	//定義讀檔物件 
	std::string log_line;	//定義存放檔案每一行的buf 
	try		//開檔 
	{
		fileIn.open(filename);
		if(fileIn.fail()) throw "open fail: ";
	}
	catch (const char* eptr) {std::cerr << eptr << filename << std::endl; return;}
	std::cout << "Read " << filename << std::endl;
	//開始逐行讀檔 
	getline(fileIn, log_line, '\n');
	while(fileIn.peek() != EOF) {
		//這裡開始對檔案的每一行做操作	
		get_combined_cid(log_line, v_umts_id, v_lte_id);
		getline(fileIn, log_line, '\n');
	}
	fileIn.close();
}
