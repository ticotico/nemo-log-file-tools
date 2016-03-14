#include <stdio.h>
#include <string.h>
#include <io.h> // for c_file
#include <direct.h>
#include "cid_io.h" 

#define FILENAME_LEN 256
void traverse_all_files(void)
{
	// 對找資料夾內特定檔案需要的變數做定義 
	char cur_dir[FILENAME_LEN], filter[FILENAME_LEN], cur_filename[FILENAME_LEN];
	struct _finddata_t c_file;
	long hFile;
	// 對輸出結構做定義 
	LTE_cid LTE_cid_struct;
	ini_LTE_cid (&LTE_cid_struct);
	UMTS_cid UMTS_cid_struct;
	ini_UMTS_cid (&UMTS_cid_struct);
	
	// 設定目前目錄 與 *.nmf api
	getcwd(cur_dir, FILENAME_LEN);
	strcpy(filter, "*.nmf");
	
	// 確認目前目錄有 nmf檔 
	hFile = _findfirst(filter, &c_file);
	if (hFile != -1) { // 如果有 nmf檔 ，則依序讀入每個 nmf 檔 
		do {
			sprintf(cur_filename, "%s\\%s", cur_dir, c_file.name);
			#ifdef DEBUG
			printf("%s:%d\n", __FILE__, __LINE__);
			printf("find file: %s\n", cur_filename);
			#endif
			// 對每個 nmf 檔作讀入 
			read_file_by_line_and_add_cid(cur_filename, &UMTS_cid_struct, &LTE_cid_struct);
			
		} while(_findnext(hFile, &c_file) == 0);
	}
	
	// 輸出結果至 cellid.csv
	print_all_cid(&LTE_cid_struct, &UMTS_cid_struct, "cellid.csv");
	#ifdef DEBUG
	printf("%s:%d\n", __FILE__, __LINE__);
	print_LTE_cid(&LTE_cid_struct);
	print_UMTS_cid(&UMTS_cid_struct);
	#endif //DEBUG
	// 結束時釋放 cid 結構所 malloc 的記憶體 
	close_LTE_cid(&LTE_cid_struct);
	close_UMTS_cid(&UMTS_cid_struct);
	return ;
}
