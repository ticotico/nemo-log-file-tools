#include "findfile.h"
#include "read_file_by_line.h"
#include "cell_id_io.h"
#include <ctime>
#include <iostream>
#include <fstream> 
int main()
{
	std::clock_t t_start = clock(), t_end;	//定義程式開始與結束時間 ，追曾效率用 
	V_UMTS_id v_umts_id; //定義存放 cell id 資料的容器 
	V_LTE_id v_lte_id;//定義存放 cell id 資料的容器 
	//先找出要開啟檔案的檔名 
	V_str nmf_file;	//定義存放檔名的容器 
	FindFile(nmf_file, "*.nmf");	//找相對路徑內的檔案並加入容器 
	//PrintFindFile(nmf_file);
	
	//逐步開啟每個檔案，並對其做操作 
	V_str::iterator pfilename = nmf_file.begin();
	while (pfilename != nmf_file.end()) {
		read_file_by_line(v_umts_id, v_lte_id, pfilename->c_str());
		++ pfilename;
	}
	std::ofstream fileOut("output.csv");
	fileOut.close();
	output_cid_data(v_umts_id, "output.csv");
	output_cid_data(v_lte_id, "output.csv");
	t_end = clock();
	std::cout << "Total run time: " << (double)(t_end - t_start) / 1000.0 << " sec" << std::endl;
	system("pause");
	return 0;
}
