#include <io.h> 
#include <iostream>
#include "findfile.h"


void FindFile(V_str& V_filename, const char* filter)
{
	//預設會存放的檔案名稱個數 
	V_filename.reserve(30);
	//存放目前找到檔案檔名的buf 
	std::string cur_find_file;
	struct _finddata_t c_file;
	long hFile;
	
	hFile = _findfirst(filter, &c_file);
	if (hFile == -1) {	//沒找到符合filter的檔案 
		return ;
	}
	
	do {				
		cur_find_file = c_file.name;
		V_filename.push_back(cur_find_file);
		
	//一直找直到找不到下一個包含 filter的檔案 
	} while (_findnext(hFile, &c_file) == 0);
	return ;
}

void PrintFindFile(V_str& V_filename)
{
	V_str::iterator i_str;
	for (i_str = V_filename.begin(); i_str != V_filename.end(); ++ i_str)
		std::cout << *i_str << std::endl;
}
