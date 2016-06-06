#ifndef FIND_FILE_H
#define FIND_FILE_H
#include <vector>
#include <string>
typedef std::vector<std::string> V_str;
//將相對路徑中包含 filter 字串的檔案 通通存入 string vector  V_filename 中 
void FindFile(V_str& V_filename, const char* filter);
//將 V_filename 存放的每一個 string 印出 
void PrintFindFile(V_str& V_filename);
#endif
