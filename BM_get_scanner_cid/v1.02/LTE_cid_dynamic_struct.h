#include "LTE_cid_unit.h"

#ifndef LTE_cid_def
#define LTE_cid_def
typedef struct {
	LTE_cid_unit **array;
	int array_size;
	int array_member; 
} LTE_cid;
#endif // LTE_cid_def
